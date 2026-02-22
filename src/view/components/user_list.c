#include "user_list.h"

#include "employee_admin/i_user_list.h"

static struct IUserList delegate;

static GtkWidget *column_view;

void user_list_set_delegate(struct IUserList _delegate) {
    delegate = _delegate;
}

static void setup_cb(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_list_item_set_child(GTK_LIST_ITEM(list_item), label);
}

static void bind_username_cb(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkWidget *label = gtk_list_item_get_child(list_item);
    const struct UserVO *user = gtk_list_item_get_item(list_item);
    gtk_label_set_text(GTK_LABEL(label), user->username);

    // GtkSignalListItemFactory *factory = gtk_signal_list_item_factory_new();
    // g_signal_connect(factory, "setup", G_CALLBACK(setup_cb), NULL);
    // g_signal_connect(factory, "bind", G_CALLBACK(bind_username_cb), NULL);
    // GtkColumnViewColumn *column = gtk_column_view_column_new("Username", GTK_LIST_ITEM_FACTORY(factory));
    // gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), column);
}

void user_list_run() {
    if (delegate.list) {
        struct UserVO *users[MAX_USERS];
        const size_t count = delegate.list(delegate.context, users, MAX_USERS);

        GListStore *store = g_list_store_new(G_TYPE_PTR_ARRAY);
        for (size_t i = 0; i < count; i++) {
            g_list_store_append(store, &users[i]);
        }

        GtkSingleSelection *selection = gtk_single_selection_new(G_LIST_MODEL(store));
        gtk_column_view_set_model(GTK_COLUMN_VIEW(column_view), GTK_SELECTION_MODEL(selection));

        g_object_unref(selection);
        g_object_unref(store);
    }
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

    // Add margins directly on the label
    gtk_widget_set_margin_start(label, 12);
    gtk_widget_set_margin_end(label, 12);
    gtk_widget_set_margin_top(label, 12);
    gtk_widget_set_margin_bottom(label, 0);

    return label;
}

static GtkWidget *body() {
    GtkWidget *scroller = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroller, TRUE);
    gtk_widget_set_hexpand(scroller, TRUE);

    column_view = gtk_column_view_new(NULL);

    const char *titles[] = { "Username", "First Name", "Last Name", "Email", "Department"};
    const int count = sizeof(titles) / sizeof(titles[0]);

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
