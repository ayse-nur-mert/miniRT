/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:17:29 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 18:29:56 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_object	*new_object(t_obj_type type, void *data, t_vec3 color)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->data = data;
	obj->color = color;
	obj->next = NULL;
	return (obj);
}

static bool	parse_object_sphere(char **t, t_scene *scene)
{
	t_sphere	*sp;
	t_vec3		center;
	t_vec3		color;
	double		diameter;
	t_object	*obj;

	if (!(t[0] && t[1] && t[2] && t[3] && !t[4]
			&& t[0][0] == 's' && t[0][1] == 'p' && t[0][2] == '\0'))
		return (false);
	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp)
		return (false);
	if (!parse_vec3(t[1], &center)
		|| !parse_double_str(t[2], &diameter) || diameter <= 0.0
		|| !parse_color255(t[3], &color))
		return (free(sp), false);
	sp->center = center;
	sp->diameter = diameter;
	obj = new_object(SPHERE, sp, color);
	if (!obj)
		return (free(sp), false);
	scene_add_object(scene, obj);
	return (true);
}

static bool	parse_object_plane(char **t, t_scene *scene)
{
	t_plane		*pl;
	t_vec3		point;
	t_vec3		normal;
	t_vec3		color;
	t_object	*obj;

	if (!(t[0] && t[1] && t[2] && t[3] && !t[4]
			&& t[0][0] == 'p' && t[0][1] == 'l' && t[0][2] == '\0'))
		return (false);
	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl)
		return (false);
	if (!parse_vec3(t[1], &point)
		|| !parse_vec3(t[2], &normal)
		|| !vec3_in_range(normal, -1.0, 1.0) || !vec3_nonzero(normal)
		|| !parse_color255(t[3], &color))
		return (free(pl), false);
	pl->point = point;
	pl->normal = vec_normalize(normal);
	obj = new_object(PLANE, pl, color);
	if (!obj)
		return (free(pl), false);
	scene_add_object(scene, obj);
	return (true);
}

static bool	parse_object_cylinder(char **t, t_scene *scene)
{
	t_cylinder	*cy;
	t_vec3		color;
	t_object	*obj;

	if (!(t[0] && t[1] && t[2] && t[3] && t[4] && t[5] && !t[6]
			&& t[0][0] == 'c' && t[0][1] == 'y' && t[0][2] == '\0'))
		return (false);
	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (false);
	if (!parse_vec3(t[1], &cy->center)
		|| !parse_vec3(t[2], &cy->normal)
		|| !vec3_in_range(cy->normal, -1.0, 1.0) || !vec3_nonzero(cy->normal)
		|| !parse_double_str(t[3], &cy->diameter) || cy->diameter <= 0.0
		|| !parse_double_str(t[4], &cy->height) || cy->height <= 0.0
		|| !parse_color255(t[5], &color))
		return (free(cy), false);
	cy->normal = vec_normalize(cy->normal);
	obj = new_object(CYLINDER, cy, color);
	if (!obj)
		return (free(cy), false);
	scene_add_object(scene, obj);
	return (true);
}

bool	parse_line_object(const char *line, t_scene *scene)
{
	char	**t;
	bool	ok;

	t = split_ws(line);
	if (!t)
		return (false);
	ok = parse_object_sphere(t, scene);
	if (!ok)
		ok = parse_object_plane(t, scene);
	if (!ok)
		ok = parse_object_cylinder(t, scene);
	free_tokens(t);
	return (ok);
}
