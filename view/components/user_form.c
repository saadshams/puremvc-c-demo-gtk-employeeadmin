#include "user_form.h"

static GtkWidget *header();
static GtkWidget *component();
static GtkWidget *footer();

GtkWidget *user_form() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_box_append(GTK_BOX(box), header());
    gtk_box_append(GTK_BOX(box), component());
    gtk_box_append(GTK_BOX(box), footer());

    return box;
}

static GtkWidget *header() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    GtkWidget *label = gtk_label_new("Users");
    gtk_widget_add_css_class(box, "title-3");
    gtk_box_append(GTK_BOX(box), label);
    return box;
}

static GtkWidget *component() {
    GtkWidget *grid = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 12);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("First Name"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_entry_new(), 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Last Name"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_entry_new(), 1, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Email"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_entry_new(), 1, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Username *"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_entry_new(), 1, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Password *"), 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_entry_new(), 1, 4, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Confirm Password *"), 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_entry_new(), 1, 5, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Department *"), 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_drop_down_new_from_strings((const char *[]){ "--None Selected--", "Accounting", "Sales", "Plant", "Shipping", "Quality Control", NULL}), 1, 6, 1, 1);

    return grid;
}

static GtkWidget *footer() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    // gtk_widget_set_halign(box, GTK_ALIGN_END);
    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_hexpand(spacer, TRUE);

    GtkWidget *update = gtk_button_new_with_label("Update Profile");

    GtkWidget *cancel = gtk_button_new_with_label("Cancel");

    gtk_box_append(GTK_BOX(box), spacer);
    gtk_box_append(GTK_BOX(box), update);
    gtk_box_append(GTK_BOX(box), cancel);

    return box;
}
