#include "user_role.h"

static GtkWidget *header();
static GtkWidget *component();
static GtkWidget *footer();

GtkWidget *user_role() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_append(GTK_BOX(box), header());
    gtk_box_append(GTK_BOX(box), component());
    gtk_box_append(GTK_BOX(box), footer());
    return box;
}

static GtkWidget *header() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    GtkWidget *label = gtk_label_new("User Role");
    gtk_widget_add_css_class(label, "title-3");
    gtk_box_append(GTK_BOX(box), label);
    return box;
}

static GtkWidget *component() {
    GtkWidget *list = gtk_list_box_new();
    gtk_list_box_append(GTK_LIST_BOX(list), gtk_label_new("Admin"));
    gtk_list_box_append(GTK_LIST_BOX(list), gtk_label_new("Role"));
    return list;
}

static GtkWidget *footer() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    GtkWidget *dropdown = gtk_drop_down_new_from_strings((const char*[]) {"Admin", "Editor", NULL});
    GtkWidget *add = gtk_button_new_with_label("Add");
    GtkWidget *remove = gtk_button_new_with_label("Remove");

    gtk_box_append(GTK_BOX(box), dropdown);
    gtk_box_append(GTK_BOX(box), add);
    gtk_box_append(GTK_BOX(box), remove);

    return box;
}
