/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:00:00 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 18:29:56 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	vec3_in_range(const t_vec3 v, double min, double max)
{
	return (v.x >= min && v.x <= max
		&& v.y >= min && v.y <= max
		&& v.z >= min && v.z <= max);
}

bool	vec3_nonzero(const t_vec3 v)
{
	return (!(v.x == 0.0 && v.y == 0.0 && v.z == 0.0));
}
