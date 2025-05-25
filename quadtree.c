#include "quadtree.h"

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