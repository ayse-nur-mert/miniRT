#include "parser.h"

bool	parse_line_ambient(const char *line, t_scene *scene)
{
	char	**t;
	double	ratio;
	t_vec3	color;

	t = split_ws(line);
	if (!t)
		return (false);
	if (!(t[0] && t[1] && t[2] && !t[3] && t[0][0] == 'A' && t[0][1] == '\0'))
	{
		free_tokens(t);
		return (false);
	}
	if (scene->has_ambient)
	{
		free_tokens(t);
		return (false);
	}
	if (!parse_double_str(t[1], &ratio) || ratio < 0.0 || ratio > 1.0 || !parse_color255(t[2], &color))
	{
		free_tokens(t);
		return (false);
	}
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
	if (!(t[0] && t[1] && t[2] && t[3] && !t[4] && t[0][0] == 'C' && t[0][1] == '\0'))
	{
		free_tokens(t);
		return (false);
	}
	if (scene->has_camera)
	{
		free_tokens(t);
		return (false);
	}
	if (!parse_vec3(t[1], &pos) || !parse_vec3(t[2], &ori) || !vec3_in_range(ori, -1.0, 1.0) || !vec3_nonzero(ori) || !parse_int_str(t[3], &fov) || fov < 0 || fov > 180)
	{
		free_tokens(t);
		return (false);
	}
	scene->camera.position = pos;
	scene->camera.orientation = vec_normalize(ori);
	scene->camera.fov = fov;
	scene->has_camera = true;
	free_tokens(t);
	return (true);
}
