/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_camera_ambient.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:17:22 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 16:23:17 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	free_tokens_false(char **t)
{
	free_tokens(t);
	return (false);
}

static bool	is_id_token(const char *tok, char id)
{
	return (tok && tok[0] == id && tok[1] == '\0');
}

static bool	parse_camera_values(char **t, t_vec3 *pos, t_vec3 *ori, int *fov)
{
	if (!parse_vec3(t[1], pos) || !parse_vec3(t[2], ori))
		return (false);
	if (!vec3_in_range(*ori, -1.0, 1.0) || !vec3_nonzero(*ori))
		return (false);
	if (!parse_int_str(t[3], fov) || *fov < 0 || *fov > 180)
		return (false);
	return (true);
}

bool	parse_line_ambient(const char *line, t_scene *scene)
{
	char	**t;
	double	ratio;
	t_vec3	color;

	t = split_ws(line);
	if (!t)
		return (false);
	if (!(is_id_token(t[0], 'A') && t[1] && t[2] && !t[3]))
		return (free_tokens_false(t));
	if (scene->has_ambient)
		return (free_tokens_false(t));
	if (!parse_double_str(t[1], &ratio)
		|| ratio < 0.0 || ratio > 1.0
		|| !parse_color255(t[2], &color))
		return (free_tokens_false(t));
	scene->ambient.ratio = ratio;
	scene->ambient.color = color;
	scene->has_ambient = true;
	free_tokens(t);
	return (true);
}

bool	parse_line_camera(const char *line, t_scene *scene)
{
	char	**t;
	t_vec3	pos;
	t_vec3	ori;
	int		fov;

	t = split_ws(line);
	if (!t)
		return (false);
	if (!(is_id_token(t[0], 'C') && t[1] && t[2] && t[3] && !t[4]))
		return (free_tokens_false(t));
	if (scene->has_camera)
		return (free_tokens_false(t));
	if (!parse_camera_values(t, &pos, &ori, &fov))
		return (free_tokens_false(t));
	scene->camera.position = pos;
	scene->camera.orientation = vec_normalize(ori);
	scene->camera.fov = fov;
	scene->has_camera = true;
	free_tokens(t);
	return (true);
}
