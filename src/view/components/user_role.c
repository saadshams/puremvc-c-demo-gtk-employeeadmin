#include "user_role.h"

#include "model/enum/role_enum.h"

struct IUserRole delegate;

static GtkWidget *header();
static GtkWidget *body();
static GtkWidget *footer();

void user_role_set_delegate(struct IUserRole _delegate) {
    delegate = _delegate;
}

GtkWidget *user_role_init() {
    GtkWidget *frame = gtk_frame_new(NULL);

    gtk_frame_set_label_widget(GTK_FRAME(frame), header()); // Header

    GtkWidget *content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);  // Layout Container
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
    GtkWidget *label = gtk_label_new("User Role");
    gtk_widget_add_css_class(label, "title-4");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    return label;
}

static GtkWidget *body() {
    GtkWidget *list = gtk_list_box_new();
    gtk_widget_set_vexpand(list, TRUE);

    const char *roles[] = { "Admin" };
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

    GtkStringList *roles = gtk_string_list_new(NULL);
    for (size_t i = 0; i < ROLE_COMBO_LIST_COUNT; i++)
        gtk_string_list_append(roles, role_to_string(ROLE_COMBO_LIST[i]));

    GtkWidget *dropdown = gtk_drop_down_new(NULL, NULL);
    gtk_drop_down_set_model(GTK_DROP_DOWN(dropdown), G_LIST_MODEL(roles));

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
