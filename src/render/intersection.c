#include "../../include/engine.h"

/*
 * Geometric Sphere Intersection
 * Distinct from the algebraic solver (which solves at^2 + bt + c = 0).
 * Uses vector projection logic:
 * 1. L = C - O (Vector from ray origin to sphere center)
 * 2. tca = L . D (Project L onto ray direction)
 * 3. d2 = L . L - tca * tca (Squared distance from C to ray)
 * 4. thc = sqrt(r^2 - d2)
 * 5. t0 = tca - thc, t1 = tca + thc
 */
bool hit_sphere(t_ray ray, t_sphere *sp, t_hit *rec)
{
    t_v3    l_vec;
    double  tca;
    double  d2;
    double  thc;
    double  t0;
    double  t1;
    double  rad2;

    l_vec = vec_sub(sp->center, ray.orig);
    tca = vec_dot(l_vec, ray.dir);
    
    // If tca < 0, center is behind ray origin. 
    // BUT we might still be inside. 
    // However, if we assume objects are in front generally, simplified check:
    // Ideally we check d2.
    
    d2 = vec_dot(l_vec, l_vec) - (tca * tca);
    rad2 = sp->radius * sp->radius;
    
    if (d2 > rad2)
        return (false); // Miss: Ray misses sphere
        
    thc = sqrt(rad2 - d2);
    t0 = tca - thc;
    t1 = tca + thc;

    // Find closest valid t
    if (t0 > 0.001)
        rec->t = t0;
    else if (t1 > 0.001)
        rec->t = t1;
    else
        return (false); // Both behind

    rec->p = vec_add(ray.orig, vec_scale(ray.dir, rec->t));
    rec->normal = vec_unit(vec_sub(rec->p, sp->center));
    
    // Inside check: if normal points in same direction as ray, flip it?
    // Standard miniRT usually expects outside viewing, but good to know data.
    return (true);
}

/* Plane Intersection */
/* (P - P0) . N = 0 */
bool hit_plane(t_ray ray, t_plane *pl, t_hit *rec)
{
    double  denom;
    double  t;
    t_v3    p0_sub_orig;

    denom = vec_dot(pl->normal, ray.dir);
    
    // Check if parallel
    if (fabs(denom) < 1e-6)
        return (false);
        
    p0_sub_orig = vec_sub(pl->point, ray.orig);
    t = vec_dot(p0_sub_orig, pl->normal) / denom;
    
    if (t < 0.001)
        return (false);
        
    rec->t = t;
    rec->p = vec_add(ray.orig, vec_scale(ray.dir, t));
    rec->normal = pl->normal;
    
    // If we hit back face, flip normal?
    if (denom > 0)
        rec->normal = vec_scale(pl->normal, -1.0);
        
    return (true);
}

/* Cylinder Intersection Helpers */
// Simplified infinite cylinder check followed by height crop
static bool solve_quadratic(double a, double b, double c, double *t)
{
    double disc;
    double t1;
    double t2;
    
    disc = b * b - 4 * a * c;
    if (disc < 0)
        return (false);
    t1 = (-b - sqrt(disc)) / (2 * a);
    t2 = (-b + sqrt(disc)) / (2 * a);
    
    if (t1 > 0.001)
        *t = t1;
    else if (t2 > 0.001)
        *t = t2;
    else
        return (false);
    return (true);
}

// Check height bounds
// P = O + tD
// h = (P - C) . Axis
// 0 <= h <= height  OR  -height/2 <= h <= height/2 depending on def
// miniRT subject doesn't strictly specify center vs base. usually Center.
// We assume center. Range: [-H/2, H/2]
bool hit_cylinder(t_ray ray, t_cylinder *cy, t_hit *rec)
{
    t_v3    oc;
    double  a, b, c;
    double  t;
    t_v3    p;
    double  h;
    
    oc = vec_sub(ray.orig, cy->center);
    
    // A = D . D - (D . Axis)^2
    // B = 2 * ( (D . OC) - (D . Axis)(OC . Axis) )
    // C = OC . OC - (OC . Axis)^2 - R^2
    
    double d_dot_axis = vec_dot(ray.dir, cy->axis);
    double oc_dot_axis = vec_dot(oc, cy->axis);
    
    a = vec_len_sq(ray.dir) - d_dot_axis * d_dot_axis;
    b = 2 * (vec_dot(ray.dir, oc) - d_dot_axis * oc_dot_axis);
    c = vec_len_sq(oc) - oc_dot_axis * oc_dot_axis - (cy->diameter / 2) * (cy->diameter / 2);
    
    if (!solve_quadratic(a, b, c, &t))
        return (false);
        
    p = vec_add(ray.orig, vec_scale(ray.dir, t));
    h = vec_dot(vec_sub(p, cy->center), cy->axis);
    
    if (fabs(h) > cy->height / 2.0)
        return (false); // Out of height bounds
        
    rec->t = t;
    rec->p = p;
    
    // Normal: Project P onto axis => C + h*Axis
    // Normal is P - (C + h*Axis) normalized
    t_v3 proj_pt = vec_add(cy->center, vec_scale(cy->axis, h));
    rec->normal = vec_unit(vec_sub(p, proj_pt));
    
    // Check orientation
    if (vec_dot(ray.dir, rec->normal) > 0)
        rec->normal = vec_scale(rec->normal, -1.0);
        
    return (true);
}

/* Master Hit Function */
bool hit_world(t_world *world, t_ray ray, t_hit *rec)
{
    t_hit       temp_rec;
    bool        hit_anything = false;
    double      closest_so_far = 1e30; // INFINITY
    t_object    *current;
    
    current = world->objects;
    while (current)
    {
        bool hit_status = false;
        
        if (current->type == SPHERE)
            hit_status = hit_sphere(ray, (t_sphere *)current->data, &temp_rec);
        else if (current->type == PLANE)
            hit_status = hit_plane(ray, (t_plane *)current->data, &temp_rec);
        else if (current->type == CYLINDER)
            hit_status = hit_cylinder(ray, (t_cylinder *)current->data, &temp_rec);
            
        if (hit_status)
        {
            if (temp_rec.t < closest_so_far)
            {
                closest_so_far = temp_rec.t;
                *rec = temp_rec;
                rec->obj = current; // Save reference to object for material/color
                hit_anything = true;
            }
        }
        current = current->next;
    }
    return (hit_anything);
}
