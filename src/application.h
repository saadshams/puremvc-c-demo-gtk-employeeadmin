#pragma once

#include "application_facade.h"

#include <gtk/gtk.h>

GtkApplication *application_new(struct ApplicationFacade *data);
