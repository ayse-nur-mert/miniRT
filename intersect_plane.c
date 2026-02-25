/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:14 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 16:01:15 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_plane(t_ray ray, t_plane *plane)
{
	double	denom;
	double	t;
	t_vec3	p0l0;

	if (!plane)
		return (-1.0);
	denom = vec_dot_product(plane->normal, ray.direction);
	if (fabs(denom) < 1e-9)
		return (-1.0);
	p0l0 = vec_sub(plane->point, ray.origin);
	t = vec_dot_product(p0l0, plane->normal) / denom;
	if (t <= 1e-6)
		return (-1.0);
	return (t);
}
