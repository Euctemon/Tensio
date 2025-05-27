#include <stdio.h>
#include "quadtree.h"


int main(void) {
    struct Point points[] = {{0,0}, {10,30}, {30,60}, {70,20}, {50,-10}, {20, -20}, {0,0}};
    struct Geometry geom = {7, &points};
    geometry_to_svg(geom, "./geometry.svg");
    return 0;
}