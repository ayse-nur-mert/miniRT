/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:57:42 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 17:14:36 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 p)
{
	t_vec3	cp;
	double	m;

	m = vec_dot_product(vec_sub(p, cy->center), cy->normal);
	if (fabs(m - (cy->height * 0.5)) < 1e-3)
		return (cy->normal);
	if (fabs(m + (cy->height * 0.5)) < 1e-3)
		return (vec_scale(cy->normal, -1.0));
	cp = vec_add_scaled(cy->center, cy->normal, m);
	return (vec_normalize(vec_sub(p, cp)));
}

t_vec3	get_normal_at_hit(t_object *obj, t_vec3 p)
{
	if (obj->type == SPHERE)
		return (vec_normalize(vec_sub(p, ((t_sphere *)obj->data)->center)));
	if (obj->type == PLANE)
		return (((t_plane *)obj->data)->normal);
	if (obj->type == CYLINDER)
		return (get_cylinder_normal((t_cylinder *)obj->data, p));
	return ((t_vec3){0.0, 1.0, 0.0});
}

t_object	*get_closest_object(t_ray ray, t_object *objects, double *out_t)
{
	t_object	*current;
	t_object	*hit;
	double		closest_t;
	double		current_t;

	current = objects;
	hit = NULL;
	closest_t = -1.0;
	while (current)
	{
		current_t = check_intersection(ray, current);
		if (current_t > 0.0 && (closest_t < 0.0 || current_t < closest_t))
		{
			closest_t = current_t;
			hit = current;
		}
		current = current->next;
	}
	if (out_t)
		*out_t = closest_t;
	return (hit);
}

double	get_closest_intersection(t_ray ray, t_object *objects)
{
	t_object	*current;
	double		closest_t;
	double		current_t;

	current = objects;
	closest_t = -1.0;
	while (current != NULL)
	{
		current_t = check_intersection(ray, current);
		if (current_t > 0 && (closest_t == -1.0 || current_t < closest_t))
			closest_t = current_t;
		current = current->next;
	}
	return (closest_t);
}
