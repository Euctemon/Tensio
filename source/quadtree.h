#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#pragma once

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
    struct QuadTree (*trees)[];
};

struct Geometry {
    unsigned int size;
    struct Point (*points)[];
};

struct QuadPool* quad_pool_init(unsigned int init_capacity);
void quad_pool_free(struct QuadPool* pool_pt);
void quadtree_compute(struct QuadPool* pool, struct Geometry geom);

struct Region bounding_region(struct Geometry geom);

bool is_leaf(struct QuadTree tree);