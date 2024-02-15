#include "newUser.h"

static GtkWidget *nameEntry;

void saveData(GtkWidget *widget, gpointer ptr) {
    printf("Saving Data...\n");

    const char *newUsername = gtk_entry_get_text(GTK_ENTRY(nameEntry));

    char filename[38] = "users/";
    strcat(filename, newUsername);
    strcat(filename, ".db");

    // checkDir(filename);

    openFile(filename);
    initTable();
    closeSubWin(widget, ptr);
}

void newUserWin(GtkWidget *win, gpointer ptr) {
    struct newUserData *data = ptr;
    printf("NewUserWin ptr: %d\n", data->existingUsers);
    if(data->existingUsers == 1) {
        printf("AAA\n");
        // this means the new user window was opened from the login window
        // therefore close the login win
    }
    else {
        printf("SEND HELP\n");
    }

    GtkWidget *subWin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(subWin), 400, 150); // set width and height
    gtk_window_set_resizable(GTK_WINDOW(subWin), FALSE); // set non-resizable
    gtk_window_set_title(GTK_WINDOW(subWin), "New User");

    nameEntry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(nameEntry), 15); // max length 15
    gtk_entry_set_placeholder_text(GTK_ENTRY(nameEntry), "Name...");

    GtkWidget *saveBtn = gtk_button_new_with_label("Save"); // Create a button with a label
    GtkWidget *closeBtn = gtk_button_new_with_label("Cancel"); // Create a button with a label

    g_signal_connect(saveBtn, "clicked", G_CALLBACK(saveData), subWin); 

    g_signal_connect(closeBtn, "clicked", G_CALLBACK(closeSubWin), subWin); 
    g_signal_connect(subWin, "delete_event", G_CALLBACK(closeSubWin), subWin);
    setSubWinOpen(1);

    GtkWidget *blank = gtk_label_new(""); // blanking block
    gtk_widget_set_hexpand(GTK_WIDGET(blank), TRUE); // set the blanking box to use as much width of the screen as possible

    GtkWidget *blank2 = gtk_label_new(""); 
    gtk_widget_set_hexpand(GTK_WIDGET(blank2), TRUE); 

    GtkWidget *grd = gtk_grid_new(); // create a new grid

    // attach everything to the grid
    gtk_grid_attach(GTK_GRID(grd), blank, 0, 0, 8, 1); 
    gtk_grid_attach(GTK_GRID(grd), nameEntry, 1, 1, 6, 1);
    gtk_grid_attach(GTK_GRID(grd), blank2, 0, 2, 8, 1); 
    gtk_grid_attach(GTK_GRID(grd), saveBtn, 5, 3, 2, 1);
    gtk_grid_attach(GTK_GRID(grd), closeBtn, 1, 3, 2, 1);

    gtk_container_add(GTK_CONTAINER(subWin), grd); // add the grid to the window

    gtk_widget_show_all(subWin);
}
