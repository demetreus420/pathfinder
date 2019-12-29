#include "header.h"

static int pop_from_stack(t_stack *st);
static int get_from_stack(t_stack *st);
static void restore_path_Helper(t_App *app, t_stack *st);
static void restore_allpaths_from_to(t_App *app, int i, int j);
static bool is_next(t_App *app, t_stack *st, int next);

void restore_all_paths(t_App *app) {
    for (int i = 0; i < app->SIZE; i++)
        for (int j = i + 1; j < app->SIZE; j++)
            restore_allpaths_from_to(app, i, j);
}

void mx_make_allpaths_and_print(t_App *app) {
    mx_make_cost_matrix(app);
    restore_all_paths(app);
}

static int pop_from_stack(t_stack *st) {
    if (st->size > 1) {
        st->size--;
        return st->path[st->size + 1];
    }
    return st->path[1];
}

static int get_from_stack(t_stack *st) {
    return st->path[st->size];
}

static bool is_next(t_App *app, t_stack *st, int next) {
    int k = get_from_stack(st);
    int i = st->path[0];
    int *AM = app->AM;
    int *DM = app->dist_M;
    int size = app->SIZE;

    if (k != next)
        if (DM[i * size + k] - AM[k * size + next] == DM[i * size + next])
            return true;
    return false;
}

static void restore_path_Helper(t_App *app, t_stack *st) {
    if (get_from_stack(st) == st->path[0]) {
        mx_print_path_info(app, st);
        return;
    }
    else {
        for (int next = 0; next < app->SIZE; next++) {
            if (is_next(app, st, next)) {
                mx_push_in_stack(st, next);
                restore_path_Helper(app, st);
                pop_from_stack(st);
            }
        }
    }
}

static void restore_allpaths_from_to(t_App *app, int i, int j) {
    t_stack *st = NULL;

    mx_init_stack(&st, app, i, j);
    restore_path_Helper(app, st);
    free(st->path);
    free(st);
}
