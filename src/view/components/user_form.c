#include "user_form.h"

#include "model/enum/dept_enum.h"

static GtkWidget *header();
static GtkWidget *body();
static GtkWidget *footer();

GtkWidget *user_form_init() {
    GtkWidget *frame = gtk_frame_new(NULL);

    gtk_frame_set_label_widget(GTK_FRAME(frame), header()); // Set Header

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
    GtkWidget *label = gtk_label_new("User Profile");
    gtk_widget_add_css_class(label, "title-4");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    return label;
}

static GtkWidget *body(void) {
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 12);

    const char *fields[] = {"First Name", "Last Name", "Email", "Username *", "Password *", "Confirm Password *"};
    const int count = sizeof(fields) / sizeof(fields[0]);

    for(int i=0; i<count; i++) {
        GtkWidget *label = gtk_label_new(fields[i]);
        gtk_widget_set_hexpand(label, TRUE);
        gtk_widget_set_halign(label, GTK_ALIGN_END);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i, 1, 1);

        GtkWidget *entry = gtk_entry_new();
        gtk_widget_set_hexpand(entry, TRUE);
        gtk_widget_set_halign(entry, GTK_ALIGN_FILL);
        gtk_grid_attach(GTK_GRID(grid), entry, 1, i, 2, 1);
    }

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Department *"), 0, 6, 1, 1);

    GtkStringList *departments = gtk_string_list_new(NULL);
    for (size_t i = 0; i < DEPT_COMBO_LIST_COUNT; i++)
        gtk_string_list_append(departments, dept_to_string(DEPT_COMBO_LIST[i]));

    GtkWidget *dropdown = gtk_drop_down_new(NULL, NULL);
    gtk_drop_down_set_model(GTK_DROP_DOWN(dropdown), G_LIST_MODEL(departments));
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
