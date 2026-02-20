#pragma once

#include "application.h"

#include <puremvc/puremvc.h>

#define VERSION "EmployeeAdmin Version 1.0.0"
#define STARTUP "startup"
#define SERVICE "service"
#define SERVICE_RESULT "service_result"
#define SERVICE_FAULT "service_fault"

struct ApplicationFacade {
    struct IFacade *super;

    void (*startup)(const struct ApplicationFacade *self, struct Stage *stage);
};

struct IFacade *application_facade_getInstance(struct FacadeMap **facadeMap, const char *key);

struct ApplicationFacade *application_facade_bind(struct ApplicationFacade *facade, struct IFacade *super);
