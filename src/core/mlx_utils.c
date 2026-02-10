#include "../../include/engine.h"
#include "../minilibx-linux/mlx.h"

#define ESC_KEY 65307

int close_window(t_world *world)
{
    // Free memory + mlx destroy
    if (world->img)
        mlx_destroy_image(world->mlx, world->img);
    if (world->win)
        mlx_destroy_window(world->mlx, world->win);
    // mlx_destroy_display(world->mlx); // Linux only?
    // free(world->mlx);
    exit(0);
    return (0);
}

int key_hook(int keycode, t_world *world)
{
    if (keycode == ESC_KEY)
        close_window(world);
    return (0);
}

void init_mlx_utils(t_world *world)
{
    // These should be set, defaults if not
    if (world->width == 0) world->width = 800; // Default
    if (world->height == 0) world->height = 600;

    world->mlx = mlx_init();
    if (!world->mlx)
        exit(1);
    
    world->win = mlx_new_window(world->mlx, world->width, world->height, "MiniRT Refactored");
    if (!world->win)
        exit(1);
        
    world->img = mlx_new_image(world->mlx, world->width, world->height);
    world->addr = mlx_get_data_addr(world->img, &world->bpp, &world->line_len, &world->endian);

    // Hooks
    mlx_hook(world->win, 17, 0, close_window, world);
    mlx_key_hook(world->win, key_hook, world);
}
