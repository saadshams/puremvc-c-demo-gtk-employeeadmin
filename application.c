#include "application.h"
#include "view/components/user_list.h"
#include "view/components/user_form.h"
#include "view/components/user_role.h"

static void activate(GtkApplication *app, gpointer data);
static GtkWidget *layout();
static GtkWidget *master();
static GtkWidget *detail();

GtkApplication *startup(void) {
    GtkApplication *app = gtk_application_new("org.puremvc.employeeadmin", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    return app;
}

static void activate(GtkApplication *app, gpointer data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Employee Admin");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    gtk_window_set_child(GTK_WINDOW(window), layout());
    gtk_window_present(GTK_WINDOW(window));
}

static GtkWidget *layout() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_box_append(GTK_BOX(box), master());
    gtk_box_append(GTK_BOX(box), detail());
    return box;
}

static GtkWidget *master() {
    return user_list();
}

static GtkWidget *detail() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);

    GtkWidget *form = user_form();
    GtkWidget *role = user_role();

    gtk_widget_set_hexpand(form, TRUE);
    gtk_widget_set_hexpand(role, TRUE);

    gtk_box_append(GTK_BOX(box), form);
    gtk_box_append(GTK_BOX(box), role);

    return box;
}
