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

bool	parse_line_object(const char *line, t_scene *scene)
{
	char	**t;
	t_vec3	color;
	t_vec3	v1;
	t_vec3	v2;
	double	d1;
	double	d2;

	t = split_ws(line);
	if (!t)
		return (false);
	if (t[0] && t[1] && t[2] && t[3] && !t[4] && t[0][0] == 's' && t[0][1] == 'p' && t[0][2] == '\0')
	{
		t_sphere *sp = (t_sphere *)malloc(sizeof(t_sphere));
		if (!sp || !parse_vec3(t[1], &v1) || !parse_double_str(t[2], &d1) || d1 <= 0.0 || !parse_color255(t[3], &color))
		{
			free(sp);
			free_tokens(t);
			return (false);
		}
		sp->center = v1;
		sp->diameter = d1;
		if (!scene_add_object(scene, new_object(SPHERE, sp, color)))
		{
			free(sp);
			free_tokens(t);
			return (false);
		}
		free_tokens(t);
		return (true);
	}
	if (t[0] && t[1] && t[2] && t[3] && !t[4] && t[0][0] == 'p' && t[0][1] == 'l' && t[0][2] == '\0')
	{
		t_plane *pl = (t_plane *)malloc(sizeof(t_plane));
		if (!pl || !parse_vec3(t[1], &v1) || !parse_vec3(t[2], &v2) || !vec3_in_range(v2, -1.0, 1.0) || !vec3_nonzero(v2) || !parse_color255(t[3], &color))
		{
			free(pl);
			free_tokens(t);
			return (false);
		}
		pl->point = v1;
		pl->normal = vec_normalize(v2);
		if (!scene_add_object(scene, new_object(PLANE, pl, color)))
		{
			free(pl);
			free_tokens(t);
			return (false);
		}
		free_tokens(t);
		return (true);
	}
	if (t[0] && t[1] && t[2] && t[3] && t[4] && t[5] && !t[6] && t[0][0] == 'c' && t[0][1] == 'y' && t[0][2] == '\0')
	{
		t_cylinder *cy = (t_cylinder *)malloc(sizeof(t_cylinder));
		if (!cy || !parse_vec3(t[1], &v1) || !parse_vec3(t[2], &v2) || !vec3_in_range(v2, -1.0, 1.0) || !vec3_nonzero(v2)
			|| !parse_double_str(t[3], &d1) || d1 <= 0.0 || !parse_double_str(t[4], &d2) || d2 <= 0.0 || !parse_color255(t[5], &color))
		{
			free(cy);
			free_tokens(t);
			return (false);
		}
		cy->center = v1;
		cy->normal = vec_normalize(v2);
		cy->diameter = d1;
		cy->height = d2;
		if (!scene_add_object(scene, new_object(CYLINDER, cy, color)))
		{
			free(cy);
			free_tokens(t);
			return (false);
		}
		free_tokens(t);
		return (true);
	}
	free_tokens(t);
	return (false);
}
