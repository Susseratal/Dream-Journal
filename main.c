#include <stdio.h>
#include <gtk/gtk.h>

int winWidth = 1280;
int winHeight = 720;

int subWinOpen = 0;

GtkWidget *txt;
GtkTextBuffer *buffer;

void endProgram(GtkWidget *win, gpointer ptr) {
    if(subWinOpen == 0) {
        gtk_main_quit();
    }
}

void closeSubwin(GtkWidget *widget, gpointer ptr) {
    subWinOpen = 0;
    GtkWidget* subWin = GTK_WIDGET(ptr);
    gtk_widget_destroy(subWin);
}

void dreamTypeChanged(GtkWidget *wid, gpointer ptr) {
    char* selected = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(wid));
    printf("The dream type was %s\n", selected);
}

void newWin(GtkWidget *win, gpointer ptr) {
    GtkWidget *subWin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(subWin), winWidth, winHeight); // set width and height
    gtk_window_set_resizable(GTK_WINDOW(subWin), FALSE); // set non-resizable
    gtk_window_set_title(GTK_WINDOW(subWin), "New Dream Journal Entry");

    GtkWidget *closeBtn = gtk_button_new_with_label("Quit"); // Create a button with a label

    g_signal_connect(closeBtn, "clicked", G_CALLBACK(closeSubwin), subWin); 
    g_signal_connect(subWin, "delete_event", G_CALLBACK(closeSubwin), subWin);
    subWinOpen = 1;

    GtkWidget *dreamType = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(dreamType), "Good dream");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(dreamType), "No dream");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(dreamType), "Bad dream");
    gtk_combo_box_set_active(GTK_COMBO_BOX(dreamType), 0);
    g_signal_connect(dreamType, "changed", G_CALLBACK(dreamTypeChanged), NULL);

    GtkWidget *drunkCheck = gtk_check_button_new_with_label("Drunk");
    GtkWidget *insomniaCheck = gtk_check_button_new_with_label("Insomnia");

    txt = gtk_text_view_new();
    GtkWidget *blank = gtk_label_new(""); // blanking block
    gtk_widget_set_hexpand(GTK_WIDGET(blank), TRUE); // set the blanking box to use as much width of the screen as possible
    gtk_widget_set_vexpand(GTK_WIDGET(txt), TRUE); // set the text box to use as much height of the screen as possible
    gtk_widget_set_valign(GTK_WIDGET(txt), GTK_ALIGN_FILL);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(txt), 5);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(txt), 5);
    // gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(txt), GTK_TEXT_WINDOW_WIDGET, 5);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(txt), GTK_WRAP_WORD);
    gtk_scrollable_set_hadjustment(GTK_SCROLLABLE(txt), NULL);
    // gtk_entry_set_placeholder_text(GTK_ENTRY(txt), "What did you dream about?"); 

    GtkWidget *grd = gtk_grid_new(); // create a new grid

    // attach everything to the grid
    gtk_grid_attach(GTK_GRID(grd), dreamType, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), drunkCheck, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), insomniaCheck, 4, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grd), txt, 1, 1, 6, 1);

    gtk_grid_attach(GTK_GRID(grd), blank, 0, 2, 8, 1); // this forces a specific window width which everything else is oriented around
                                                       // It's put here because a gap between text box and quit looks nicer than anywhere else
    gtk_grid_attach(GTK_GRID(grd), closeBtn, 6, 3, 2, 1);

    gtk_container_add(GTK_CONTAINER(subWin), grd); // add the grid to the window

    gtk_widget_show_all(subWin);
}

/*
GtkWidget newBox(){
    GtkWidget *grd = gtk_grid_new();
    // add the values passed in as arguments to the box as a tile

}
*/

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv); // Initialise GTK

    /* This all creates and formats the text entry window */
    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL); // Create a window 
    gtk_window_set_default_size(GTK_WINDOW(win), winWidth, winHeight); // set width and height
    gtk_window_set_resizable(GTK_WINDOW(win), FALSE); // set non-resizable
    gtk_window_set_title(GTK_WINDOW(win), "Dream Journal");
    g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);

    g_signal_connect(win, "delete_event", G_CALLBACK(endProgram), NULL); // connect the `x` in the toolbar to the endProgram function as well
    // inside this window i need to create a calendar-esque grid

    // for loop to create a grid of grid items - 1 for every day of the month
    // maintain an array of these

    GtkWidget *cal = gtk_calendar_new();
    gtk_calendar_set_detail_height_rows(GTK_CALENDAR(cal), 2);

    // GtkWidget *newBtn = gtk_button_new_with_label("New");
    // g_signal_connect(newBtn, "clicked", G_CALLBACK(newWin), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_box_pack_start(GTK_BOX(box), cal, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(box), newBtn, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(win), box);

    gtk_widget_show_all(win); // show everything in the window
    gtk_main(); // run it 
    return 0;
}
