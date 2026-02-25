#include "parser.h"

bool	validate_file_content(t_scene *scene)
{
	if (!scene)
		return (false);
	if (!scene->has_ambient)
		return (false);
	if (!scene->has_camera)
		return (false);
	if (!scene->lights)
		return (false);
	if (!scene->objects)
		return (false);
	return (true);
}
