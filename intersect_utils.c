/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:07 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 16:10:55 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec_scale(t_vec3 v, double s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
}

t_vec3	vec_add_scaled(t_vec3 a, t_vec3 b, double s)
{
	return ((t_vec3){a.x + b.x * s, a.y + b.y * s, a.z + b.z * s});
}

double	min_pos(double a, double b)
{
	if (a > 0.0 && b > 0.0)
	{
		if (a < b)
			return (a);
		return (b);
	}
	if (a > 0.0)
		return (a);
	if (b > 0.0)
		return (b);
	return (-1.0);
}

bool	within_cap_radius(t_vec3 p, t_vec3 cap_center, t_vec3 axis, double r)
{
	t_vec3	d;
	t_vec3	perp;

	d = vec_sub(p, cap_center);
	perp = vec_sub(d, vec_scale(axis, vec_dot_product(d, axis)));
	return (vec_dot_product(perp, perp) <= r * r);
}
