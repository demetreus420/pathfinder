#include "header.h"
#include "libmx.h"

int mx_my_atoi(char *s);
bool mx_is_valid_name(char *s);
bool mx_parse_line(char *line, char **arg1, char **arg2, int *arg3);
void mx_init_city(t_App *app);
void mx_init_stack(t_stack **st, t_App *app, int i, int j);
void mx_push_in_stack(t_stack *st, int elem);

int mx_my_atoi(char *s) {
    int res = 0;

    while (*s != '\0') {
        if (!mx_isdigit(*s)) return -1;
        res = 10 * res + (*s) - '0';
        s++;
    }
    if (res == 0)
        res = -1;
    return res;
}

bool mx_is_valid_name(char *s) {
    if (mx_strlen(s) == 0)
        return false;
    for (int i = 0; s[i] != '\0'; i++)
        if(!mx_isalpha(s[i]))
            return false;
    return true;
}

bool mx_parse_line(char *line, char **arg1, char **arg2, int *arg3) {
    int dash_idx = mx_get_char_index(line, '-');
    int coma_idx = mx_get_char_index(line, ',');
    int len = mx_strlen(line);

    if (dash_idx == -1 || coma_idx == -1
        || len == 0 || dash_idx > coma_idx)
            return false;
    *arg1 = mx_strndup(line, dash_idx);
    *arg2 = mx_strndup(line + dash_idx + 1, coma_idx - dash_idx - 1);
    char *number = mx_strndup(line + coma_idx + 1, len - coma_idx - 1);
    if (!mx_is_valid_name(*arg1) || !mx_is_valid_name(*arg2))
        return false;
    *arg3 = mx_my_atoi(number);
    if (*arg3 == -1)
        return false;
    free(number);
    return true;
}

void mx_init_city(t_App *app) {
    app->city = malloc(app->SIZE * sizeof (char *) + 1);
    if (app->city == NULL)
        exit(1);
    for (int i = 0; i < app->SIZE + 1; i++)
        app->city[i] = NULL;
}

void mx_init_stack(t_stack **st, t_App *app, int i, int j) {
    *st = malloc(sizeof(t_stack));
    if ((*st) == NULL)
        exit(1);
    (*st)->max_size = app->SIZE;
    (*st)->path = malloc((*st)->max_size * sizeof(int) + 1);
    (*st)->path[0] = i;
    (*st)->path[1] = j;
    (*st)->size = 1;
}

void mx_push_in_stack(t_stack *st, int elem) {
    if (st->size < st->max_size) {
        st->size++;
        st->path[st->size] = elem;
    }
}
