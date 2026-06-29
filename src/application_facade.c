#include "application_facade.h"

#include "controller/startup_command.h"

static void (*super_initializeController)(struct IFacade *self);

static void initialize_controller(struct IFacade *self) {
    super_initializeController(self); // Call overridden (super) initialization
    self->register_command(self, STARTUP, startup_command_new);
}

static void startup(const struct ApplicationFacade *self) {
    const struct IFacade *facade = self->super;
    facade->send_notification(facade, STARTUP, NULL, NULL);
}

static void set_component(const struct ApplicationFacade *self, void *component, const char *mediatorName) {
    const struct IFacade *facade = self->super;
    facade->send_notification(facade, REGISTER, component, mediatorName);
}

struct IFacade *application_facade_getInstance(const char *key) {
    struct IFacade *facade = puremvc_facade_get_instance(key);
    super_initializeController = facade->initialize_controller; // Save original initializer
    facade->initialize_controller = initialize_controller; // override
    return facade;
}

struct ApplicationFacade *application_facade_extend(struct ApplicationFacade *facade, struct IFacade *super) {
    facade->super = super;
    facade->startup = startup;
    facade->set_component = set_component;

    return facade;
}
