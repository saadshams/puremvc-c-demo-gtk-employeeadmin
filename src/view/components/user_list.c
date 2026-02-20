#include "user_list.h"

#include "employee_admin/i_user_list.h"

struct IUserList delegate;

void user_list_set_delegate(struct IUserList _delegate) {
    delegate = _delegate;
}

static GtkWidget *header();
static GtkWidget *body();
static GtkWidget *footer();

GtkWidget *user_list_init() {
    GtkWidget *frame = gtk_frame_new(NULL);

    gtk_frame_set_label_widget(GTK_FRAME(frame), header()); // Header

    GtkWidget *content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6); // Layout Container

    gtk_widget_set_margin_start(content_area, 15);
    gtk_widget_set_margin_end(content_area, 15);
    gtk_widget_set_margin_top(content_area, 15);
    gtk_widget_set_margin_bottom(content_area, 10);

    gtk_box_append(GTK_BOX(content_area), body()); // Assembly
    gtk_box_append(GTK_BOX(content_area), footer());

    gtk_frame_set_child(GTK_FRAME(frame), content_area);

    return frame;
}

static GtkWidget *header() {
    GtkWidget *label = gtk_label_new("Users");
    gtk_widget_add_css_class(label, "title-4");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    // Wrap in a box if you need specific padding/margins for the title
    return label;
}

static GtkWidget *body() {
    GtkWidget *scroller = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroller, TRUE);
    gtk_widget_set_hexpand(scroller, TRUE);

    GtkWidget *column_view = gtk_column_view_new(NULL);

    const char *titles[] = { "Username", "First Name", "Last Name", "Email", "Department"};
    int count = sizeof(titles) / sizeof(titles[0]);

    for(int i=0; i<count; i++) {
        GtkColumnViewColumn *column = gtk_column_view_column_new(titles[i], gtk_signal_list_item_factory_new());
        gtk_column_view_column_set_expand(column, TRUE);
        gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), column);
    }

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroller), column_view);

    return scroller;
}

static GtkWidget *footer() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    gtk_widget_set_margin_top(box, 5);

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
