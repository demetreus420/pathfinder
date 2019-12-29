#include "header.h"

static void push_element_in_city(char *elem, t_App *app);
static int index_in_city(char *elem, t_App *app);
static void init_adjacency_matrix(t_App *app);
static char *read_file(char *argv[], t_App *app);
static void parse_rest_of_lines(t_App *app, char **str_parsed);

void mx_initialize(int argc, char *argv[], t_App *app) {
    app->city = NULL;
    app->AM = NULL;
    app->dist_M = NULL;
    app->parsed_lines_array = NULL;
    app->file_to_str = NULL;

    if (argc != 2)
        mx_cast_error_message(Invalid_Number_Of_CommandLine, app);
    char *str = read_file(argv, app);
    app->parsed_lines_array = mx_strsplit(str, '\n');
    char **str_parsed = app->parsed_lines_array;
    app->SIZE = mx_my_atoi(str_parsed[0]); 
    if (app->SIZE == -1)
        mx_cast_error_message(Line1_isnt_valid, app);
    parse_rest_of_lines(app, str_parsed);
    if (app->city[app->SIZE - 1] == NULL)
        mx_cast_error_message(Invalid_Number_of_Islands, app);
}

static void parse_rest_of_lines(t_App *app, char **str_parsed) {
    mx_init_city(app);
    init_adjacency_matrix(app);
    for (int i = 1; str_parsed[i] != NULL; i++) {
        char *arg1 = NULL;
        char *arg2 = NULL;
        int arg3 = -1;
        if (mx_parse_line(str_parsed[i], &arg1, &arg2, &arg3)) {
            push_element_in_city(arg1, app);
            push_element_in_city(arg2, app);
            int i = index_in_city(arg1, app);
            int j = index_in_city(arg2, app);
            app->AM[i * app->SIZE + j] = arg3;
            app->AM[j * app->SIZE + i] = arg3;
        }
        else {
            free(arg1);
            free(arg2);
            app->invalid_line_number = i + 1;
            mx_cast_error_message(Line_isnt_Valid, app);
        }
        free(arg1);
        free(arg2);
    }
}

static void push_element_in_city(char *elem, t_App *app) {
    char **city = app->city;
    int i;

    for (i = 0; i < app->SIZE; i++) {
        if (city[i] == NULL)
            break;
        if (mx_strcmp(city[i], elem) == 0)
            return;
    }
    if (i < app->SIZE)
        city[i] = mx_strdup(elem);
    else
        mx_cast_error_message(Invalid_Number_of_Islands, app);
}

static int index_in_city(char *elem, t_App *app) {
    for (int i = 0; i < app->SIZE; i++)
        if ( mx_strcmp(app->city[i], elem) == 0)
            return i;
    return -1;
}

static void init_adjacency_matrix(t_App *app) {
    app->AM = malloc(app->SIZE * app->SIZE * sizeof(int));
    for (int i = 0; i < app->SIZE; i++)
        for (int j = 0 ; j < app->SIZE; j++) {
            if (i == j)
                app->AM[i * app->SIZE + j] = 0;
            else
                app->AM[i * app->SIZE + j] = 1000000000;
        }
}

static char *read_file(char *argv[], t_App *app) {
    int fd = open(argv[1], O_RDONLY);
    char *str;

    app->file_name = argv[1];
    if (fd < 0) {
        close(fd);
        mx_cast_error_message(File_Doesnt_Exist, app);
    }
    close(fd);
    app->file_to_str = mx_file_to_str(argv[1]);
    str = app->file_to_str;
    if (mx_strlen(str) == 0)
        mx_cast_error_message(File_Is_Empty, app);
    return str;
}
