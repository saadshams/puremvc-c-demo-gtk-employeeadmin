#include "user_role.h"

static GtkWidget *component();
static GtkWidget *footer();

GtkWidget *user_role() {
    GtkWidget *frame = gtk_frame_new("User Role");
    GtkWidget *label = gtk_frame_get_label_widget(GTK_FRAME(frame));
    if (label) {
        gtk_widget_add_css_class(label, "title-4");
        gtk_widget_set_halign(label, GTK_ALIGN_START);
    }

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);

    gtk_widget_set_margin_top(box, 15);
    gtk_widget_set_margin_end(box, 15);
    gtk_widget_set_margin_bottom(box, 10);
    gtk_widget_set_margin_start(box, 15);

    gtk_box_append(GTK_BOX(box), component());
    gtk_box_append(GTK_BOX(box), footer());

    gtk_frame_set_child(GTK_FRAME(frame), box);

    return frame;
}

static GtkWidget *component() {
    GtkWidget *list = gtk_list_box_new();
    gtk_widget_set_vexpand(list, TRUE);

    const char *roles[] = { "Admin", "Role", "User", "Manager", "Guest" };
    const int count = sizeof(roles) / sizeof(roles[0]);

    for(int i=0; i<count; i++) {
        GtkWidget *label = gtk_label_new(roles[i]);
        gtk_widget_set_halign(label, GTK_ALIGN_START);
        gtk_list_box_append(GTK_LIST_BOX(list), label);
    }

    return list;
}

static GtkWidget *footer() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    gtk_widget_set_margin_top(box, 5);

    GtkWidget *dropdown = gtk_drop_down_new_from_strings((const char*[]) {"Admin", "Editor", NULL});
    gtk_widget_set_hexpand(dropdown, TRUE);
    gtk_widget_set_halign(dropdown, GTK_ALIGN_FILL);

    GtkWidget *add = gtk_button_new_with_label("Add");
    gtk_widget_set_sensitive(add, FALSE);
    GtkWidget *remove = gtk_button_new_with_label("Remove");
    gtk_widget_set_sensitive(remove, FALSE);

    gtk_box_append(GTK_BOX(box), dropdown);
    gtk_box_append(GTK_BOX(box), add);
    gtk_box_append(GTK_BOX(box), remove);

    return box;
}
