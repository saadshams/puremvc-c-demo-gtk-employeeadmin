#include "application_facade.h"

#include "controller/startup_command.h"
#include "view/user_list_mediator.h"
#include "view/user_form_mediator.h"
#include "view/user_role_mediator.h"

#include <gtk/gtk.h>

static void (*super_initializeController)(struct IFacade *self, struct IController *controller);

static void initializeController(struct IFacade *self, struct IController *controller) {
    super_initializeController(self, controller); // Call original (super) initialization
    self->registerCommand(self, STARTUP, startup_command_init);
}

static void registerComponent(const struct ApplicationFacade *self, const char *mediatorName, void *component) {
    const struct IFacade *facade = self->super;

    struct IMediator *super = facade->retrieveMediator(facade, mediatorName);
    if (strcmp(mediatorName, "UserListMediator") == 0) { // register delegate within mediator scope
        const struct UserListMediator *mediator = user_list_mediator_bind(&(struct UserListMediator){}, super);
        mediator->registerComponent(mediator, component);
    } else if (strcmp(mediatorName, "UserFormMediator") == 0) {
        const struct UserFormMediator *mediator = user_form_mediator_bind(&(struct UserFormMediator){}, super);
        mediator->registerComponent(mediator, component);
    } else if (strcmp(mediatorName, "UserRoleMediator") == 0) {
        const struct UserRoleMediator *mediator = user_role_mediator_bind(&(struct UserRoleMediator){}, super);
        mediator->registerComponent(mediator, component);
    }
}

static void startup(const struct ApplicationFacade *self) {
    const struct IFacade *facade = self->super;
    facade->sendNotification(facade, STARTUP, NULL, NULL);
}

struct IFacade *application_facade_getInstance(struct FacadeMap **facadeMap, const char *key) {
    struct IFacade *facade = puremvc_facade_getInstance(facadeMap, key);
    super_initializeController = facade->initializeController; // Save original initializer
    facade->initializeController = initializeController; // override
    return facade;
}

struct ApplicationFacade *application_facade_bind(struct ApplicationFacade *facade, struct IFacade *super) {
    facade->super = super;
    facade->registerComponent = registerComponent;
    facade->startup = startup;
    return facade;
}
