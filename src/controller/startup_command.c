#include "startup_command.h"

#include "model/user_proxy.h"
#include "model/role_proxy.h"
#include "view/user_list_mediator.h"
#include "view/user_form_mediator.h"
#include "view/user_role_mediator.h"

#include <puremvc/puremvc.h>

static void execute(const struct ICommand *self, struct INotification *notification) {
    const struct IFacade *facade = self->getNotifier(self)->getFacade(self->getNotifier(self));

    void **body = notification->getBody(notification);
    facade->registerProxy(facade, user_proxy_init, UserProxy_NAME, body[0]);
    facade->registerProxy(facade, role_proxy_init, RoleProxy_NAME, body[1]);

    facade->registerMediator(facade, user_list_mediator_init, UserListMediator_NAME, NULL);
    facade->registerMediator(facade, user_form_mediator_init, UserFormMediator_NAME, NULL);
    facade->registerMediator(facade, user_role_mediator_init, UserRoleMediator_NAME, NULL);
}

struct ICommand *startup_command_init(void *buffer) {
    struct ICommand *command = puremvc_simple_command_init(buffer);
    command->execute = execute; // override
    return command;
}
