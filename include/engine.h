#ifndef ENGINE_H
# define ENGINE_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>

/*
 * ============================================================================
 *                                Data Structures
 * ============================================================================
 */

/* Vector Structure - Double precision for better quality */
typedef struct s_v3
{
    double x;
    double y;
    double z;
} t_v3;

/* Color Structure - Helper for calculation */
typedef struct s_color
{
    double r;
    double g;
    double b;
} t_color;

/* Ray Structure */
typedef struct s_ray
{
    t_v3 orig;
    t_v3 dir;
} t_ray;

/* Camera / View Structure */
typedef struct s_view
{
    t_v3   pos;
    t_v3   dir;
    double fov;
    // Viewport helper data will be calculated during init
    t_v3   horizontal;
    t_v3   vertical;
    t_v3   low_left;
} t_view;

/*
 * Scene Objects
 */

typedef struct s_ambient
{
    double  ratio;
    t_color color;
} t_ambient;

typedef struct s_light
{
    t_v3    pos;
    double  ratio;
    t_color color;
} t_light;

/* Object Types */
typedef enum e_obj_type
{
    SPHERE,
    PLANE,
    CYLINDER
} t_obj_type;

/* Base Object Structure (Linked List) */
typedef struct s_object
{
    t_obj_type      type;
    void            *data; // Pointer to specific shape struct
    t_color         color;
    // Material properties could be added here (specular, etc.)
    double          specular; // Blinn-Phong shininess
    struct s_object *next;
} t_object;

typedef struct s_sphere
{
    t_v3    center;
    double  radius;
} t_sphere;

typedef struct s_plane
{
    t_v3 point;
    t_v3 normal;
} t_plane;

typedef struct s_cylinder
{
    t_v3    center;
    t_v3    axis;
    double  diameter;
    double  height;
} t_cylinder;

/* World Structure - Holds everything */
typedef struct s_world
{
    t_ambient   ambient;
    t_view      camera;
    t_light     *lights; // Support for multiple lights later?
    t_object    *objects;
    void        *mlx;
    void        *win;
    void        *img;
    char        *addr;
    int         bpp;
    int         line_len;
    int         endian;
    int         width;
    int         height;
} t_world;

/*
 * ============================================================================
 *                                 Prototypes
 * ============================================================================
 */

/* Math - Vector Operations */
t_v3    vec_new(double x, double y, double z);
t_v3    vec_add(t_v3 a, t_v3 b);
t_v3    vec_sub(t_v3 a, t_v3 b);
t_v3    vec_scale(t_v3 v, double s);
double  vec_dot(t_v3 a, t_v3 b);
t_v3    vec_cross(t_v3 a, t_v3 b);
double  vec_len_sq(t_v3 v);
double  vec_len(t_v3 v);
t_v3    vec_unit(t_v3 v);
t_v3    vec_reflect(t_v3 v, t_v3 n);

/* Hit Record - Result of intersection */
typedef struct s_hit
{
    double      t;          // Distance along ray
    t_v3        p;          // Hit point
    t_v3        normal;     // Surface normal at hit
    t_object    *obj;       // Object hit
} t_hit;

/* Render / Intersection Prototypes */
bool    hit_sphere(t_ray ray, t_sphere *sp, t_hit *rec);
bool    hit_plane(t_ray ray, t_plane *pl, t_hit *rec);
bool    hit_cylinder(t_ray ray, t_cylinder *cy, t_hit *rec);
bool    hit_world(t_world *world, t_ray ray, t_hit *rec);
void    render_scene(t_world *world);

/* Shading Prototypes */
t_color compute_shading(t_world *world, t_ray ray, t_hit *rec);

/* Camera */
void    init_camera(t_world *world);
t_ray   get_ray(t_world *world, double u, double v);

/* Core / MLX */
void    init_mlx_utils(t_world *world);
int     close_window(t_world *world);

/* Utils */
int     ft_strlen(const char *s);
int     ft_strcmp(const char *s1, const char *s2);
char    *ft_strdup(const char *s);
double  ft_atof(const char *s);
int     is_space(char c);
void    *ft_memset(void *b, int c, size_t len);

#endif
