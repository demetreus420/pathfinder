#include "libmx.h"
#include "header.h" 

int main(int argc, char *argv[]) {
    t_App *app = malloc(sizeof(t_App));

    mx_initialize(argc, argv, app);
    mx_make_allpaths_and_print(app);
    mx_free_all(app);
    //system("leaks -q pathfinder example2"); Test for leaks
    return 0;
}

