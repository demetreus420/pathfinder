#include "header.h"

static char *get_name_by_id(int i, t_App *app);
static void print_line(void);
static void print_path(t_App *app, t_stack *st);
static void print_route(t_App *app, t_stack *st);
static void print_distance(t_App *app, t_stack *st);

void mx_print_path_info(t_App *app, t_stack *st) {
    bool first_line = true;

    if (first_line)
        first_line = false;
    else
        mx_printstr("\n");
    print_line();
    mx_printstr("\n");
    print_path(app, st);
    print_route(app, st);
    print_distance(app, st);
    print_line();
}

static char *get_name_by_id(int i, t_App *app) {
    return app->city[i];
}

static void print_line(void) {
    char s[]= "========================================";
    mx_printstr(s);
}

static void print_path(t_App *app, t_stack *st) {
    mx_printstr("Path: ");
    mx_printstr(get_name_by_id (st->path[0], app));
    mx_printstr(" -> ");
    mx_printstr(get_name_by_id(st->path[1], app));
    mx_printstr("\n");
}

static void print_route(t_App *app, t_stack *st) {
    mx_printstr("Route: ");
    for(int i = st->size; i >= 2; i--) {
        mx_printstr(get_name_by_id(st->path[i], app));
        mx_printstr(" -> ");

    }
    mx_printstr(get_name_by_id(st->path[1], app));
    mx_printstr("\n");
}

static void print_distance(t_App *app, t_stack *st) {
    int total_dist = 0;
    int dist;

    mx_printstr("Distance: ");
    for(int i = st->size - 1; i >= 2; i--) {
        dist = app->AM[st->path[i] * app->SIZE + st->path[i + 1]];
        total_dist += dist;
        mx_printint(dist);
        mx_printstr(" + ");
    }
    if (total_dist != 0) {
        dist = app->AM[st->path[2] * app->SIZE + st->path[1]];
        total_dist += dist;
        mx_printint(dist);
        mx_printstr(" = ");
    }
    else
       total_dist = app->AM[st->path[2] * app->SIZE + st->path[1]];
    mx_printint(total_dist);
    mx_printstr("\n");
}

