#include "application.h"

#include "view/components/user_form.h"
#include "view/components/user_role.h"

static void activate(GtkApplication *app, gpointer data);
static GtkWidget *layout(struct Stage *component);
static GtkWidget *master(struct Stage *stage);
static GtkWidget *detail(struct Stage *component);

GtkApplication *getApp(struct Stage *stage) {
    GtkApplication *app = gtk_application_new("org.puremvc.employeeadmin", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), stage);
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

static GtkWidget *layout(struct Stage *component) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);

    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_end(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    gtk_widget_set_margin_start(box, 20);

    GtkWidget *master_widget = master(component);
    GtkWidget *detail_widget = detail(component);

    gtk_widget_set_vexpand(master_widget, TRUE);
    gtk_widget_set_vexpand(detail_widget, FALSE);

    gtk_box_append(GTK_BOX(box), master_widget);
    gtk_box_append(GTK_BOX(box), detail_widget);
    return box;
}

static GtkWidget *master(struct Stage *stage) {
    stage->list.widget = user_list_init();
    return stage->list.widget;
}

static GtkWidget *detail(struct Stage *component) {
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 12);

    component->form.widget = user_form_init();
    component->role.widget = user_role_init();

    gtk_widget_set_hexpand(component->form.widget, TRUE);
    gtk_widget_set_hexpand(component->role.widget, TRUE);

    gtk_grid_attach(GTK_GRID(grid), component->form.widget, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), component->role.widget, 1, 0, 1, 1);

    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    return grid;
}
