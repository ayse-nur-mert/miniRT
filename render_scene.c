#include "miniRT.h"

#define EPS 1e-4

static t_vec3	vec_scale(t_vec3 v, double s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
}

static t_vec3	vec_add_scaled(t_vec3 a, t_vec3 b, double s)
{
	return ((t_vec3){a.x + b.x * s, a.y + b.y * s, a.z + b.z * s});
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!data || !data->addr)
		return;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static int	pack_rgb(t_vec3 c)
{
	int	r;
	int	g;
	int	b;

	r = (int)lrint(c.x);
	g = (int)lrint(c.y);
	b = (int)lrint(c.z);
	if (r < 0) r = 0;
	if (r > 255) r = 255;
	if (g < 0) g = 0;
	if (g > 255) g = 255;
	if (b < 0) b = 0;
	if (b > 255) b = 255;
	return ((r << 16) | (g << 8) | b);
}

static t_vec3	clamp_color255(t_vec3 c)
{
	if (c.x < 0.0) c.x = 0.0;
	if (c.x > 255.0) c.x = 255.0;
	if (c.y < 0.0) c.y = 0.0;
	if (c.y > 255.0) c.y = 255.0;
	if (c.z < 0.0) c.z = 0.0;
	if (c.z > 255.0) c.z = 255.0;
	return (c);
}

static t_vec3	color_mul255(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){(a.x * b.x) / 255.0, (a.y * b.y) / 255.0, (a.z * b.z) / 255.0});
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

static t_vec3	get_normal_at_hit(t_object *obj, t_vec3 p)
{
	if (obj->type == SPHERE)
	{
		t_sphere *sp = (t_sphere *)obj->data;
		return (vec_normalize(vec_sub(p, sp->center)));
	}
	if (obj->type == PLANE)
	{
		t_plane *pl = (t_plane *)obj->data;
		return (pl->normal);
	}
	if (obj->type == CYLINDER)
	{
		t_cylinder	*cy;
		t_vec3		axis;
		t_vec3		cp;
		double		m;
		double		half_h;
		cy = (t_cylinder *)obj->data;
		axis = cy->normal;
		half_h = cy->height * 0.5;
		m = vec_dot_product(vec_sub(p, cy->center), axis);
		if (fabs(m - half_h) < 1e-3)
			return (axis);
		if (fabs(m + half_h) < 1e-3)
			return (vec_scale(axis, -1.0));
		cp = vec_add_scaled(cy->center, axis, m);
		return (vec_normalize(vec_sub(p, cp)));
	}
	return ((t_vec3){0.0, 1.0, 0.0});
}

static t_vec3	shade_hit(t_scene *scene, t_object *hit, t_vec3 p, t_vec3 n)
{
	t_vec3	result;
	t_vec3	ambient;
	t_light	*l;
	t_vec3	to_light;
	double	dist;
	t_vec3	ldir;
	double	diff;
	double	intensity;
	t_vec3	light_contrib;
	t_vec3	base;

	base = hit->color;
	ambient = color_mul255(scene->ambient.color, base);
	result = vec_mult_scalar(ambient, scene->ambient.ratio);
	l = scene->lights;
	while (l)
	{
		if (!is_in_shadow(scene, p, n, l))
		{
			to_light = vec_sub(l->position, p);
			dist = vec_magnitude(to_light);
			if (dist > EPS)
			{
				ldir = vec_divide_scalar(to_light, dist);
				diff = vec_dot_product(n, ldir);
				if (diff > 0.0)
				{
					intensity = l->brightness * diff;
					light_contrib = color_mul255(l->color, base);
					result = vec_add(result, vec_mult_scalar(light_contrib, intensity));
				}
			}
		}
		l = l->next;
	}
	return (clamp_color255(result));
}

static t_object	*get_closest_object(t_ray ray, t_object *objects, double *out_t)
{
	t_object	*current;
	t_object	*hit;
	double		closest_t;
	double		current_t;

	current = objects;
	hit = NULL;
	closest_t = -1.0;
	while (current)
	{
		current_t = check_intersection(ray, current);
		if (current_t > 0.0 && (closest_t < 0.0 || current_t < closest_t))
		{
			closest_t = current_t;
			hit = current;
		}
		current = current->next;
	}
	if (out_t)
		*out_t = closest_t;
	return (hit);
}

t_ray	generate_ray(int x, int y, t_scene *scene, double fov_fact)
{
	t_ray	ray;
	t_vec3	temp;
	t_vec3	forward;
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	up;
	t_vec3	dir;

	ray.origin = scene->camera.position;
	temp.x = ndc_x(x) * ASPECT_RATIO * fov_fact;
	temp.y = ndc_y(y) * fov_fact;
	temp.z = 1.0;
	forward = vec_normalize(scene->camera.orientation);
	world_up = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(vec_dot_product(forward, world_up)) > 0.999)
		world_up = (t_vec3){0.0, 0.0, 1.0};
	right = vec_normalize(vec_cross_product(world_up, forward));
	up = vec_cross_product(forward, right);
	dir = vec_add(vec_add(vec_scale(right, temp.x), vec_scale(up, temp.y)), forward);
	ray.direction = vec_normalize(dir);
	return (ray);
}

double	get_closest_intersection(t_ray ray, t_object *objects)
{
	t_object	*current;
	double		closest_t;
	double		current_t;

	current = objects;
	closest_t = -1.0;
	while (current != NULL)
	{
		current_t = check_intersection(ray, current);
		if (current_t > 0 && (closest_t == -1.0 || current_t < closest_t))
			closest_t = current_t;
		current = current->next;
	}
	return (closest_t);
}

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	return (0);
}

void	render_scene(t_data *data, t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	double	fov_fact;
	double	closest_t;
	t_object	*hit;
	int		color;
	t_vec3	p;
	t_vec3	n;
	t_vec3	shaded;

	fov_fact = fov_factor(scene->camera.fov);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(x, y, scene, fov_fact);
			hit = get_closest_object(ray, scene->objects, &closest_t);
			if (hit && closest_t > 0.0)
			{
				p = vec_add_scaled(ray.origin, ray.direction, closest_t);
				n = get_normal_at_hit(hit, p);
				if (vec_dot_product(n, ray.direction) > 0.0)
					n = vec_scale(n, -1.0);
				shaded = shade_hit(scene, hit, p, n);
				color = pack_rgb(shaded);
			}
			else
				color = 0x000000;
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
