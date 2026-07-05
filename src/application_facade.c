#include "application_facade.h"
#include "controller/startup_command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma region Initialization

static void (*super_initializeController)(struct IFacade *self); // Super implementation

static void initialize_controller(struct IFacade *self) {
    super_initializeController(self); // Invoke super initialization
    self->register_command(self, STARTUP, startup_command_new);
}

#pragma endregion

#pragma region Operations

static void startup(const struct ApplicationFacade *self) {
    const struct IFacade *facade = self->super;
    facade->send_notification(facade, STARTUP, NULL, NULL);
}

static void set_component(const struct ApplicationFacade *self, void *component, const char *mediatorName) {
    const struct IFacade *facade = self->super;
    facade->send_notification(facade, REGISTER, component, mediatorName);
}

#pragma endregion

#pragma region Memory Management

static size_t size(void) {
    return (sizeof(struct ApplicationFacade) + (sizeof(void *) - 1u)) & ~(sizeof(void *) - 1u);
}

static struct ApplicationFacade *alloc(void) {
    struct ApplicationFacade *facade = malloc(size());

    if (facade == NULL) {
        fprintf(stderr, "\033[0;31m[Todo::ApplicationFacade::alloc] ERROR: Instance allocation failed.\033[0m\n");
        return NULL;
    }

    return facade;
}

static struct ApplicationFacade *init(struct ApplicationFacade *facade) {
    if (facade == NULL) return NULL;

    memset(facade, 0, size());

    facade->startup = startup;
    facade->set_component = set_component;

    return facade;
}

static struct IFacade *new(const char *key) {
    struct IFacade *super = puremvc_facade_new(key);
    if (super == NULL) return NULL;

    struct ApplicationFacade *facade = init(alloc());
    if (facade == NULL) {
        puremvc_facade_remove(key);
        return NULL;
    }

    super_initializeController = super->initialize_controller; // Save super implementation
    super->initialize_controller = initialize_controller; // Override implementation

    // wire bidirectional references
    super->sub = facade; // interface to subclass
    facade->super = super; // subclass to interface

    return super;
}

#pragma endregion

#pragma region Public API

struct IFacade *application_facade_get_instance(const char *key) {
    struct IFacade *facade = puremvc_facade_get_instance(key, new);
    if (facade == NULL) return NULL;
    return facade;
}

#pragma endregion
