/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:20:00 by amert             #+#    #+#             */
/*   Updated: 2026/02/26 12:14:28 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	free_object_node(t_object *obj)
{
	if (!obj)
		return ;
	free(obj->data);
	free(obj);
}

void	free_objects(t_object **objects)
{
	t_object	*obj;
	t_object	*next;

	if (!objects)
		return ;
	obj = *objects;
	while (obj)
	{
		next = obj->next;
		free_object_node(obj);
		obj = next;
	}
	*objects = NULL;
}

void	free_lights(t_light **lights)
{
	t_light	*light;
	t_light	*next;

	if (!lights)
		return ;
	light = *lights;
	while (light)
	{
		next = light->next;
		free(light);
		light = next;
	}
	*lights = NULL;
}

void	cleanup_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_objects(&scene->objects);
	free_lights(&scene->lights);
}

void	free_scene(t_scene *scene)
{
	cleanup_scene(scene);
}
