#pragma once

#include <puremvc/puremvc.h>

#define VERSION "EmployeeAdmin Version 1.0.0"
#define STARTUP "startup"
#define SERVICE "service"
#define SERVICE_RESULT "service_result"
#define SERVICE_FAULT "service_fault"

struct ApplicationFacade {
    struct IFacade *super;

    void (*registerComponent)(const struct ApplicationFacade *self, const char *mediatorName, void *component);
    void (*startup)(const struct ApplicationFacade *self);
};

struct IFacade *application_facade_getInstance(struct FacadeMap **facadeMap, const char *key);

struct ApplicationFacade *application_facade_bind(struct ApplicationFacade *facade, struct IFacade *super);
