/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:57:15 by esir              #+#    #+#             */
/*   Updated: 2026/02/26 12:14:28 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	vec3_zero(void)
{
	t_vec3	v;

	v.x = 0.0;
	v.y = 0.0;
	v.z = 0.0;
	return (v);
}

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

static double	light_factor(t_scene *sc, t_vec3 p, t_vec3 n, t_light *l)
{
	t_vec3	dir;
	double	dist;
	double	diff;

	if (is_in_shadow(sc, p, n, l))
		return (0.0);
	dir = vec_sub(l->position, p);
	dist = vec_magnitude(dir);
	if (dist <= EPS)
		return (0.0);
	diff = vec_dot_product(n, vec_divide_scalar(dir, dist));
	if (diff <= 0.0)
		return (0.0);
	return (l->brightness * diff);
}

static t_vec3	add_light_contrib(t_scene *sc, t_vec3 p,
			t_vec3 n, t_object *hit)
{
	t_vec3	res;
	t_light	*l;
	t_vec3	lc;
	double	f;

	res = vec3_zero();
	l = sc->lights;
	while (l)
	{
		f = light_factor(sc, p, n, l);
		if (f > 0.0)
		{
			lc = color_mul255(l->color, hit->color);
			res = vec_add(res, vec_mult_scalar(lc, f));
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
