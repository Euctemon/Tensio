#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "quadtree.h"

void geometry_svg(FILE* file, struct Geometry geom);

void quadtree_svg(FILE* file, struct QuadPool pool);

void svg_write(struct Geometry geom, struct QuadPool pool);