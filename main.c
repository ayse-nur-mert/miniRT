/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:37 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 16:28:19 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_scene	scene;
	t_data	data;

	if (argc != 2)
		return (1);
	init_scene(&scene);
	if (!parse_file(argv[1], &scene))
		return (1);
	if (init_mlx(&data) != 0)
	{
		free_scene(&scene);
		return (1);
	}
	render_scene(&data, &scene);
	mlx_loop(data.mlx);
	free_scene(&scene);
	return (0);
}
