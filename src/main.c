#include "application.h"
#include "application_facade.h"

#include <puremvc/puremvc.h>
#include <gtk/gtk.h>

int main(const int argc, char **argv) {
    struct IFacade *super = application_facade_getInstance("EmployeeAdmin");
    super->initialize_facade(super);

    struct ApplicationFacade *facade = application_facade_extend(&(struct ApplicationFacade){}, super);
    facade->startup(facade);

    GtkApplication *app = get_app(facade);
    const int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    puremvc_facade_remove_facade("EmployeeAdmin");

    return status;
}
