#include "register_command.h"
#include "view/user_list_mediator.h"
#include "view/user_form_mediator.h"
#include "view/user_role_mediator.h"

#include <string.h>

static void execute(const struct ICommand *self, struct INotification *notification) {
    const struct INotifier *notifier = self->getNotifier(self);
    const struct IFacade *facade = notifier->getFacade(notifier);

    void *component = notification->getBody(notification);
    const char *mediatorName = notification->getType(notification);

    struct IMediator *super = facade->retrieveMediator(facade, mediatorName);
    if (strcmp(mediatorName, UserListMediator_NAME) == 0) { // register delegate within mediator scope
        const struct UserListMediator *mediator = user_list_mediator_bind(&(struct UserListMediator){}, super);
        mediator->registerComponent(mediator, component);
    } else if (strcmp(mediatorName, UserFormMediator_NAME) == 0) {
        const struct UserFormMediator *mediator = user_form_mediator_bind(&(struct UserFormMediator){}, super);
        mediator->registerComponent(mediator, component);
    } else if (strcmp(mediatorName, UserRoleMediator_NAME) == 0) {
        const struct UserRoleMediator *mediator = user_role_mediator_bind(&(struct UserRoleMediator){}, super);
        mediator->registerComponent(mediator, component);
    }
}

struct ICommand *register_command_init(void *buffer) {
    struct ICommand *command = puremvc_simple_command_init(buffer);
    command->execute = execute; // override
    return command;
}
