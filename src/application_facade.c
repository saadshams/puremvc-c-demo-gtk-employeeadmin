#include "application_facade.h"

#include "controller/startup_command.h"

static void (*super_initializeController)(struct IFacade *self, struct IController *controller);

static void initializeController(struct IFacade *self, struct IController *controller) {
    super_initializeController(self, controller); // Call retained (super) initialization
    self->registerCommand(self, STARTUP, startup_command_init);
}

static void startup(const struct ApplicationFacade *self, void *body) {
    const struct IFacade *facade = self->super;
    facade->sendNotification(facade, STARTUP, body, NULL);
}

static void assign(const struct ApplicationFacade *self, void *component, const char *mediatorName) {
    const struct IFacade *facade = self->super;
    facade->sendNotification(facade, REGISTER, component, mediatorName);
}

struct IFacade *application_facade_getInstance(struct FacadeMap **facadeMap, const char *key) {
    struct IFacade *facade = puremvc_facade_getInstance(facadeMap, key);
    super_initializeController = facade->initializeController; // Retain original initializer
    facade->initializeController = initializeController; // override
    return facade;
}

struct ApplicationFacade *application_facade_extend(struct ApplicationFacade *facade, struct IFacade *super) {
    facade->super = super;
    facade->assign = assign;
    facade->startup = startup;
    return facade;
}
