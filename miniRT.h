/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:43 by esir              #+#    #+#             */
/*   Updated: 2026/02/26 12:20:09 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"

# define WIDTH 800
# define HEIGHT 600
# define PI 3.14159265358979323846
# define EPS 1e-4

typedef struct s_vec3
{
	/* 3D vektor */
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef struct s_sphere
{
	/* Merkez + cap */
	t_vec3	center;
	double	diameter;
}	t_sphere;

typedef struct s_plane
{
	/* Nokta + normal */
	t_vec3	point;
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	/* Merkez + eksen + boyutlar */
	t_vec3	center;
	t_vec3	normal;
	double	diameter;
	double	height;
}	t_cylinder;

typedef struct s_object
{
	/* Sahnedeki geometrik obje node'u */
	t_obj_type		type;
	void			*data;
	t_vec3			color;
	struct s_object	*next;
}	t_object;

typedef struct s_ray
{
	/* Origin + yon (normalize) */
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_camera
{
	/* Konum + bakis + fov */
	t_vec3	position;
	t_vec3	orientation;
	int		fov;
}	t_camera;

typedef struct s_light
{
	/* Noktasal isik */
	t_vec3			position;
	double			brightness;
	t_vec3			color;
	struct s_light	*next;
}	t_light;

typedef struct s_ambient
{
	/* Ortam isigi */
	double	ratio;
	t_vec3	color;
}	t_ambient;

typedef struct s_scene
{
	/* Scene: object/light listeleri + kamera/ambient */
	t_object	*objects;
	t_light		*lights;
	t_camera	camera;
	t_ambient	ambient;
	bool		has_camera;
	bool		has_ambient;
}	t_scene;

typedef struct s_data
{
	/* MLX handle'lari */
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_app
{
	/* Unified cleanup icin wrapper */
	t_scene	*scene;
	t_data	*data;
}	t_app;

t_vec3		vec_add(t_vec3 vector1, t_vec3 vector2);
t_vec3		vec_sub(t_vec3 vector1, t_vec3 vector2);
t_vec3		vec_mult(t_vec3 vector1, t_vec3 vector2);
t_vec3		vec_divide(t_vec3 vector1, t_vec3 vector2);
t_vec3		vec_cross_product(t_vec3 vector1, t_vec3 vector2);
t_vec3		vec_mult_scalar(t_vec3 vector, double scalar);
t_vec3		vec_divide_scalar(t_vec3 vector, double scalar);
double		vec_magnitude(t_vec3 vector);
t_vec3		vec_normalize(t_vec3 vector);
double		vec_dot_product(t_vec3 vector1, t_vec3 vector2);
double		ndc_x(int x);
double		ndc_y(int y);
double		fov_factor(int fov);
double		check_intersection(t_ray ray, t_object *obj);
double		intersect_sphere(t_ray ray, t_sphere *sphere);
double		intersect_plane(t_ray ray, t_plane *plane);
double		intersect_cylinder(t_ray ray, t_cylinder *cylinder);
t_ray		generate_ray(int x, int y, t_scene *scene, double fov_fact);
int			init_mlx(t_data *data);
void		render_scene(t_data *data, t_scene *scene);
double		get_closest_intersection(t_ray ray, t_object *objects);
t_vec3		vec_add_scaled(t_vec3 a, t_vec3 b, double s);
t_vec3		vec_scale(t_vec3 v, double s);
double		min_pos(double a, double b);
bool		within_cap_radius(t_vec3 p, t_vec3 cap, t_vec3 axis, double r);
void		init_scene(t_scene *scene);
void		free_scene(t_scene *scene);
void		free_objects(t_object **objects);
void		free_lights(t_light **lights);
void		cleanup_scene(t_scene *scene);
bool		scene_add_object(t_scene *scene, t_object *obj);
bool		scene_add_light(t_scene *scene, t_light *light);
bool		parse_file(const char *path, t_scene *scene);
t_object	*get_closest_object(t_ray ray, t_object *objects, double *out_t);
t_vec3		get_normal_at_hit(t_object *obj, t_vec3 p);
int			pack_rgb(t_vec3 c);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_vec3		shade_hit(t_scene *scene, t_object *hit, t_vec3 p, t_vec3 n);
t_vec3		color_mul255(t_vec3 a, t_vec3 b);
t_vec3		clamp_color255(t_vec3 c);
void		cleanup_mlx(t_data *data);
int			app_exit(t_app *app, int exit_code);
int			close_window(void *param);

#endif