/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:57:58 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 17:12:18 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	pack_rgb(t_vec3 c)
{
	int	r;
	int	g;
	int	b;

	r = (int)lrint(c.x);
	g = (int)lrint(c.y);
	b = (int)lrint(c.z);
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

t_vec3	clamp_color255(t_vec3 c)
{
	if (c.x < 0.0)
		c.x = 0.0;
	if (c.x > 255.0)
		c.x = 255.0;
	if (c.y < 0.0)
		c.y = 0.0;
	if (c.y > 255.0)
		c.y = 255.0;
	if (c.z < 0.0)
		c.z = 0.0;
	if (c.z > 255.0)
		c.z = 255.0;
	return (c);
}

t_vec3	color_mul255(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){(a.x * b.x) / 255.0, (a.y * b.y) / 255.0, (a.z * b.z) / 255.0});
}
