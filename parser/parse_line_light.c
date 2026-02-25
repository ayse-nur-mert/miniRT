/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:17:26 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 16:31:50 by amert            ###   ########.fr       */
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

static bool	parse_light_values(char **t, t_vec3 *pos,
				double *bright, t_vec3 *color)
{
	if (!parse_vec3(t[1], pos))
		return (false);
	if (!parse_double_str(t[2], bright)
		|| *bright < 0.0 || *bright > 1.0)
		return (false);
	if (!parse_color255(t[3], color))
		return (false);
	return (true);
}

static bool	scene_push_light(t_scene *scene, t_vec3 pos,
				double bright, t_vec3 color)
{
	t_light	*l;

	l = (t_light *)malloc(sizeof(t_light));
	if (!l)
		return (false);
	l->position = pos;
	l->brightness = bright;
	l->color = color;
	l->next = NULL;
	if (!scene_add_light(scene, l))
	{
		free(l);
		return (false);
	}
	return (true);
}

bool	parse_line_light(const char *line, t_scene *scene)
{
	char	**t;
	t_vec3	pos;
	t_vec3	color;
	double	bright;

	t = split_ws(line);
	if (!t)
		return (false);
	if (!(is_id_token(t[0], 'L') && t[1] && t[2] && t[3] && !t[4]))
		return (free_tokens_false(t));
	if (!parse_light_values(t, &pos, &bright, &color))
		return (free_tokens_false(t));
	if (!scene_push_light(scene, pos, bright, color))
		return (free_tokens_false(t));
	free_tokens(t);
	return (true);
}
