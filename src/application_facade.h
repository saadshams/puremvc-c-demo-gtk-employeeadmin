#pragma once

#include <puremvc/puremvc.h>

#define STARTUP "startup"
#define REGISTER "register"

#define NEW_USER "newUser"
#define DELETE_USER "deleteUser"
#define USER_SELECTED "userSelected"

#define CANCEL_SELECTED "cancelSelected"

struct ApplicationFacade {
    struct IFacade *super;

    void (*assign)(const struct ApplicationFacade *self, void *component, const char *mediatorName);
    void (*startup)(const struct ApplicationFacade *self, void *body);
};

struct IFacade *application_facade_getInstance(struct FacadeMap **facadeMap, const char *key);

struct ApplicationFacade *application_facade_extend(struct ApplicationFacade *facade, struct IFacade *super);
