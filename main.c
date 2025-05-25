#include <stdio.h>
#include <stdlib.h>
#include "quadtree.h"

const char* print_pos(enum Position pos) {
    switch (pos) {
        case TOP_LEFT:  return "top left\n";
        case TOP_RIGHT: return "top right\n";
        case BOT_LEFT:  return "bottom left\n";
        case BOT_RIGHT: return "bottom right\n";
        case OUTER:     return "outer\n";
        default:        return "oh no\n";
    }
}

void foo(void) {
    struct Point points[] = {{1,2}, {2,3}, {3,1}};

    struct QuadTree* tree_pt = quadtree_init((struct Point){0,0}, (struct Point){5,5}, points[0]);

    for (size_t i = 1; i < 3; i++) {
        quad_tree_insert(tree_pt, points[i]);
    }
    
    quadtree_clear(tree_pt);
}


int main(void) {
    foo();

    return 0;
}