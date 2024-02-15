#include "login.h"

const int loginWinWidth = 240;
const int loginWinHeight = 180;
char userNames[15][5];

void login(GtkWidget *widget, gpointer ptr) { 
    struct loginData *dat = (struct loginData*)ptr;

    int userIndex = dat->index;

    printf("%d\n%s\n", userIndex, userNames[userIndex]);

    char filename[20];
    strcpy(filename, "users/");
    strcat(filename, userNames[userIndex]);
    printf("%s\n", filename);
    openFile(filename);

    loggedIn = true;

    dreamType type = d_good;
    struct USERDATA data = {
        getDate(), 
        type,
        0,
        0,
        0,
        "Hello"
    };
    writeFile(data);

    closeSubWin(widget, dat->loginWin);
}

void openLoginWin(GtkWidget *win, gpointer ptr) {
    GtkWidget *subWin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(subWin), FALSE); // set non-resizable
    gtk_window_set_title(GTK_WINDOW(subWin), "Login");

    GtkWidget *closeBtn = gtk_button_new_with_label("Quit"); // Create a button with a label

    g_signal_connect(closeBtn, "clicked", G_CALLBACK(closeSubWin), subWin);  // for some reason this throws an exception
    g_signal_connect(subWin, "delete_event", G_CALLBACK(closeSubWin), subWin);

    struct newUserData newData = {1, subWin};

    GtkWidget *newUserBtn = gtk_button_new_with_label("New User");
    g_signal_connect(newUserBtn, "clicked", G_CALLBACK(newUserWin), &newData);

    GtkWidget *blank = gtk_label_new(""); // blanking block
    gtk_widget_set_hexpand(GTK_WIDGET(blank), true); // set the blanking box to use as much width of the screen as possible

    GtkWidget *blank2 = gtk_label_new(""); // blanking block
    gtk_widget_set_hexpand(GTK_WIDGET(blank2), true); // set the blanking box to use as much width of the screen as possible

    GtkWidget *grd = gtk_grid_new(); // create a new grid
    gtk_grid_attach(GTK_GRID(grd), blank, 0, 0, 4, 1); // define the width

    DIR* d;
    struct dirent *dir;
    int rowIndex = 0;
    int btnIndex = 0;

    int newWinHeight = loginWinHeight;

    d = opendir("users");
    if(!d) {
        printf("ERR: Directory 'users' does not exist\n");
    }
    else {
        while((dir = readdir(d)) != NULL) {
            if(rowIndex > 1) {
                GtkWidget *newBtn = gtk_button_new_with_label(dir->d_name);

                memcpy(userNames[btnIndex], dir->d_name, 15);

                gtk_grid_attach(GTK_GRID(grd), newBtn, 1, rowIndex, 2, 1);

                struct loginData *dat = malloc(sizeof(struct loginData));

                dat->index = btnIndex;
                dat->loginWin = subWin;
                // g_signal_connect(newBtn, "clicked", G_CALLBACK(login), GINT_TO_POINTER(btnIndex));

                g_signal_connect(newBtn, "clicked", G_CALLBACK(login), dat);

                btnIndex++;
                rowIndex++;
                
                GtkWidget *newSpacer = gtk_label_new("");
                gtk_widget_set_hexpand(GTK_WIDGET(newSpacer), TRUE);
                gtk_grid_attach(GTK_GRID(grd), newSpacer, 0, rowIndex, 4, 1);
            }
            rowIndex++;
        }
    }
    closedir(d);

    // attach everything to the grid
    gtk_grid_attach(GTK_GRID(grd), newUserBtn, 1, rowIndex, 2, 1);

    rowIndex++;

    gtk_grid_attach(GTK_GRID(grd), blank2, 0, rowIndex, 4, 1);

    rowIndex++;

    gtk_grid_attach(GTK_GRID(grd), closeBtn, 1, rowIndex, 2, 1);

    gtk_container_add(GTK_CONTAINER(subWin), grd); // add the grid to the window

    newWinHeight = 30 * rowIndex; 

    gtk_window_set_default_size(GTK_WINDOW(subWin), loginWinWidth, newWinHeight); // set width and height

    gtk_widget_show_all(subWin);

    setSubWinOpen(1);
}
