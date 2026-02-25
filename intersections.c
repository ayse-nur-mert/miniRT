#include "miniRT.h"

static t_vec3	vec_scale(t_vec3 v, double s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
}

static t_vec3	vec_add_scaled(t_vec3 a, t_vec3 b, double s)
{
	return ((t_vec3){a.x + b.x * s, a.y + b.y * s, a.z + b.z * s});
}

static double	min_pos(double a, double b)
{
	if (a > 0.0 && b > 0.0)
		return (a < b ? a : b);
	if (a > 0.0)
		return (a);
	if (b > 0.0)
		return (b);
	return (-1.0);
}

double	intersect_spere(t_ray ray, t_sphere *sphere)
{
	t_vec3	oc;
	double	r;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	sqrt_disc;
	double	t1;
	double	t2;

	if (!sphere)
		return (-1.0);
	r = sphere->diameter * 0.5;
	oc = vec_sub(ray.origin, sphere->center);
	a = vec_dot_product(ray.direction, ray.direction);
	b = 2.0 * vec_dot_product(oc, ray.direction);
	c = vec_dot_product(oc, oc) - (r * r);
	disc = (b * b) - (4.0 * a * c);
	if (disc < 0.0)
		return (-1.0);
	sqrt_disc = sqrt(disc);
	t1 = (-b - sqrt_disc) / (2.0 * a);
	t2 = (-b + sqrt_disc) / (2.0 * a);
	return (min_pos(t1, t2));
}

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

static bool	within_cap_radius(t_vec3 p, t_vec3 cap_center, t_vec3 axis, double r)
{
	t_vec3	d;
	t_vec3	perp;

	d = vec_sub(p, cap_center);
	perp = vec_sub(d, vec_scale(axis, vec_dot_product(d, axis)));
	return (vec_dot_product(perp, perp) <= r * r);
}

static double	intersect_cylinder_caps(t_ray ray, t_cylinder *cy, t_vec3 axis, double half_h, double r)
{
	t_vec3	cap1;
	t_vec3	cap2;
	t_plane	pl;
	t_vec3	p;
	double	t1;
	double	t2;

	cap1 = vec_add_scaled(cy->center, axis, half_h);
	cap2 = vec_add_scaled(cy->center, axis, -half_h);

	pl.point = cap1;
	pl.normal = axis;
	t1 = intersect_plane(ray, &pl);
	if (t1 > 0.0)
	{
		p = vec_add_scaled(ray.origin, ray.direction, t1);
		if (!within_cap_radius(p, cap1, axis, r))
			t1 = -1.0;
	}

	pl.point = cap2;
	pl.normal = vec_scale(axis, -1.0);
	t2 = intersect_plane(ray, &pl);
	if (t2 > 0.0)
	{
		p = vec_add_scaled(ray.origin, ray.direction, t2);
		if (!within_cap_radius(p, cap2, axis, r))
			t2 = -1.0;
	}
	return (min_pos(t1, t2));
}

double	intersect_cylinder(t_ray ray, t_cylinder *cylinder)
{
	t_vec3	axis;
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	r;
	double	half_h;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	sqrt_disc;
	double	t_side1;
	double	t_side2;
	double	t_side;
	double	m;
	t_vec3	p;
	double	t_caps;

	if (!cylinder)
		return (-1.0);
	axis = cylinder->normal;
	r = cylinder->diameter * 0.5;
	half_h = cylinder->height * 0.5;

	oc = vec_sub(ray.origin, cylinder->center);
	d_perp = vec_sub(ray.direction, vec_scale(axis, vec_dot_product(ray.direction, axis)));
	oc_perp = vec_sub(oc, vec_scale(axis, vec_dot_product(oc, axis)));

	a = vec_dot_product(d_perp, d_perp);
	b = 2.0 * vec_dot_product(d_perp, oc_perp);
	c = vec_dot_product(oc_perp, oc_perp) - (r * r);
	if (fabs(a) < 1e-12)
		return (intersect_cylinder_caps(ray, cylinder, axis, half_h, r));
	disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		t_side = -1.0;
	else
	{
		sqrt_disc = sqrt(disc);
		t_side1 = (-b - sqrt_disc) / (2.0 * a);
		t_side2 = (-b + sqrt_disc) / (2.0 * a);
		t_side = min_pos(t_side1, t_side2);
		if (t_side > 0.0)
		{
			p = vec_add_scaled(ray.origin, ray.direction, t_side);
			m = vec_dot_product(vec_sub(p, cylinder->center), axis);
			if (m < -half_h || m > half_h)
				t_side = -1.0;
		}
	}
	if (t_side > 0.0)
		return (t_side);
	t_caps = intersect_cylinder_caps(ray, cylinder, axis, half_h, r);
	return (t_caps);
}
