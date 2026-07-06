#include "application.h"
#include "application_facade.h"

#include <puremvc/puremvc.h>
#include <gtk/gtk.h>

int main(const int argc, char **argv) {
    struct ApplicationFacade *facade = application_facade_get_instance("EmployeeAdmin")->sub;
    facade->startup(facade);

    GtkApplication *app = application_new(facade);
    const int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    puremvc_facade_remove("EmployeeAdmin");
    return status;
}
