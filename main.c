/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:37 by esir              #+#    #+#             */
/*   Updated: 2026/02/26 12:03:48 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_scene	scene;
	t_data	data;
	t_app	app;

	if (argc != 2)
		return (1);
	init_scene(&scene);
	app.scene = &scene;
	app.data = &data;
	if (!parse_file(argv[1], &scene))
		return (1);
	if (init_mlx(&data) != 0)
	{
		cleanup_scene(&scene);
		cleanup_mlx(&data);
		return (1);
	}
	render_scene(&data, &scene);
	mlx_hook(data.win, 17, 0, close_window, &app);
	mlx_loop(data.mlx);
	cleanup_mlx(&data);
	cleanup_scene(&scene);
	return (0);
}
