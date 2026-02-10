#include "../../include/engine.h"

/* Returns a new vector with x,y,z values */
t_v3    vec_new(double x, double y, double z)
{
    t_v3 v;
    
    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

/* Vector Addition: a + b */
t_v3    vec_add(t_v3 a, t_v3 b)
{
    t_v3 res;

    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    return (res);
}

/* Vector Subtraction: a - b */
t_v3    vec_sub(t_v3 a, t_v3 b)
{
    t_v3 res;

    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return (res);
}

/* Vector Scaling: v * s */
t_v3    vec_scale(t_v3 v, double s)
{
    t_v3 res;

    res.x = v.x * s;
    res.y = v.y * s;
    res.z = v.z * s;
    return (res);
}

/* Dot Product: a . b */
double  vec_dot(t_v3 a, t_v3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/* Cross Product: a x b */
t_v3    vec_cross(t_v3 a, t_v3 b)
{
    t_v3 res;

    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return (res);
}

/* Length Squared (faster than length) */
double  vec_len_sq(t_v3 v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

/* Vector Length (Magnitude) */
double  vec_len(t_v3 v)
{
    return (sqrt(vec_len_sq(v)));
}

/* Normalize Vector (Unit Vector) */
t_v3    vec_unit(t_v3 v)
{
    double len;
    
    len = vec_len(v);
    if (len == 0)
        return ((t_v3){0, 0, 0});
    return (vec_scale(v, 1.0 / len));
}

/* Reflect vector v around normal n */
/* r = v - 2(v.n)n */
t_v3    vec_reflect(t_v3 v, t_v3 n)
{
    return (vec_sub(v, vec_scale(n, 2.0 * vec_dot(v, n))));
}
