/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:47 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 17:09:32 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define EPS 1e-4

t_ray	generate_ray(int x, int y, t_scene *sc, double fov_fact)
{
	t_ray	r;
	t_vec3	tmp;
	t_vec3	fwd;
	t_vec3	up;
	t_vec3	rht;

	r.origin = sc->camera.position;
	tmp.x = ndc_x(x) * ASPECT_RATIO * fov_fact;
	tmp.y = ndc_y(y) * fov_fact;
	fwd = vec_normalize(sc->camera.orientation);
	up = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(vec_dot_product(fwd, up)) > 0.999)
		up = (t_vec3){0.0, 0.0, 1.0};
	rht = vec_normalize(vec_cross_product(up, fwd));
	up = vec_cross_product(fwd, rht);
	r.direction = vec_add(vec_scale(rht, tmp.x), vec_scale(up, tmp.y));
	r.direction = vec_normalize(vec_add(r.direction, fwd));
	return (r);
}

static int	get_pixel_color(t_scene *scene, t_ray ray)
{
	t_object	*hit;
	double		t;
	t_vec3		p;
	t_vec3		n;

	hit = get_closest_object(ray, scene->objects, &t);
	if (hit && t > 0.0)
	{
		p = vec_add_scaled(ray.origin, ray.direction, t);
		n = get_normal_at_hit(hit, p);
		if (vec_dot_product(n, ray.direction) > 0.0)
			n = vec_scale(n, -1.0);
		return (pack_rgb(shade_hit(scene, hit, p, n)));
	}
	return (0x000000); // Background color
}

void	render_scene(t_data *data, t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	double	fov_fact;

	fov_fact = fov_factor(scene->camera.fov);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(x, y, scene, fov_fact);
			my_mlx_pixel_put(data, x, y, get_pixel_color(scene, ray));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
