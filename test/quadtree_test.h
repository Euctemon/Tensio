#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

struct Point {
    double x;
    double y;
};

struct QuadTree {
    double min_x;
    double max_x;
    double min_y;
    double max_y;

    struct QuadTree* Nodes[4];
};

struct QuadPool {
    unsigned int capacity;
    unsigned int filled;

    struct QuadTree* (*trees)[];
};

bool line_intersect(struct Point p1, struct Point p2, struct Point p3, struct Point p4);

bool in_unit_range(double a, double b);