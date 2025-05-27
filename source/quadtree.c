#include "quadtree.h"
#include <math.h>

struct QuadPool* quad_pool_init(unsigned int init_capacity) {
    struct QuadPool* pool_pt = malloc(sizeof(struct QuadPool));

    if (pool_pt == NULL) {
        fprintf(stderr, "Failed to allocate quad pool structure.\n");
        exit(EXIT_FAILURE);
    }

    pool_pt->trees = malloc(init_capacity * sizeof(struct QuadTree*));

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
bool intersect(struct Point p1, struct Point p2, struct Point p3, struct Point p4) {
    double det = (p2.x - p1.x) * (p3.y - p4.y) - (p2.y - p1.y) * (p3.x - p4.x);
    double det1 = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    double det2 = (p3.x - p1.x) * (p3.y - p4.y) - (p3.y - p1.y) * (p3.x - p4.x);

    return in_unit_range(det1, det) && in_unit_range(det2,det);
}