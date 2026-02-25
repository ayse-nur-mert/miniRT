/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:56 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 16:04:22 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec_add(t_vec3 vector1, t_vec3 vector2)
{
	t_vec3	result;

	result.x = vector1.x + vector2.x;
	result.y = vector1.y + vector2.y;
	result.z = vector1.z + vector2.z;
	return (result);
}

t_vec3	vec_sub(t_vec3 vector1, t_vec3 vector2)
{
	t_vec3	result;

	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return (result);
}

t_vec3	vec_mult(t_vec3 vector1, t_vec3 vector2)
{
	t_vec3	result;

	result.x = vector1.x * vector2.x;
	result.y = vector1.y * vector2.y;
	result.z = vector1.z * vector2.z;
	return (result);
}

t_vec3	vec_divide(t_vec3 vector1, t_vec3 vector2)
{
	t_vec3	result;

	result.x = vector1.x / vector2.x;
	result.y = vector1.y / vector2.y;
	result.z = vector1.z / vector2.z;
	return (result);
}
