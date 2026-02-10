#include "../../include/engine.h"
#include <stdio.h>

void print_vec(const char *label, t_v3 v)
{
    printf("%s: (%.2f, %.2f, %.2f)\n", label, v.x, v.y, v.z);
}

int main(void)
{
    t_v3 v1 = vec_new(1, 2, 3);
    t_v3 v2 = vec_new(4, 5, 6);
    t_v3 v3;
    double d;

    printf("=== Vector Unit Tests ===\n");
    print_vec("v1", v1);
    print_vec("v2", v2);

    // Add
    v3 = vec_add(v1, v2);
    print_vec("Add (v1+v2) [Expect 5,7,9]", v3);

    // Sub
    v3 = vec_sub(v2, v1);
    print_vec("Sub (v2-v1) [Expect 3,3,3]", v3);

    // Dot
    d = vec_dot(v1, v2);
    printf("Dot (v1.v2) [Expect 32.00]: %.2f\n", d);

    // Cross
    // v1 x v2 = (2*6 - 3*5, 3*4 - 1*6, 1*5 - 2*4) = (12-15, 12-6, 5-8) = (-3, 6, -3)
    v3 = vec_cross(v1, v2);
    print_vec("Cross (v1xv2) [Expect -3,6,-3]", v3);

    // Norm
    t_v3 v4 = vec_new(3, 0, 0);
    print_vec("v4", v4);
    v3 = vec_unit(v4);
    print_vec("Unit(v4) [Expect 1,0,0]", v3);

    // Length
    printf("Len(v4) [Expect 3.00]: %.2f\n", vec_len(v4));

    printf("=== Test Complete ===\n");
    return (0);
}
