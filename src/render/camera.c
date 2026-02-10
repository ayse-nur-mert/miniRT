#include "../../include/engine.h"

/*
 * Initialize Camera Viewport
 * Calculates the 'screen' in 3D space based on FOV and Camera Orientation.
 */
void init_camera(t_world *world)
{
    t_view  *cam;
    double  viewport_height;
    double  viewport_width;
    double  aspect_ratio;
    double  theta;
    double  h;
    t_v3    w, u, v; // Basis vectors

    cam = &world->camera;
    aspect_ratio = (double)world->width / (double)world->height;
    
    // FOV to Dimensions
    theta = cam->fov * M_PI / 180.0;
    h = tan(theta / 2.0);
    viewport_height = 2.0 * h;
    viewport_width = aspect_ratio * viewport_height;
    
    // Camera Basis (LookAt logic)
    // We need an "up" vector. Assuming (0,1,0) usually.
    // Handle edge case where dir is parallel to world up.
    t_v3 world_up = vec_new(0, 1, 0);
    
    // Check if dir is vertical
    if (fabs(cam->dir.y) > 0.99)
        world_up = vec_new(0, 0, 1);

    cam->dir = vec_unit(cam->dir); // Ensure normalized
    w = vec_scale(cam->dir, -1.0); // Backend usually looks -Z, but here let's align w with -direction?
    // Wait, standard ray tracing: w is opposite to view direction.
    // If cam->dir is where we look, w = -dir.
    
    u = vec_unit(vec_cross(world_up, w));
    v = vec_cross(w, u);
    
    // For standard coord system (right handed), usually:
    // cam->dir is forward.
    // Let's stick thereto:
    // w (forward) = cam->dir
    // right = cross(up, w) OR cross(w, up) depending on coords.
    // Let's use simplified approach if unsure:
    // Horizontal = width * u
    // Vertical = height * v
    // Lower_Left = Origin - Hor/2 - Ver/2 - FocalLength*w
    
    // Re-eval using w = -dir convention:
    w = vec_scale(cam->dir, -1.0);
    u = vec_unit(vec_cross(world_up, w));
    v = vec_cross(w, u);
    
    cam->horizontal = vec_scale(u, viewport_width);
    cam->vertical = vec_scale(v, viewport_height);
    
    // lower_left_corner = origin - horizontal/2 - vertical/2 - w
    t_v3 half_hor = vec_scale(cam->horizontal, 0.5);
    t_v3 half_ver = vec_scale(cam->vertical, 0.5);
    
    cam->low_left = vec_sub(cam->pos, half_hor);
    cam->low_left = vec_sub(cam->low_left, half_ver);
    cam->low_left = vec_sub(cam->low_left, w);
}

/*
 * Generate Ray for Pixel (u, v)
 * u, v are ratios [0, 1]
 */
t_ray get_ray(t_world *world, double u, double v)
{
    t_ray   r;
    t_view  *cam;
    t_v3    hor_comp;
    t_v3    ver_comp;

    cam = &world->camera;
    r.orig = cam->pos;
    
    // Target = LowLeft + u*Hor + v*Ver
    hor_comp = vec_scale(cam->horizontal, u);
    ver_comp = vec_scale(cam->vertical, v);
    
    t_v3 target = vec_add(cam->low_left, hor_comp);
    target = vec_add(target, ver_comp);
    
    r.dir = vec_sub(target, cam->pos);
    // r.dir = vec_unit(r.dir); // Ray direction is usually normalized? 
    // Usually yes, but strictly it doesn't have to be if t is scaled. 
    // But engine functions often expect normalized D.
    r.dir = vec_unit(r.dir);
    
    return (r);
}
