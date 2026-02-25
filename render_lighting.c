/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:57:15 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 17:13:42 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define EPS 1e-4

static bool	is_in_shadow(t_scene *scene, t_vec3 p, t_vec3 n, t_light *light)
{
	t_ray	shadow;
	t_vec3	to_light;
	double	dist;
	double	t;

	to_light = vec_sub(light->position, p);
	dist = vec_magnitude(to_light);
	if (dist <= EPS)
		return (false);
	shadow.origin = vec_add_scaled(p, n, EPS);
	shadow.direction = vec_divide_scalar(to_light, dist);
	t = get_closest_intersection(shadow, scene->objects);
	return (t > EPS && t < dist - EPS);
}

static t_vec3	add_light_contrib(t_scene *sc, t_vec3 p, t_vec3 n, t_object *hit)
{
	t_vec3	res;
	t_light	*l;
	t_vec3	dir;
	t_vec3	lc;
	double	diff;

	res = (t_vec3){0, 0, 0};
	l = sc->lights;
	while (l)
	{
		if (!is_in_shadow(sc, p, n, l))
		{
			dir = vec_sub(l->position, p);
			if (vec_magnitude(dir) > EPS)
			{
				diff = vec_dot_product(n, vec_normalize(dir));
				if (diff > 0.0)
				{
					lc = color_mul255(l->color, hit->color);
					res = vec_add(res, vec_mult_scalar(lc, l->brightness * diff));
				}
			}
		}
		l = l->next;
	}
	return (res);
}

t_vec3	shade_hit(t_scene *scene, t_object *hit, t_vec3 p, t_vec3 n)
{
	t_vec3	res;
	t_vec3	ambient;

	ambient = color_mul255(scene->ambient.color, hit->color);
	res = vec_mult_scalar(ambient, scene->ambient.ratio);
	res = vec_add(res, add_light_contrib(scene, p, n, hit));
	return (clamp_color255(res));
}