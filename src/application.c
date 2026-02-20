#include "application.h"

#include "application_facade.h"
#include "view/components/user_form.h"
#include "view/components/user_list.h"
#include "view/components/user_role.h"

static void activate(GtkApplication *app, gpointer data);
static GtkWidget *layout(gpointer data);
static GtkWidget *master(gpointer data);
static GtkWidget *detail(gpointer data);

GtkApplication *getApp(gpointer data) {
    GtkApplication *app = gtk_application_new("org.puremvc.employeeadmin", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), data);
    return app;
}

static void activate(GtkApplication *app, gpointer data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Employee Admin");
    gtk_window_set_default_size(GTK_WINDOW(window), 750, 650);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    gtk_window_set_child(GTK_WINDOW(window), layout(data));
    gtk_window_present(GTK_WINDOW(window));
}

static GtkWidget *layout(gpointer data) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);

    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_end(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    gtk_widget_set_margin_start(box, 20);

    GtkWidget *master_widget = master(data);
    GtkWidget *detail_widget = detail(data);

    gtk_widget_set_vexpand(master_widget, TRUE);
    gtk_widget_set_vexpand(detail_widget, FALSE);

    gtk_box_append(GTK_BOX(box), master_widget);
    gtk_box_append(GTK_BOX(box), detail_widget);
    return box;
}

static GtkWidget *master(gpointer data) {
    const struct ApplicationFacade *facade = data;
    GtkWidget *user = user_list_init();
    facade->registerComponent(facade, "UserListMediator", user);
    return user;
}

static GtkWidget *detail(gpointer data) {
    const struct ApplicationFacade *facade = data;

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 12);

    GtkWidget *form = user_form_init();
    facade->registerComponent(facade, "UserFormMediator", form);

    GtkWidget *role = user_role_init();
    facade->registerComponent(facade, "UserRoleMediator", role);

    gtk_widget_set_hexpand(form, TRUE);
    gtk_widget_set_hexpand(role, TRUE);

    gtk_grid_attach(GTK_GRID(grid), form, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), role, 1, 0, 1, 1);

    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    return grid;
}
