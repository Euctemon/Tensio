#include "svg.h"

void geometry_svg(FILE* file, struct Geometry geom) {
    fprintf(file, "<polyline points=\"");

    for (size_t i = 0; i < geom.size; i++) {
        fprintf(file, "%f,%f ", (*geom.points)[i].x, (*geom.points)[i].y);
    }

    fprintf(file, "\" stroke=\"green\" fill=\"none\" stroke-width=\"0.5\" />\n");
}

void quadtree_svg(FILE* file, struct QuadPool pool) {
    struct Region box = (*pool.trees)[0].box;
    double mid_x;
    double mid_y;

    fprintf(file, "<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" style=\"stroke-width:0.5;stroke:red; fill:none\"/>", box.max_x-box.min_x, box.max_y-box.min_y, box.min_x, box.min_y);
    
    for (size_t i = 0; i < pool.filled; i++) {
        if (!is_leaf((*pool.trees)[i])) {
            box = (*pool.trees)[i].box;
            mid_x = (box.max_x - box.min_x) / 2;
            mid_y = (box.max_y - box.min_y) / 2;
            fprintf(file, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:red;stroke-width:0.2\"/>", box.min_x,mid_y, box.max_x, mid_y);
            fprintf(file, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:red;stroke-width:0.2\"/>", box.min_y,mid_x, box.max_y, mid_x);
        }        
    }
}

void svg_write(struct Geometry geom, struct QuadPool pool) {
    FILE* file = fopen("./geometry.svg", "w");
    struct Region box = bounding_region(geom);
    
    int min_x = (int)(box.min_x-10.0);
    int min_y = (int)(box.min_y-10.0);
    int width = (int)(box.max_x-box.min_x+20.0);
    int height = (int)(box.max_y-box.min_y+20.0);

    if (!file) {
        fprintf(stderr, "Failed to open file.\n");
        return;
    }
    
    fprintf(file, "<svg xmlns=\"http://www.w3.org/2000/svg\" ");
    fprintf(file, "viewBox=\"%d, %d, %d, %d\">\n", min_x, min_y ,width, height);

    geometry_svg(file, geom);
    quadtree_svg(file, pool);

    fprintf(file, "</svg>\n");
}