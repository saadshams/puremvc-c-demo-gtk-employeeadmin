#include "user_list.h"

#pragma region State

static GListStore *store;
static GtkSingleSelection *selection;
static struct IUserList delegate;

#pragma endregion

#pragma region Widgets

static GtkWidget *column_view;
static GtkWidget *delete;

#pragma endregion

#pragma region Signal Handlers

static void on_new(GtkButton *button, gpointer data) {
    (void) button; (void) data;
    gtk_single_selection_set_selected(selection, GTK_INVALID_LIST_POSITION);
    delegate.on_new(delegate.context, NULL);
}

static void on_delete(GtkButton *button, gpointer data) {
    (void) button; (void) data;
    const UserVOObject *object = gtk_single_selection_get_selected_item(selection);
    delegate.on_delete(delegate.context, object);
}

static void on_select(GtkSingleSelection *sel, GParamSpec *pspec, gpointer data) {
    (void) pspec; (void) data;
    const guint position = gtk_single_selection_get_selected(sel);
    gtk_widget_set_sensitive(delete, position != GTK_INVALID_LIST_POSITION);
    if (position == GTK_INVALID_LIST_POSITION) return;

    const UserVOObject *object = gtk_single_selection_get_selected_item(sel);
    delegate.on_select(delegate.context, object);
}

static gboolean on_close_request(GtkWindow *window, gpointer data) {
    (void) window;
    (void) data;

    if (column_view)
        gtk_column_view_set_model(GTK_COLUMN_VIEW(column_view), NULL);

    g_clear_object(&selection);
    g_clear_object(&store);

    column_view = NULL;
    delete = NULL;

    return FALSE; // allow GTK to continue closing the window
}

#pragma endregion

#pragma region Column Factory

static void setup(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    (void) factory; (void) data;
    GtkWidget *label = gtk_label_new("");
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_list_item_set_child(list_item, label);
}

static void bind(const GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    (void) factory;

    GtkWidget *label = gtk_list_item_get_child(list_item);
    const UserVOObject *object = gtk_list_item_get_item(list_item);

    const char *(*getter)(const struct UserVO *user) = data;

    if (!object || !object->user || !getter) {
        gtk_label_set_text(GTK_LABEL(label), "");
        return;
    }

    gtk_label_set_text(GTK_LABEL(label), getter(object->user));
}

static GtkColumnViewColumn *create_text_column(const char *title, const char *(*getter)(const struct UserVO *user)) {
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();

    g_signal_connect(factory, "setup", G_CALLBACK(setup), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind), getter);

    GtkColumnViewColumn *column = gtk_column_view_column_new(title, factory);
    gtk_column_view_column_set_expand(column, TRUE);

    return column;
}

#pragma endregion

#pragma region Layout

static GtkWidget *header(void) {
    GtkWidget *label = gtk_label_new("Users");
    gtk_widget_add_css_class(label, "title-4");
    gtk_widget_set_halign(label, GTK_ALIGN_START);

    gtk_widget_set_margin_start(label, 12);
    gtk_widget_set_margin_end(label, 0);
    gtk_widget_set_margin_top(label, 8);
    gtk_widget_set_margin_bottom(label, 0);

    return label;
}

static GtkWidget *body(void) {
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

static GtkWidget *footer(void) {
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

#pragma endregion

#pragma region Public API

GtkWidget *user_list_layout(GtkWidget *window) {
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

void user_list_load_users(void) {
    store = delegate.find_all(delegate.context);

    selection = gtk_single_selection_new(G_LIST_MODEL(store));
    gtk_single_selection_set_autoselect(selection, FALSE);
    gtk_single_selection_set_can_unselect(selection, TRUE);
    gtk_single_selection_set_selected(selection, GTK_INVALID_LIST_POSITION);

    g_signal_connect(selection, "notify::selected", G_CALLBACK(on_select), NULL);
    gtk_column_view_set_model(GTK_COLUMN_VIEW(column_view), GTK_SELECTION_MODEL(selection));
}

void user_list_update_user(const struct UserVO *user) {
    const guint count = g_list_model_get_n_items(G_LIST_MODEL(store));
    for (guint i = 0; i < count; i++) {
        UserVOObject *object = g_list_model_get_item(G_LIST_MODEL(store), i);

        if (object && object->user == user) {
            UserVOObject *replacement = user_vo_object_new(user);

            g_list_store_splice(store, i, 1, (gpointer *) &replacement, 1);

            g_object_unref(replacement);
            g_object_unref(object);

            return;
        }

        if (object) {
            g_object_unref(object);
        }
    }
}

void user_list_set_delegate(struct IUserList _delegate) {
    delegate = _delegate;
}

#pragma endregion
