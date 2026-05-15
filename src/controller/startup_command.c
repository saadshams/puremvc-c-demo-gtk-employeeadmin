#include "startup_command.h"

#include "application_facade.h"
#include "register_command.h"
#include "model/user_proxy.h"
#include "model/role_proxy.h"
#include "model/valueObject/user_vo.h"
#include "view/user_list_mediator.h"
#include "view/user_form_mediator.h"
#include "view/user_role_mediator.h"

#include <puremvc/puremvc.h>

static void execute(const struct ICommand *self, struct INotification *notification) {
    const struct INotifier *notifier = self->getNotifier(self);
    const struct IFacade *facade = notifier->getFacade(notifier);
    void **body = notification->getBody(notification);

    facade->registerCommand(facade, REGISTER, register_command_init);
    facade->registerProxy(facade, user_proxy_init, UserProxy_NAME, body[0]);
    facade->registerProxy(facade, role_proxy_init, RoleProxy_NAME, body[1]);

    struct IProxy *super = facade->retrieveProxy(facade, UserProxy_NAME);
    struct UserProxy *user_proxy = user_proxy_extend(&(struct UserProxy) {}, super);

    user_proxy->add(user_proxy, &(struct UserVO) { .username = "lstooge", .first = "Larry", .last = "Stooge",
        .email = "larry@stooges.com", .password = "ijk456", .department = DEPT_ACCT });
    user_proxy->add(user_proxy, &(struct UserVO) { .username = "cstooge", .first = "Curly", .last = "Stooge",
        .email = "curly@stooges.com", .password = "xyz987", .department = DEPT_SALES });
    user_proxy->add(user_proxy, &(struct UserVO) { .username = "mstooge", .first = "Moe", .last = "Stooge",
        .email = "moe@stooges.com", .password = "abc123", .department = DEPT_SALES });

    const struct RoleProxy *role_proxy = (struct RoleProxy *) facade->retrieveProxy(facade, RoleProxy_NAME);
    role_proxy->addItem(role_proxy, &(struct RoleVO) { .username = "lstooge", .roles = {ROLE_PAYROLL} });
    role_proxy->addItem(role_proxy, &(struct RoleVO) { .username = "cstooge", .roles = {ROLE_ACCT_PAY,
        ROLE_ACCT_RCV, ROLE_GEN_LEDGER} });
    role_proxy->addItem(role_proxy, &(struct RoleVO) { .username = "cstooge", .roles = {ROLE_INVENTORY,
        ROLE_PRODUCTION, ROLE_SALES, ROLE_SHIPPING} });

    facade->registerMediator(facade, user_list_mediator_init, UserListMediator_NAME, NULL);
    facade->registerMediator(facade, user_form_mediator_init, UserFormMediator_NAME, NULL);
    facade->registerMediator(facade, user_role_mediator_init, UserRoleMediator_NAME, NULL);
}

struct ICommand *startup_command_init(void *buffer) {
    struct ICommand *command = puremvc_simple_command_init(buffer);
    command->execute = execute; // override
    return command;
}
