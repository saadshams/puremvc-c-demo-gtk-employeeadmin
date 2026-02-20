#include "user_form_mediator.h"

#include "employee_admin/i_user_form.h"
#include "view/components/user_form.h"

static void onRegister(struct IMediator *self) {
    struct UserForm *component = self->getComponent(self);
    // component->setDelegate(component, (struct IUserForm) { .context = self });
}

static const char *const *listNotificationInterests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { NULL };
    return interests;
}

static void handleNotification(const struct IMediator *self, struct INotification *notification) {

}

struct IMediator *user_form_mediator_init(void *buffer, const char *name, void *component) {
    struct IMediator *mediator = puremvc_mediator_init(buffer, name, component);
    mediator->onRegister = onRegister;
    mediator->listNotificationInterests = listNotificationInterests;
    mediator->handleNotification = handleNotification;
    return mediator;
}

struct UserFormMediator *user_form_mediator_bind(struct UserFormMediator *mediator, struct IMediator *super) {
    mediator->super = super;
    return mediator;
}