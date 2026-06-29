#pragma once

#include <puremvc/puremvc.h>

#define STARTUP "startup"
#define REGISTER "register"

#define NEW_USER "newUser"
#define DELETE_USER "deleteUser"
#define CANCEL_SELECTED "cancelSelected"

#define USER_SELECTED "userSelected"
#define USER_ADDED "userAdded"
#define USER_UPDATED "userUpdated"
#define USER_DELETED "userDeleted"

struct ApplicationFacade {
    struct IFacade *super;

    void (*startup)(const struct ApplicationFacade *self);
    void (*set_component)(const struct ApplicationFacade *self, void *component, const char *mediatorName);
};

struct IFacade *application_facade_getInstance(const char *key);

struct ApplicationFacade *application_facade_extend(struct ApplicationFacade *facade, struct IFacade *super);
