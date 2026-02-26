/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:58:21 by esir              #+#    #+#             */
/*   Updated: 2026/02/26 12:03:48 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!data || !data->addr)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

int	init_mlx(t_data *data)
{
	if (!data)
		return (1);
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (data->win == NULL)
		return (cleanup_mlx(data), 1);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img == NULL)
		return (cleanup_mlx(data), 1);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (data->addr == NULL)
		return (cleanup_mlx(data), 1);
	return (0);
}

void	cleanup_mlx(t_data *data)
{
	if (!data)
		return ;
	if (data->mlx && data->img)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
		data->addr = NULL;
	}
	if (data->mlx && data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}

int	app_exit(t_app *app, int exit_code)
{
	if (app)
	{
		if (app->data)
			cleanup_mlx(app->data);
		if (app->scene)
			cleanup_scene(app->scene);
	}
	exit(exit_code);
	return (exit_code);
}

int	close_window(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	return (app_exit(app, 0));
}
