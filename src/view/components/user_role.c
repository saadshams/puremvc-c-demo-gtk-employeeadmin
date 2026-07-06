#include "user_role.h"

#include "model/enum/role_enum.h"
#include "employee_admin/i_user_role.h"

#pragma region State

static struct IUserRole delegate;

#pragma endregion

#pragma region Signal Handlers

static gboolean on_close_request(GtkWindow *window, gpointer data) {
    (void) window; (void) data;
    return FALSE;
}

#pragma endregion

#pragma region Layout

static GtkWidget *header(void) {
    GtkWidget *label = gtk_label_new("User Role");
    gtk_widget_add_css_class(label, "title-4");
    gtk_widget_set_halign(label, GTK_ALIGN_START);

    gtk_widget_set_margin_start(label, 12);
    gtk_widget_set_margin_end(label, 0);
    gtk_widget_set_margin_top(label, 8);
    gtk_widget_set_margin_bottom(label, 0);

    return label;
}

static GtkWidget *body(void) {
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

static GtkWidget *footer(void) {
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

#pragma endregion

#pragma region Public API

GtkWidget *user_role_layout(GtkWidget *window) {
    g_signal_connect(GTK_WINDOW(window), "close-request", G_CALLBACK(on_close_request), NULL);

    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_frame_set_label_widget(GTK_FRAME(frame), header());

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_margin_start(box, 15);
    gtk_widget_set_margin_end(box, 15);
    gtk_widget_set_margin_top(box, 15);
    gtk_widget_set_margin_bottom(box, 10);

    gtk_box_append(GTK_BOX(box), body());
    gtk_box_append(GTK_BOX(box), footer());

    gtk_frame_set_child(GTK_FRAME(frame), box);

    return frame;
}

void user_role_set_delegate(struct IUserRole _delegate) {
    delegate = _delegate;
}

#pragma endregion
