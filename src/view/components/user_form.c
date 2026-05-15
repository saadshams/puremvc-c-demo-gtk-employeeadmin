#include "user_form.h"

#include "employee_admin/i_user_form.h"
#include "model/enum/dept_enum.h"
#include "model/valueObject/user_vo.h"

static GtkWidget *first, *last, *email, *username, *password, *confirm, *department;
static const struct UserVO *current_user;
struct IUserForm delegate;

// Signal handlers
static gboolean on_close_request(GtkWindow *window, gpointer data) {
    (void) window;
    (void) data;

    return FALSE;
}

// Layout
static GtkWidget *header() {
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

    GtkWidget *dept_label = gtk_label_new("Department *");
    gtk_widget_set_halign(dept_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), dept_label, 0, 6, 1, 1);

    GtkStringList *departments = gtk_string_list_new(NULL);
    for (size_t i = 0; i < DEPT_COMBO_LIST_COUNT; i++) {
        gtk_string_list_append(departments, dept_to_string(DEPT_COMBO_LIST[i]));
    }

    GtkWidget *dropdown = gtk_drop_down_new(G_LIST_MODEL(departments), NULL);
    g_object_unref(departments);
    gtk_widget_set_hexpand(dropdown, TRUE);
    gtk_widget_set_halign(dropdown, GTK_ALIGN_FILL);
    gtk_grid_attach(GTK_GRID(grid), dropdown, 1, 6, 2, 1);

    return grid;
}

static GtkWidget *footer() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_widget_set_margin_top(box, 5);

    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_hexpand(spacer, TRUE);

    GtkWidget *update = gtk_button_new_with_label("Update Profile");
    gtk_widget_add_css_class(update, "suggested-action");

    GtkWidget *cancel = gtk_button_new_with_label("Cancel");
    gtk_widget_set_margin_start(cancel, 5);
    gtk_widget_add_css_class(cancel, "destructive-action");

    gtk_box_append(GTK_BOX(box), spacer);
    gtk_box_append(GTK_BOX(box), update);
    gtk_box_append(GTK_BOX(box), cancel);

    return box;
}

GtkWidget *user_form_init(GtkWidget *window) {
    g_signal_connect(GTK_WINDOW(window), "close-request", G_CALLBACK(on_close_request), NULL);

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

void user_form_set_user(const struct UserVO *user) {
    current_user = user;

    gtk_editable_set_text(GTK_EDITABLE(first), user_vo_get_first(user));
    gtk_editable_set_text(GTK_EDITABLE(last), user_vo_get_last(user));
    gtk_editable_set_text(GTK_EDITABLE(email), user_vo_get_email(user));
    gtk_editable_set_text(GTK_EDITABLE(username), user_vo_get_username(user));
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
