#include "user_form.h"

#include "model/enum/dept_enum.h"
#include "employee_admin/i_user_form.h"

#pragma region State

static struct UserVO *user;
static struct IUserForm delegate;

#pragma endregion

#pragma region UI Components

static GtkWidget *first, *last, *email, *username, *password, *confirm, *department;

#pragma endregion

#pragma region Signal Handlers

// Signal handlers
static void on_update(GtkButton *button, gpointer data) {
    (void) button; (void) data;

    if (!user) return;

    g_free(user->first);
    g_free(user->last);
    g_free(user->email);
    g_free(user->username);
    g_free(user->password);

    user->first = g_strdup(gtk_editable_get_text(GTK_EDITABLE(first)));
    user->last = g_strdup(gtk_editable_get_text(GTK_EDITABLE(last)));
    user->email = g_strdup(gtk_editable_get_text(GTK_EDITABLE(email)));
    user->username = g_strdup(gtk_editable_get_text(GTK_EDITABLE(username)));
    user->password = g_strdup(gtk_editable_get_text(GTK_EDITABLE(password)));

    guint position = gtk_drop_down_get_selected(GTK_DROP_DOWN(department));
    user->department = position >= DEPT_COMBO_LIST_COUNT ? DEPT_NONE_SELECTED : DEPT_COMBO_LIST[position];

    if (user->validate(username, password, confirm, department))
        delegate.on_update(delegate.context, user);
}

static void on_cancel(GtkButton *button, gpointer data) {

}

static gboolean on_close_request(GtkWindow *window, gpointer data) {
    (void) window; (void) data;
    return FALSE;
}

#pragma endregion

#pragma region Layout

static GtkWidget *header(void) {
    GtkWidget *label = gtk_label_new("User Profile");
    gtk_widget_add_css_class(label, "title-4");
    gtk_widget_set_halign(label, GTK_ALIGN_START);

    gtk_widget_set_margin_start(label, 12);
    gtk_widget_set_margin_end(label, 0);
    gtk_widget_set_margin_top(label, 8);
    gtk_widget_set_margin_bottom(label, 0);

    return label;
}

static GtkWidget *body(void) {
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 12);

    const char *fields[] = {"First Name", "Last Name", "Email", "Username *", "Password *", "Confirm Password *"};
    GtkWidget **widgets[] = { &first, &last, &email, &username, &password, &confirm };
    const int count = sizeof(fields) / sizeof(fields[0]);

    for(int i = 0; i < count; i++) {
        GtkWidget *label = gtk_label_new(fields[i]);
        gtk_widget_set_hexpand(label, TRUE);
        gtk_widget_set_halign(label, GTK_ALIGN_END);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i, 1, 1);

        *widgets[i] = gtk_entry_new();
        gtk_widget_set_hexpand(*widgets[i], TRUE);
        gtk_widget_set_halign(*widgets[i], GTK_ALIGN_FILL);
        gtk_grid_attach(GTK_GRID(grid), *widgets[i], 1, i, 2, 1);
    }

    gtk_entry_set_visibility(GTK_ENTRY(password), FALSE);
    gtk_entry_set_visibility(GTK_ENTRY(confirm), FALSE);

    GtkWidget *label = gtk_label_new("Department *");
    gtk_widget_set_halign(label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 6, 1, 1);

    GtkStringList *values = gtk_string_list_new(NULL);
    for (size_t i = 0; i < DEPT_COMBO_LIST_COUNT; i++) {
        gtk_string_list_append(values, dept_to_string(DEPT_COMBO_LIST[i]));
    }

    department = gtk_drop_down_new(G_LIST_MODEL(values), NULL);
    g_object_unref(values);
    gtk_widget_set_hexpand(department, TRUE);
    gtk_widget_set_halign(department, GTK_ALIGN_FILL);
    gtk_grid_attach(GTK_GRID(grid), department, 1, 6, 2, 1);

    return grid;
}

static GtkWidget *footer(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_widget_set_margin_top(box, 5);

    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_hexpand(spacer, TRUE);

    GtkWidget *update = gtk_button_new_with_label("Update Profile");
    gtk_widget_add_css_class(update, "suggested-action");
    g_signal_connect(update, "clicked", G_CALLBACK(on_update), NULL);

    GtkWidget *cancel = gtk_button_new_with_label("Cancel");
    g_signal_connect(cancel, "clicked", G_CALLBACK(on_cancel), NULL);
    gtk_widget_set_margin_start(cancel, 5);
    gtk_widget_add_css_class(cancel, "destructive-action");

    gtk_box_append(GTK_BOX(box), spacer);
    gtk_box_append(GTK_BOX(box), update);
    gtk_box_append(GTK_BOX(box), cancel);

    return box;
}

#pragma endregion

#pragma region Public API

GtkWidget *user_form_layout(GtkWidget *window) {
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

void user_form_reset(void) {
    user = NULL;

    gtk_editable_set_text(GTK_EDITABLE(first), "");
    gtk_editable_set_text(GTK_EDITABLE(last), "");
    gtk_editable_set_text(GTK_EDITABLE(email), "");
    gtk_editable_set_text(GTK_EDITABLE(username), "");
    gtk_widget_set_sensitive(username, TRUE);
    gtk_editable_set_text(GTK_EDITABLE(password), "");
    gtk_editable_set_text(GTK_EDITABLE(confirm), "");

    gtk_drop_down_set_selected(GTK_DROP_DOWN(department), 0);
}

void user_form_set_user(struct UserVO *_user) {
    user = _user;

    gtk_editable_set_text(GTK_EDITABLE(first), user_vo_get_first(user));
    gtk_editable_set_text(GTK_EDITABLE(last), user_vo_get_last(user));
    gtk_editable_set_text(GTK_EDITABLE(email), user_vo_get_email(user));
    gtk_editable_set_text(GTK_EDITABLE(username), user_vo_get_username(user));
    gtk_widget_set_sensitive(username, FALSE);
    gtk_editable_set_text(GTK_EDITABLE(password), user->password ? user->password : "");
    gtk_editable_set_text(GTK_EDITABLE(confirm), user->password ? user->password : "");

    guint position = 0;
    for (guint i = 0; i < DEPT_COMBO_LIST_COUNT; i++) {
        if (DEPT_COMBO_LIST[i] == user->department) {
            position = i;
            break;
        }
    }
    gtk_drop_down_set_selected(GTK_DROP_DOWN(department), position);
}

void user_form_set_delegate(struct IUserForm _delegate) {
    delegate = _delegate;
}

#pragma endregion
