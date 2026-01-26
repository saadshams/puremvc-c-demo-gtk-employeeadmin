#include <gtk/gtk.h>
#include "application.h"

int main(int argc, char **argv) {
    GtkApplication *app = getApp();

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
