#include "quadtree_test.h"

void test_intersection()
{
    struct Point A = {-5, -5};
    struct Point B = {5, 5};

    // line overlap
    struct Point A2 = {-10, -10};
    struct Point B2 = {2, 2};
    assert(intersect(A, B, A2, B2) == false);

    // simple intersection
    struct Point A3 = {-5, 5};
    struct Point B3 = {5, -5};
    assert(intersect(A, B, A3, B3) == true);

    // endpoint intersection
    struct Point A4 = {-7, 7};
    assert(intersect(A, B, A4, A) == true);

    struct Point B4 = {7, -7};
    assert(intersect(A, B, B, B4) == true);

    // parallel lines
    struct Point A5 = {-4, -5};
    struct Point B5 = {6, 5};
    assert(intersect(A, B, A5, B5) == false);

    // non-intersecting
    struct Point A6 = {9, 0};
    struct Point B6 = {14, 1};
    assert(intersect(A,B, A6, B6) == false);

    // long lines
    struct Point A7 = {-1.2E+8, -3.1E+2};
    struct Point B7 = {2.2E+122, 1.8E+31};
    assert(intersect(A,B, A7, B7) == false);

    printf("All tests passed!\n");
}

void test_unit_range()
{
    // signs
    assert(in_unit_range(2.1, 3.8) == true);
    assert(in_unit_range(-2.1, -4.8) == true);
    assert(in_unit_range(1.2, 0.8) == false);
    assert(in_unit_range(-1.9, 3.8) == false);

    // signed zero
    assert(in_unit_range(0.0, 1.1) == true);
    assert(in_unit_range(-0.0, 1.7) == true);

    // exponent difference
    assert(in_unit_range(1.1, 1E+150) == true);
    assert(in_unit_range(1E-199, 1E-8) == true);
    assert(in_unit_range(1E-32, 1E-266) == false);

    printf("All tests passed!\n");
}

int main()
{
    test_intersection();
    test_unit_range();
    return 0;
}