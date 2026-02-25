/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:59 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 16:13:50 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec_mult_scalar(t_vec3 vector, double scalar)
{
	t_vec3	result;

	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	result.z = vector.z * scalar;
	return (result);
}

t_vec3	vec_divide_scalar(t_vec3 vector, double scalar)
{
	t_vec3	result;

	result.x = vector.x / scalar;
	result.y = vector.y / scalar;
	result.z = vector.z / scalar;
	return (result);
}

double	vec_magnitude(t_vec3 vector)
{
	double	result;
	double	x;
	double	y;
	double	z;

	x = vector.x * vector.x;
	y = vector.y * vector.y;
	z = vector.z * vector.z;
	result = sqrt(x + y + z);
	return (result);
}

t_vec3	vec_normalize(t_vec3 vector)
{
	t_vec3	result;
	double	magnitude;

	magnitude = vec_magnitude(vector);
	result.x = vector.x / magnitude;
	result.y = vector.y / magnitude;
	result.z = vector.z / magnitude;
	return (result);
}

double	vec_dot_product(t_vec3 vector1, t_vec3 vector2)
{
	double	result;
	double	x;
	double	y;
	double	z;

	x = vector1.x * vector2.x;
	y = vector1.y * vector2.y;
	z = vector1.z * vector2.z;
	result = x + y + z;
	return (result);
}
