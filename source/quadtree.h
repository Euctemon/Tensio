#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Point {
    double x;
    double y;
};

struct Region {
    double min_x;
    double max_x;
    double min_y;
    double max_y;
};

struct QuadTree {
    struct Region box;
    struct QuadTree* Nodes[4];
};

struct QuadPool {
    unsigned int capacity;
    unsigned int filled;
    struct QuadTree* (*trees)[];
};

struct Geometry {
    unsigned int size;
    struct Point (*points)[];
};

void geometry_to_svg(struct Geometry geom, const char filename[]);