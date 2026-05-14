#include "user_list.h"
#include "employee_admin/i_user_list.h"

static struct IUserList delegate;
static GtkWidget *column_view;
static GtkSingleSelection *selection;
static GtkWidget *delete;

// signal handlers
static void on_select(GtkSingleSelection *sel, GParamSpec *pspec, gpointer data) {
    guint position = gtk_single_selection_get_selected(sel);
    gtk_widget_set_sensitive(delete, position != GTK_INVALID_LIST_POSITION);

    if (position == GTK_INVALID_LIST_POSITION) return;

    const struct UserVO *user = ((UserObject *) gtk_single_selection_get_selected_item(sel))->user;
    g_print("Selected user: %s, %s %s, %s, dept=%d\n", user->username, user->first, user->last, user->email, user->department);
}

static void on_delete(GtkButton *button, gpointer data) {
    UserObject *object = gtk_single_selection_get_selected_item(selection);

    const struct UserVO *user = object->user;
    g_print("Delete clicked for user: %s, %s %s, %s, dept=%d\n", user->username, user->first, user->last, user->email, user->department);
}

static void on_new(GtkButton *button, gpointer data) {
    gtk_single_selection_set_selected(selection, GTK_INVALID_LIST_POSITION);
    g_print("New clicked: selection cleared\n");
}

// UI helpers
static void setup_label(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkWidget *label = gtk_label_new("");
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_list_item_set_child(list_item, label);
}

static void bind_label(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkWidget *label = gtk_list_item_get_child(list_item);
    UserObject *object = gtk_list_item_get_item(list_item);

    if (object == NULL || object->user == NULL)
        return gtk_label_set_text(GTK_LABEL(label), "");

    const char *(*getter)(const struct UserVO *user) = data;
    gtk_label_set_text(GTK_LABEL(label), getter(object->user));
}

static GtkColumnViewColumn *create_text_column(const char *title, const char *(*getter)(const struct UserVO *user)) {
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();

    g_signal_connect(factory, "setup", G_CALLBACK(setup_label), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_label), getter);

    GtkColumnViewColumn *column = gtk_column_view_column_new(title, factory);
    gtk_column_view_column_set_expand(column, TRUE);

    return column;
}

static GtkWidget *header() {
    GtkWidget *label = gtk_label_new("Users");
    gtk_widget_add_css_class(label, "title-4");
    gtk_widget_set_halign(label, GTK_ALIGN_START);

    gtk_widget_set_margin_start(label, 12);
    gtk_widget_set_margin_end(label, 0);
    gtk_widget_set_margin_top(label, 8);
    gtk_widget_set_margin_bottom(label, 0);

    return label;
}

static GtkWidget *body() {
    GtkWidget *scroller = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroller, TRUE);
    gtk_widget_set_hexpand(scroller, TRUE);

    column_view = gtk_column_view_new(NULL);

    gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), create_text_column("Username", user_vo_get_username));
    gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), create_text_column("First Name", user_vo_get_first));
    gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), create_text_column("Last Name", user_vo_get_last));
    gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), create_text_column("Email", user_vo_get_email));
    gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), create_text_column("Department", user_vo_get_department));

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroller), column_view);

    return scroller;
}

static GtkWidget *footer() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    gtk_widget_set_margin_top(box, 5);

    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_hexpand(spacer, TRUE);

    delete = gtk_button_new_with_label("Delete");
    gtk_widget_add_css_class(delete, "destructive-action");
    gtk_widget_set_sensitive(delete, FALSE);
    g_signal_connect(delete, "clicked", G_CALLBACK(on_delete), NULL);

    GtkWidget *new = gtk_button_new_with_label("New");
    gtk_widget_add_css_class(new, "suggested-action");
    g_signal_connect(new, "clicked", G_CALLBACK(on_new), NULL);

    gtk_box_append(GTK_BOX(box), spacer);
    gtk_box_append(GTK_BOX(box), delete);
    gtk_box_append(GTK_BOX(box), new);

    return box;
}

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

void user_list_run() {
    if (delegate.list) {
        struct UserVO *users[MAX_USERS] = {0};
        const size_t count = delegate.list(delegate.context, users, MAX_USERS);

        GListStore *store = g_list_store_new(user_object_get_type());
        for (size_t i = 0; i < count; i++) {
            UserObject *object = user_object_new(users[i]);
            g_list_store_append(store, object);
            g_object_unref(object);
        }

        selection = gtk_single_selection_new(G_LIST_MODEL(store));
        gtk_single_selection_set_autoselect(selection, FALSE);
        gtk_single_selection_set_can_unselect(selection, TRUE);
        gtk_single_selection_set_selected(selection, GTK_INVALID_LIST_POSITION);

        g_signal_connect(selection, "notify::selected", G_CALLBACK(on_select), NULL);
        gtk_column_view_set_model(GTK_COLUMN_VIEW(column_view), GTK_SELECTION_MODEL(selection));
    }
}

void user_list_set_delegate(struct IUserList _delegate) {
    delegate = _delegate;
}
