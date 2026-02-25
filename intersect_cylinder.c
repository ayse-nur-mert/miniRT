/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:34 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 16:19:28 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	check_cap(t_ray ray, t_vec3 cap, t_vec3 p_norm, t_cylinder *cy)
{
	t_plane	pl;
	double	t;
	t_vec3	p;

	pl.point = cap;
	pl.normal = p_norm;
	t = intersect_plane(ray, &pl);
	if (t > 0.0)
	{
		p = vec_add_scaled(ray.origin, ray.direction, t);
		if (!within_cap_radius(p, cap, cy->normal, cy->diameter * 0.5))
			return (-1.0);
		return (t);
	}
	return (-1.0);
}

static double	intersect_cylinder_caps(t_ray ray, t_cylinder *cy)
{
	t_vec3	cap1;
	t_vec3	cap2;
	double	t1;
	double	t2;

	cap1 = vec_add_scaled(cy->center, cy->normal, cy->height * 0.5);
	cap2 = vec_add_scaled(cy->center, cy->normal, -(cy->height * 0.5));
	t1 = check_cap(ray, cap1, cy->normal, cy);
	t2 = check_cap(ray, cap2, vec_scale(cy->normal, -1.0), cy);
	return (min_pos(t1, t2));
}

static double	check_bounds(t_ray ray, t_cylinder *cy, double t)
{
	t_vec3	p;
	double	m;

	if (t <= 0.0)
		return (-1.0);
	p = vec_add_scaled(ray.origin, ray.direction, t);
	m = vec_dot_product(vec_sub(p, cy->center), cy->normal);
	if (m < -(cy->height * 0.5) || m > (cy->height * 0.5))
		return (-1.0);
	return (t);
}

static double	calc_cy_roots(t_ray ray, t_cylinder *cy, t_vec3 d_p, t_vec3 oc_p)
{
	double	abc[3];
	double	disc;
	double	t1;
	double	t2;

	abc[0] = vec_dot_product(d_p, d_p);
	abc[1] = 2.0 * vec_dot_product(d_p, oc_p);
	abc[2] = cy->diameter * cy->diameter * 0.25;
	abc[2] = vec_dot_product(oc_p, oc_p) - abc[2];
	if (fabs(abc[0]) < 1e-12)
		return (-1.0);
	disc = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (disc < 0.0)
		return (-1.0);
	t1 = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	t1 = check_bounds(ray, cy, t1);
	t2 = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	t2 = check_bounds(ray, cy, t2);
	return (min_pos(t1, t2));
}

double	intersect_cylinder(t_ray ray, t_cylinder *cy)
{
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	t_side;
	double	t_caps;

	if (!cy)
		return (-1.0);
	oc = vec_sub(ray.origin, cy->center);
	d_perp = vec_scale(cy->normal, vec_dot_product(ray.direction, cy->normal));
	d_perp = vec_sub(ray.direction, d_perp);
	oc_perp = vec_scale(cy->normal, vec_dot_product(oc, cy->normal));
	oc_perp = vec_sub(oc, oc_perp);
	t_side = calc_cy_roots(ray, cy, d_perp, oc_perp);
	t_caps = intersect_cylinder_caps(ray, cy);
	return (min_pos(t_side, t_caps));
}
