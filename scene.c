#include "miniRT.h"

static void	free_object_node(t_object *obj)
{
	if (!obj)
		return;
	free(obj->data);
	free(obj);
}

void	init_scene(t_scene *scene)
{
	if (!scene)
		return;
	scene->objects = NULL;
	scene->lights = NULL;
	scene->has_camera = false;
	scene->has_ambient = false;
	scene->camera.position = (t_vec3){0.0, 0.0, 0.0};
	scene->camera.orientation = (t_vec3){0.0, 0.0, 1.0};
	scene->camera.fov = 60;
	scene->ambient.ratio = 0.0;
	scene->ambient.color = (t_vec3){0.0, 0.0, 0.0};
}

bool	scene_add_object(t_scene *scene, t_object *obj)
{
	t_object	*tail;

	if (!scene || !obj)
		return (false);
	obj->next = NULL;
	if (!scene->objects)
	{
		scene->objects = obj;
		return (true);
	}
	tail = scene->objects;
	while (tail->next)
		tail = tail->next;
	tail->next = obj;
	return (true);
}

bool	scene_add_light(t_scene *scene, t_light *light)
{
	t_light	*tail;

	if (!scene || !light)
		return (false);
	light->next = NULL;
	if (!scene->lights)
	{
		scene->lights = light;
		return (true);
	}
	tail = scene->lights;
	while (tail->next)
		tail = tail->next;
	tail->next = light;
	return (true);
}

void	free_scene(t_scene *scene)
{
	t_object	*obj;
	t_object	*next_obj;
	t_light	*light;
	t_light	*next_light;

	if (!scene)
		return;
	obj = scene->objects;
	while (obj)
	{
		next_obj = obj->next;
		free_object_node(obj);
		obj = next_obj;
	}
	scene->objects = NULL;
	light = scene->lights;
	while (light)
	{
		next_light = light->next;
		free(light);
		light = next_light;
	}
	scene->lights = NULL;
}
