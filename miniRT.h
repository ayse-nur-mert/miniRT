/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esir <esir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:01:43 by esir              #+#    #+#             */
/*   Updated: 2026/02/25 17:12:38 by esir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <fcntl.h>
#include "minilibx-linux/mlx.h"

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265358979323846
#define ASPECT_RATIO ((double)WIDTH / (double)HEIGHT)

typedef struct s_vec3
{
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
	t_vec3	center;     // Kürenin merkez noktası
	double	diameter;   // Çapı (Yarıçap = diameter / 2)
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;      // Düzlem üzerindeki herhangi bir nokta
	t_vec3	normal;     // Düzlemin baktığı yön (normalize edilmiş olmalı)
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;     // Silindirin merkez noktası
	t_vec3	normal;     // Silindirin uzandığı eksen (normalize edilmiş olmalı)
	double	diameter;   // Çapı
	double	height;     // Yüksekliği
}	t_cylinder;

typedef struct s_object
{
	t_obj_type		type;   // Bu obje ne? (SPHERE, PLANE, CYLINDER)
	void			*data;  // Şeklin kendi özel verileri (t_sphere*, t_plane* vb.)
	t_vec3			color;  // Objenin RGB rengi (Ortak özellik)
	struct s_object	*next;  // Listedeki bir sonraki objeye işaretçi
}	t_object;

typedef struct s_ray
{
	t_vec3	origin;    // Işının çıktığı nokta
	t_vec3	direction; // Işının gittiği yön (vektör)
}	t_ray;

typedef struct s_camera
{
	t_vec3	position;     // Kameranın konumu
	t_vec3	orientation;  // Kameranın baktığı yön (3D vektör)
	int		fov;             // Görüş açısı (Field of View)
}	t_camera;

typedef struct s_light
{
	t_vec3			position;     // Işığın uzaydaki konumu
	double			brightness;   // Işığın parlaklık oranı (0.0 ile 1.0 arası)
	t_vec3			color;        // Işığın RGB rengi
	struct s_light	*next;
}	t_light;

typedef struct s_ambient
{
	double	ratio; // 0.0-1.0
	t_vec3	color; // 0-255
}	t_ambient;

typedef struct s_scene
{
	t_object	*objects;
	t_light		*lights;
	t_camera	camera;
	t_ambient	ambient;
	bool		has_camera;
	bool		has_ambient;
}	t_scene;

typedef struct s_data
{
	void	*mlx;      // mlx bağlantı pointer'ı
	void	*win;      // pencere pointer'ı
	void	*img;      // imaj pointer'ı
	char	*addr;     // imajın hafızadaki başlangıç adresi
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

t_vec3	vec_add(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec_sub(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec_mult(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec_divide(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec_cross_product(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec_mult_scalar(t_vec3 vector, double scalar);
t_vec3	vec_divide_scalar(t_vec3 vector, double scalar);
double	vec_magnitude(t_vec3 vector);
t_vec3	vec_normalize(t_vec3 vector);
double	vec_dot_product(t_vec3 vector1, t_vec3 vector2);
double	ndc_x(int x);
double	ndc_y(int y);
double	fov_factor(int fov);
double	check_intersection(t_ray ray, t_object *obj);
double	intersect_sphere(t_ray ray, t_sphere *sphere);
double	intersect_plane(t_ray ray, t_plane *plane);
double	intersect_cylinder(t_ray ray, t_cylinder *cylinder);
t_ray	generate_ray(int x, int y, t_scene *scene, double fov_fact);
int		init_mlx(t_data *data);
void	render_scene(t_data *data, t_scene *scene);
double	get_closest_intersection(t_ray ray, t_object *objects);
t_vec3	vec_add_scaled(t_vec3 a, t_vec3 b, double s);
t_vec3	vec_scale(t_vec3 v, double s);
double	min_pos(double a, double b);
bool	within_cap_radius(t_vec3 p, t_vec3 cap_center, t_vec3 axis, double r);
void	init_scene(t_scene *scene);
void	free_scene(t_scene *scene);
bool	scene_add_object(t_scene *scene, t_object *obj);
bool	scene_add_light(t_scene *scene, t_light *light);
bool	parse_file(const char *path, t_scene *scene);
t_object	*get_closest_object(t_ray ray, t_object *objects, double *out_t);
t_vec3	get_normal_at_hit(t_object *obj, t_vec3 p);
int		pack_rgb(t_vec3 c);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_vec3	shade_hit(t_scene *scene, t_object *hit, t_vec3 p, t_vec3 n);
t_vec3	color_mul255(t_vec3 a, t_vec3 b);
t_vec3	clamp_color255(t_vec3 c);





#endif