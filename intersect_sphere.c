/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:11 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 16:13:19 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	calc_sphere_roots(double a, double b, double c)
{
	double	disc;
	double	sqrt_d;
	double	t1;
	double	t2;

	disc = (b * b) - (4.0 * a * c);
	if (disc < 0.0)
		return (-1.0);
	sqrt_d = sqrt(disc);
	t1 = (-b - sqrt_d) / (2.0 * a);
	t2 = (-b + sqrt_d) / (2.0 * a);
	return (min_pos(t1, t2));
}

double	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_vec3	oc;
	double	r;
	double	a;
	double	b;
	double	c;

	if (!sphere)
		return (-1.0);
	r = sphere->diameter * 0.5;
	oc = vec_sub(ray.origin, sphere->center);
	a = vec_dot_product(ray.direction, ray.direction);
	b = 2.0 * vec_dot_product(oc, ray.direction);
	c = vec_dot_product(oc, oc) - (r * r);
	return (calc_sphere_roots(a, b, c));
}
