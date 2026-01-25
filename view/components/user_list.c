#include "user_list.h"

static GtkWidget *header();
static GtkWidget *component();
static GtkWidget *footer();

GtkWidget *user_list() {
    GtkWidget *frame = gtk_frame_new("Users");
    GtkWidget *label = gtk_frame_get_label_widget(GTK_FRAME(frame));
    if (label) {
        gtk_widget_add_css_class(label, "title-4");
        gtk_widget_set_halign(label, GTK_ALIGN_START);
    }

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_add_css_class(box, "panel");

    // Add components inside the box
    gtk_box_append(GTK_BOX(box), component());
    gtk_box_append(GTK_BOX(box), footer());

    gtk_frame_set_child(GTK_FRAME(frame), box); // Set the box as the frame's child

    return frame;
}

GtkWidget *user_list2() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_add_css_class(box, "panel");

    gtk_box_append(GTK_BOX(box), header());
    gtk_box_append(GTK_BOX(box), component());
    gtk_box_append(GTK_BOX(box), footer());

    return box;
}

static GtkWidget *header2(void){
    GtkWidget *frame = gtk_frame_new("Users");

    GtkWidget *label = gtk_frame_get_label_widget(GTK_FRAME(frame));
    gtk_widget_add_css_class(label, "title-4");
    gtk_widget_set_halign(label, GTK_ALIGN_START);

    return frame;
}

static GtkWidget *header() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    GtkWidget *label = gtk_label_new("Users");
    gtk_widget_add_css_class(label, "panel-title");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(box), label);

    return box;
}

static GtkWidget *component() {
    GtkWidget *scroller = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroller, TRUE);

    GtkWidget *column = gtk_column_view_new(NULL);

    gtk_column_view_append_column(GTK_COLUMN_VIEW(column), gtk_column_view_column_new("Username", gtk_signal_list_item_factory_new()));

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroller), column);

    return scroller;
}

static GtkWidget *footer() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_hexpand(spacer, TRUE);

    GtkWidget *delete = gtk_button_new_with_label("Delete");
    gtk_widget_add_css_class(delete, "destructive-action");

    GtkWidget *new = gtk_button_new_with_label("New");
    gtk_widget_add_css_class(new, "suggested-action");

    gtk_box_append(GTK_BOX(box), spacer);
    gtk_box_append(GTK_BOX(box), delete);
    gtk_box_append(GTK_BOX(box), new);

    return box;
}
