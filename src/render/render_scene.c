#include "../../include/engine.h"
#include "../minilibx-linux/mlx.h" // Assuming mlx path, might need adjustment in Makefile

/* Put pixel to MLX image buffer */
static void my_mlx_pixel_put(t_world *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

/* Convert t_color (0-1) to int (0-255) */
static int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

static int to_int_color(t_color c)
{
    int r = (int)(c.r * 255.99);
    int g = (int)(c.g * 255.99);
    int b = (int)(c.b * 255.99);
    return (create_trgb(0, r, g, b));
}

void render_scene(t_world *world)
{
    int     x;
    int     y;
    double  u;
    double  v;
    t_ray   r;
    t_hit   rec;
    t_color pixel_color;

    // Ensure camera is ready
    init_camera(world);

    y = world->height - 1;
    while (y >= 0)
    {
        x = 0;
        while (x < world->width)
        {
            u = (double)x / (world->width - 1);
            v = (double)y / (world->height - 1); // Often Image Y is inverted relative to V
            
            // Note: If using MLX, (0,0) is usually top-left.
            // But mathematical V usually goes 0 (bottom) to 1 (top).
            // So if y loop goes world->height-1 down to 0, v goes 1 to 0. 
            // Correct for standard view: v should map correctly.
            // If y goes 0 to height, v goes 1 to 0 (top-down raster).
            // Let's stick to standard loop: y=0..height.
            // Then v = (double)(height - 1 - y) / (height - 1)
            // But here I used y loop down. So v goes 1 to 0.
            // Wait, if Y is spatial coordinate, usually Y is up.
            // Screen (0,0) is top-left.
            
            // Let's Refactor loop for clarity: 0 to Height
            
            r = get_ray(world, u, v);
            
            if (hit_world(world, r, &rec))
            {
                pixel_color = compute_shading(world, r, &rec);
            }
            else
            {
                // Background color (e.g., Sky blue or Black)
                pixel_color = (t_color){0, 0, 0}; 
            }
            
            // Write to buffer
            // MLX: Y=0 is top. 
            // My loop y starts at height-1 (Top in math) -> 0.
            // So pixel Y coordinate should be height - 1 - y.
            my_mlx_pixel_put(world, x, world->height - 1 - y, to_int_color(pixel_color));
            
            x++;
        }
        y--;
        // Optional: Progress bar printf("\rScanlines remaining: %d ", y);
    }
}
