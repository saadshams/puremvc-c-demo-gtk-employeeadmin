#include "startup_command.h"

#include "application.h"
#include "application_facade.h"
#include "view/user_list_mediator.h"
#include "view/user_form_mediator.h"
#include "view/user_role_mediator.h"

static void execute(const struct ICommand *self, struct INotification *notification) {
    const struct IFacade *facade = self->getNotifier(self)->getFacade(self->getNotifier(self));
    struct Stage *stage = notification->getBody(notification);

    facade->registerMediator(facade, user_list_mediator_init, UserListMediator_NAME, &stage->list);
    facade->registerMediator(facade, user_form_mediator_init, UserFormMediator_NAME, &stage->form);
    facade->registerMediator(facade, user_role_mediator_init, UserRoleMediator_NAME, &stage->role);
}

struct ICommand *startup_command_init(void *buffer) {
    struct ICommand *command = puremvc_simple_command_init(buffer);
    command->execute = execute; // override
    return command;
}
