#include "parser.h"

bool	parse_line_light(const char *line, t_scene *scene)
{
	char	**t;
	t_vec3	pos;
	t_vec3	color;
	double	bright;
	t_light	*l;

	t = split_ws(line);
	if (!t)
		return (false);
	if (!(t[0] && t[1] && t[2] && t[3] && !t[4] && t[0][0] == 'L' && t[0][1] == '\0'))
	{
		free_tokens(t);
		return (false);
	}
	if (!parse_vec3(t[1], &pos) || !parse_double_str(t[2], &bright) || bright < 0.0 || bright > 1.0 || !parse_color255(t[3], &color))
	{
		free_tokens(t);
		return (false);
	}
	l = (t_light *)malloc(sizeof(t_light));
	if (!l)
	{
		free_tokens(t);
		return (false);
	}
	l->position = pos;
	l->brightness = bright;
	l->color = color;
	l->next = NULL;
	if (!scene_add_light(scene, l))
	{
		free(l);
		free_tokens(t);
		return (false);
	}
	free_tokens(t);
	return (true);
}
