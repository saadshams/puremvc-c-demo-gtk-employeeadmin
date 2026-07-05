#include "startup_command.h"

#include "application_facade.h"
#include "register_command.h"
#include "model/user_proxy.h"
#include "model/role_proxy.h"
#include "model/value_object/user_vo.h"
#include "view/user_list_mediator.h"
#include "view/user_form_mediator.h"
#include "view/user_role_mediator.h"

#include <puremvc/puremvc.h>

#pragma region Operations

static void execute(const struct ICommand *self, struct INotification *notification) {
    const struct INotifier *notifier = self->get_notifier(self);
    const struct IFacade *facade = notifier->get_facade(notifier);

    facade->register_command(facade, REGISTER, register_command_new);
    facade->register_proxy(facade, user_proxy_new());
    facade->register_proxy(facade, role_proxy_new());

    const struct UserProxy *user_proxy = facade->retrieve_proxy(facade, UserProxy_NAME)->sub;
    user_proxy->save(user_proxy, user_vo_new("lstooge", "Larry", "Stooge",
        "larry@stooges.com", "ijk456", DEPT_ACCT));
    user_proxy->save(user_proxy, user_vo_new("cstooge", "Curly", "Stooge",
    "curly@stooges.com", "xyz987", DEPT_SALES));
    user_proxy->save(user_proxy, user_vo_new("mstooge", "Moe", "Stooge",
     "moe@stooges.com", "abc123", DEPT_PLANT));

    // role_proxy->add_item(role_proxy, role_vo_new("lstooge", (enum RoleEnum[]) {ROLE_PAYROLL, ROLE_NONE_SELECTED}));
    // role_proxy->add_item(role_proxy, role_vo_new("cstooge", (enum RoleEnum[]) {ROLE_ACCT_PAY,
        // ROLE_ACCT_RCV, ROLE_GEN_LEDGER, ROLE_NONE_SELECTED}));
    // role_proxy->add_item(role_proxy, role_vo_new("cstooge", (enum RoleEnum[]) {ROLE_INVENTORY,
        // ROLE_PRODUCTION, ROLE_SALES, ROLE_SHIPPING, ROLE_NONE_SELECTED}));

    facade->register_mediator(facade, user_list_mediator_new());
    facade->register_mediator(facade, user_form_mediator_new());
    facade->register_mediator(facade, user_role_mediator_new());
}

#pragma endregion

#pragma region Public API

struct ICommand *startup_command_new() {
    struct ICommand *command = puremvc_command_new();
    command->execute = execute; // override
    return command;
}

#pragma endregion
