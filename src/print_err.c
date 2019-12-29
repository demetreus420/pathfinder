#include "header.h"

static void ifFile_Doesnt_Exist(char *name);
static void ifFile_Is_Empty(char *name);
static void find_err(e_Error err, t_App *app);

void mx_cast_error_message(e_Error err, t_App *app) {
    find_err(err, app);
    mx_printerr("\n");
    mx_free_all(app);
    exit(1);
}

static void ifFile_Doesnt_Exist(char *name){
    mx_printerr("error: file ");
    mx_printerr(name);
    mx_printerr(" doesn't exist");
}

static void ifFile_Is_Empty(char *name){
    mx_printerr("error: file ");
    mx_printerr(name);
    mx_printerr(" is empty");
}

static void ifLine_isnt_Valid(int line_number) {
    mx_printerr("error: line ");
    char *snum = mx_itoa(line_number);
    mx_printerr(snum);
    free(snum);
    snum = NULL;
    mx_printerr(" isn't valid");
}

static void find_err(e_Error err, t_App *app) {
    switch (err) {
        case Invalid_Number_Of_CommandLine:
            mx_printerr("usage: ./pathfinder [filename]");
            break;
        case File_Doesnt_Exist:
            ifFile_Doesnt_Exist(app->file_name);
            break;
        case File_Is_Empty:
            ifFile_Is_Empty(app->file_name);
            break;
        case Line1_isnt_valid:
            mx_printerr("error: line 1 isn't valid"); 
            break;
        case Line_isnt_Valid:
            ifLine_isnt_Valid(app->invalid_line_number);
            break;
        case Invalid_Number_of_Islands:
            mx_printerr("error: invalid number of islands");
            break;
    }
}
