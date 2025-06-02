#include <stdio.h>
#include "svg.h"


int main(void) {
    struct Point points[] = {{0,0}, {10,30}, {30,60}, {70,20}, {50,-10}, {20, -20}, {0,0}};
    struct Geometry geom = {7, &points};
    struct QuadPool* pool_pt = quad_pool_init(20);
    
    quadtree_compute(pool_pt, geom);
    svg_write(geom, *pool_pt);
    quad_pool_free(pool_pt);
    return 0;
}