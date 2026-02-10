#include "../../include/engine.h"

/* Color Helpers */
static t_color color_add(t_color c1, t_color c2)
{
    return ((t_color){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

static t_color color_scale(t_color c, double s)
{
    return ((t_color){c.r * s, c.g * s, c.b * s});
}

static t_color color_mult(t_color c1, t_color c2)
{
    return ((t_color){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}

static t_color color_clamp(t_color c)
{
    t_color res;
    
    res.r = c.r > 1.0 ? 1.0 : (c.r < 0 ? 0 : c.r);
    res.g = c.g > 1.0 ? 1.0 : (c.g < 0 ? 0 : c.g);
    res.b = c.b > 1.0 ? 1.0 : (c.b < 0 ? 0 : c.b);
    return (res);
}

/* Shadow logic */
static bool is_in_shadow(t_world *world, t_v3 point, t_v3 light_dir, double light_dist)
{
    t_ray   shadow_ray;
    t_hit   shadow_rec;
    
    shadow_ray.orig = vec_add(point, vec_scale(light_dir, 1e-4));
    shadow_ray.dir = light_dir;
    
    if (hit_world(world, shadow_ray, &shadow_rec))
    {
        if (shadow_rec.t < light_dist)
            return (true);
    }
    return (false);
}

static t_color calc_specular(t_ray ray, t_hit *rec, t_light light, t_v3 l_dir)
{
    double  spec_strength;
    t_v3    view_dir;
    t_v3    half_dir;
    double  ndh;
    t_color spec_c;

    view_dir = vec_unit(vec_scale(ray.dir, -1.0));
    half_dir = vec_unit(vec_add(l_dir, view_dir));
    ndh = vec_dot(rec->normal, half_dir);
    spec_strength = 0;
    if (ndh > 0 && rec->obj->specular > 1.0)
        spec_strength = pow(ndh, rec->obj->specular) * light.ratio;
    
    spec_c = color_scale(light.color, spec_strength);
    return (spec_c);
}

static t_color calc_light(t_world *world, t_ray ray, t_hit *rec, t_light light)
{
    t_v3    l_dir;
    double  l_dist;
    double  ndl;
    t_color diff;
    t_color spec;

    l_dir = vec_sub(light.pos, rec->p);
    l_dist = vec_len(l_dir);
    l_dir = vec_unit(l_dir);
    if (is_in_shadow(world, rec->p, l_dir, l_dist))
        return ((t_color){0,0,0});

    ndl = vec_dot(rec->normal, l_dir);
    if (ndl <= 0)
        return ((t_color){0,0,0});
    
    // Diffuse
    diff = color_mult(rec->obj->color, light.color);
    diff = color_scale(diff, ndl * light.ratio);
    
    // Specular
    spec = calc_specular(ray, rec, light, l_dir);
    
    return (color_add(diff, spec));
}

t_color compute_shading(t_world *world, t_ray ray, t_hit *rec)
{
    t_color final_c;
    t_color ambient;

    // Ambient
    ambient = color_mult(rec->obj->color, world->ambient.color);
    ambient = color_scale(ambient, world->ambient.ratio);
    final_c = ambient;

    if (world->lights)
    {
        final_c = color_add(final_c, 
            calc_light(world, ray, rec, world->lights[0]));
    }
    return (color_clamp(final_c));
}
