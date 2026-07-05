#include "register_command.h"
#include "view/user_list_mediator.h"
#include "view/user_form_mediator.h"
#include "view/user_role_mediator.h"

#include <string.h>

#pragma region Operations

static void execute(const struct ICommand *self, struct INotification *notification) {
    const struct INotifier *notifier = self->get_notifier(self);
    const struct IFacade *facade = notifier->get_facade(notifier);

    void *component = notification->get_body(notification);
    const char *mediatorName = notification->get_type(notification);

    if (strcmp(mediatorName, UserListMediator_NAME) == 0) {
        const struct UserListMediator *mediator = facade->retrieve_mediator(facade, mediatorName)->sub;
        mediator->set_component(mediator, component);
    } else if (strcmp(mediatorName, UserFormMediator_NAME) == 0) {
        const struct UserFormMediator *mediator = facade->retrieve_mediator(facade, mediatorName)->sub;
        mediator->set_component(mediator, component);
    } else if (strcmp(mediatorName, UserRoleMediator_NAME) == 0) {
        const struct UserRoleMediator *mediator = facade->retrieve_mediator(facade, mediatorName)->sub;
        mediator->set_component(mediator, component);
    }
}

#pragma endregion

#pragma region Public API

struct ICommand *register_command_new() {
    struct ICommand *command = puremvc_command_new();
    command->execute = execute; // override
    return command;
}

#pragma endregion
