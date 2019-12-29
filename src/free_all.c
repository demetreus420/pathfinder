#include "header.h"

static void delete_matrix(int *m); 

void mx_free_all( t_App *app) {
    mx_del_strarr(&(app->city));
    delete_matrix(app->AM);
    delete_matrix(app->dist_M);
    mx_del_strarr(&(app->parsed_lines_array));
    mx_strdel(&(app->file_to_str));
}

static void delete_matrix(int *m) {
    if (m != NULL)
        free(m);
}

