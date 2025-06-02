#include "quadtree.h"
#include <math.h>

struct QuadPool* quad_pool_init(unsigned int init_capacity) {
    struct QuadPool* pool_pt = malloc(sizeof(struct QuadPool));

    if (pool_pt == NULL) {
        fprintf(stderr, "Failed to allocate quad pool structure.\n");
        exit(EXIT_FAILURE);
    }

    pool_pt->trees = malloc(init_capacity * sizeof(struct QuadTree));

    if (pool_pt->trees == NULL) {
        fprintf(stderr, "Failed to allocate quad pool array.\n");
        exit(EXIT_FAILURE);
    }
    
    pool_pt->capacity = init_capacity;
    pool_pt->filled = 0;
    
    return pool_pt;
}

void quad_pool_free(struct QuadPool* pool_pt) {
    free(pool_pt->trees);
    free(pool_pt);
}

// Checks whether a/b is in [0,1]
bool in_unit_range(double a, double b) {
    bool pos = a >= 0 && b > 0 && a <= b;
    bool neg = a <= 0 && b < 0 && b <= a;

    return pos || neg;
}

// Intersection of lines p1->p2 and p3->p4
// Overlapping lines do not intersect
bool line_intersect(struct Point p1, struct Point p2, struct Point p3, struct Point p4) {
    double det = (p2.x - p1.x) * (p3.y - p4.y) - (p2.y - p1.y) * (p3.x - p4.x);
    double det1 = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    double det2 = (p3.x - p1.x) * (p3.y - p4.y) - (p3.y - p1.y) * (p3.x - p4.x);

    return in_unit_range(det1, det) && in_unit_range(det2,det);
}

struct Region bounding_region(struct Geometry geom) {
    double x_min = (*geom.points)[0].x;
    double x_max = (*geom.points)[0].y;
    double y_min = (*geom.points)[0].x;
    double y_max = (*geom.points)[0].y;

    for (size_t i = 1; i < geom.size; i++) {
        if ((*geom.points)[i].x < x_min) x_min = (*geom.points)[i].x;
        if ((*geom.points)[i].x > x_max) x_max = (*geom.points)[i].x;
        if ((*geom.points)[i].y < y_min) y_min = (*geom.points)[i].y;
        if ((*geom.points)[i].y > y_max) y_max = (*geom.points)[i].y;
    }

    return (struct Region){x_min,x_max, y_min,y_max};
}

bool is_leaf(struct QuadTree tree) {
    for (size_t i = 0; i < 4; i++) {
        if (tree.Nodes[i] != NULL) return false;
    }
    
    return true;
}

bool region_intersect(struct Region region, struct Geometry geom) {
    struct Point LB = {region.min_x, region.min_y};
    struct Point LU = {region.min_x, region.max_y};
    struct Point RB = {region.max_x, region.min_y};
    struct Point RU = {region.max_x, region.max_y};

    for (size_t i = 0; i < geom.size - 1; i++) {
     if (line_intersect(LB, LU, (*geom.points)[i], (*geom.points)[i+1])) return true;
     if (line_intersect(LU, RU, (*geom.points)[i], (*geom.points)[i+1])) return true;
     if (line_intersect(RU, RB, (*geom.points)[i], (*geom.points)[i+1])) return true;
     if (line_intersect(RB, LB, (*geom.points)[i], (*geom.points)[i+1])) return true;
    }

    return false;
}


void quadtree_compute(struct QuadPool* pool, struct Geometry geom) {
    unsigned int processed_trees = 0;
    
    (*pool->trees)[processed_trees].box = bounding_region(geom);
    pool->filled++;

    while (processed_trees != pool->filled) {
        if (region_intersect((*pool->trees)[processed_trees].box, geom)) {
            if (pool->filled + 4 > pool->capacity) {
                fprintf(stderr, "Pool array has not enough capacity.\n");
                return;
            }

            for (size_t i = 0; i < 4; i++) {
                (*pool->trees)[processed_trees].Nodes[i] = &(*pool->trees)[pool->filled];
                pool->filled++;
            }
        }
        processed_trees++;
    }
}