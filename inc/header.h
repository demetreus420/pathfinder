#ifndef HEADER_H
#define HEADER_H

#include "libmx.h"

typedef struct s_APP {
    int SIZE;
    char **city;
    int *AM;
    int *dist_M;
    char **parsed_lines_array;
    char *file_to_str;
    int invalid_line_number;
    char *file_name;
} t_App;

 typedef struct {
        int *path;
        int size;
        int max_size;
    } t_stack;

typedef enum Err {
    Invalid_Number_Of_CommandLine,
    File_Doesnt_Exist,
    File_Is_Empty,
    Line1_isnt_valid,
    Line_isnt_Valid,
    Invalid_Number_of_Islands 

} e_Error;

void mx_printerr(const char *s);
bool mx_isdigit(int c);
bool mx_isalpha(int c);

int mx_my_atoi(char *s);
bool mx_is_valid_name(char *s);
bool mx_parse_line(char *line, char **arg1, char **arg2, int *arg3);
void mx_init_city(t_App *app);
void mx_init_stack(t_stack **st, t_App *app, int i, int j);
void mx_push_in_stack(t_stack *st, int elem);
void mx_initialize(int argc, char *argv[], t_App *app);
void mx_cast_error_message(e_Error err, t_App *app);
void mx_make_allpaths_and_print(t_App *app);
void mx_make_cost_matrix(t_App *app);
void mx_print_path_info(t_App *app, t_stack *st);
void mx_free_all( t_App *app);

#endif

