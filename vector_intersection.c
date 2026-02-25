#include "miniRT.h"

double check_intersection(t_ray ray, t_object *obj)
{
	double t;

	t = -1.0;
	if (obj->type == SPHERE)
		t = intersect_spere(ray, (t_sphere *)obj->data);
	else if (obj->type == PLANE)
		t = intersect_plane(ray, (t_plane *)obj->data);
	else if (obj->type == CYLINDER)
		t = intersect_cylinder(ray, (t_cylinder *)obj->data);
	return (t);
}