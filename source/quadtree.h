#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// enum Position {
//     INSIDE,
//     OUTSIDE,
//     BOUDARY
// };

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