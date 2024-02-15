#include "consts.h"

static int winWidth = 1280;
static int winHeight = 720;

static FILE *fp;
static sqlite3 *db;

int subWinOpen = 0;
bool loggedIn = false;
char *ERR = 0;

int getWinWidth() {
    return winWidth;
}

int getWinHeight() {
    return winHeight;
}

int getSubWinOpen() {
    return subWinOpen;
}

void setSubWinOpen(int newOpen) {
    subWinOpen = newOpen;
}

bool checkDir(char* dirname) {
    DIR* d;
    int n = 0;
    struct dirent *dir;
    bool dirCreated;

    d = opendir(dirname);
    if(!d) {
        mkdir(dirname, 0700);
        dirCreated = true;
    }
    else {
        /*
        while((dir = readdir(d)) != NULL) {
            if(n > 1) {
                printf("%s\n", dir->d_name);
            }
            n++;
        }
        */
        dirCreated = false;
    }
    closedir(d);
    return dirCreated;
}

void openFile(char* newFilename) {
    char filename[20];
    int rc;

    strcpy(filename, newFilename);
    // strcat(filename, ".db");

    rc = sqlite3_open(filename, &db);

    // fp = fopen(filename, getOpenType(openType));
    if(db) {
        printf("successfully opened file %s\n", filename);
    }
    else {
        printf("failed to open file %s\n", filename);
    }
}

void initTable() {
    if(db) {
        char* sql = "CREATE TABLE DREAMS("  \
                     "DATE INT PRIMARY KEY        NOT NULL,"\
                     "TYPE             INT        NOT NULL,"\
                     "DRUNK            BOOL       NOT NULL,"\
                     "INSOMNIA         BOOL       NOT NULL,"\
                     "MELATONIN        INT        NOT NULL,"\
                     "CONTENT          CHAR(1050))";
        int rc = sqlite3_exec(db, sql, sqliteCallback, 0, &ERR);
        if(rc != SQLITE_OK) {
            printf("SQL Error: %s\n", ERR);
            sqlite3_free(ERR);
        }
        else {
            printf("Table Initialised Successfully\n");
        }
    }
}

static int sqliteCallback(void *notUsed, int argc, char **argv, char **colName) {
    for(int i = 0; i < argc; i++) {
        printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
}

void writeFile(struct USERDATA userdata) {
    if(db) {
        sqlite3_stmt *stmt;
        char* sql = "INSERT INTO DREAMS (DATE,TYPE,DRUNK,INSOMNIA,MELATONIN,CONTENT) " \
               "VALUES (?,?,?,?,?,?); ";

        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, userdata.date);
        sqlite3_bind_int(stmt, 2, userdata.type);
        sqlite3_bind_int(stmt, 3, userdata.drunk);
        sqlite3_bind_int(stmt, 4, userdata.insomnia);
        sqlite3_bind_int(stmt, 5, userdata.melatonin);
        sqlite3_bind_text(stmt, 6, userdata.content, -1, SQLITE_STATIC);

        int rc = sqlite3_step(stmt);

        // int rc = sqlite3_exec(db, stmt, sqliteCallback, 0, &ERR);

        if(rc != SQLITE_DONE) {
            printf("SQL Error: %d\n", rc);
            // sqlite3_free(ERR);
        }
        else {
            printf("info inserted successfully\n");
        }
        sqlite3_finalize(stmt);
    }

    /*
    if(fp) {
        printf("Writing userdata: %s\n", userdata.username);
        fwrite(&userdata, sizeof(struct USERDATA), 1, fp);
    }
    */
}

void readFile() {
    /*
    if(fp) {
        struct USERDATA readData;
        fread(&readData, sizeof(struct USERDATA), 1, fp);
        printf("Username: %s\n", readData.username);
    }
    */
    return;
}

void closeFile() {
    if(db){
        sqlite3_close(db);
    }
}

// struct DATE getDate() {
int getDate() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int date = (tm.tm_year + 1900)*10000;
    date += (tm.tm_mon + 1)*100;
    date += tm.tm_mday;

    /*
    struct DATE d;
    d.d = tm.tm_mday;
    d.m = tm.tm_mon + 1;
    d.y = tm.tm_year + 1900;
    */

    return date;
}

void closeSubWin(GtkWidget *widget, gpointer ptr) {
    setSubWinOpen(0);
    if(loggedIn == false) {
        gtk_main_quit();
    }
    GtkWidget* subWin = GTK_WIDGET(ptr); // occasionally these two lines throw an error 
    gtk_widget_destroy(subWin); // cause unclear
} 
