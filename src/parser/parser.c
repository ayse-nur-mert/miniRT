#include "parser.h"

/* Helper to skip to next comma and return pointer after it */
static char *next_val(char *str)
{
    while (*str && *str != ',')
        str++;
    if (*str == ',')
        return (str + 1);
    return (str);
}

/* Parse "x,y,z" */
t_v3 parse_vec3(t_token **tokens)
{
    t_v3    v;
    char    *s;
    
    if (!*tokens)
        return (vec_new(0,0,0));
    s = (*tokens)->content;
    v.x = ft_atof(s);
    s = next_val(s);
    v.y = ft_atof(s);
    s = next_val(s);
    v.z = ft_atof(s);
    *tokens = (*tokens)->next;
    return (v);
}

/* Parse "r,g,b" */
t_color parse_color(t_token **tokens)
{
    t_color c;
    char    *s;

    if (!*tokens)
        return ((t_color){0,0,0});
    s = (*tokens)->content;
    c.r = ft_atof(s) / 255.0; // Normalize to 0-1
    s = next_val(s);
    c.g = ft_atof(s) / 255.0;
    s = next_val(s);
    c.b = ft_atof(s) / 255.0;
    *tokens = (*tokens)->next;
    return (c);
}

double parse_double(t_token **tokens)
{
    double val;
    
    if (!*tokens)
        return (0.0);
    val = ft_atof((*tokens)->content);
    *tokens = (*tokens)->next;
    return (val);
}

/* Object Add Helper */
static void add_object(t_world *world, t_object *new_obj)
{
    t_object *tmp;

    if (!world->objects)
    {
        world->objects = new_obj;
    }
    else
    {
        tmp = world->objects;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_obj;
    }
}

/* --- Element Parsers --- */

int parse_ambient(t_world *world, t_token **tokens)
{
    *tokens = (*tokens)->next; // Skip "A"
    world->ambient.ratio = parse_double(tokens);
    world->ambient.color = parse_color(tokens);
    return (1);
}

int parse_camera(t_world *world, t_token **tokens)
{
    *tokens = (*tokens)->next; // Skip "C"
    world->camera.pos = parse_vec3(tokens);
    world->camera.dir = parse_vec3(tokens);
    world->camera.fov = parse_double(tokens);
    return (1);
}

int parse_light(t_world *world, t_token **tokens)
{
    // Simple single light support for now or list
    // If strict miniRT, usually one 'L'. We can support array or list.
    // Let's alloc array if needed, but for now just use the pointer in world
    // Warning: If multiple lights, this overrides. 
    // We should malloc t_light array or linked list for lights too.
    // For now, let's treat it as a single light for the struct, or update engine.h to be list.
    // engine.h has t_light *lights; let's treat it as array of size 1 for now or malloc.
    if (!world->lights)
        world->lights = malloc(sizeof(t_light)); 
    
    *tokens = (*tokens)->next; // Skip "L"
    world->lights[0].pos = parse_vec3(tokens);
    world->lights[0].ratio = parse_double(tokens);
    world->lights[0].color = parse_color(tokens);
    return (1);
}

int parse_sphere(t_world *world, t_token **tokens)
{
    t_sphere    *sp;
    t_object    *obj;

    sp = malloc(sizeof(t_sphere));
    obj = malloc(sizeof(t_object));
    
    *tokens = (*tokens)->next; // Skip "sp"
    sp->center = parse_vec3(tokens);
    sp->radius = parse_double(tokens) / 2.0; // Diameter to Radius
    obj->color = parse_color(tokens);
    
    obj->type = SPHERE;
    obj->data = sp;
    obj->specular = 100.0; // Default shininess
    obj->next = NULL;
    
    add_object(world, obj);
    return (1);
}

int parse_plane(t_world *world, t_token **tokens)
{
    t_plane     *pl;
    t_object    *obj;

    pl = malloc(sizeof(t_plane));
    obj = malloc(sizeof(t_object));
    
    *tokens = (*tokens)->next; // Skip "pl"
    pl->point = parse_vec3(tokens);
    pl->normal = parse_vec3(tokens);
    obj->color = parse_color(tokens);
    
    obj->type = PLANE;
    obj->data = pl;
    obj->specular = 0.0; // Planes usually matte?
    obj->next = NULL;
    
    add_object(world, obj);
    return (1);
}

int parse_cylinder(t_world *world, t_token **tokens)
{
    t_cylinder  *cy;
    t_object    *obj;

    cy = malloc(sizeof(t_cylinder));
    obj = malloc(sizeof(t_object));
    
    *tokens = (*tokens)->next; // Skip "cy"
    cy->center = parse_vec3(tokens);
    cy->axis = parse_vec3(tokens);
    cy->diameter = parse_double(tokens);
    cy->height = parse_double(tokens);
    obj->color = parse_color(tokens);
    
    obj->type = CYLINDER;
    obj->data = cy;
    obj->specular = 50.0;
    obj->next = NULL;
    
    add_object(world, obj);
    return (1);
}

/* Dispatcher */
int parse_scene(t_world *world, t_token *tokens)
{
    while (tokens)
    {
        if (ft_strcmp(tokens->content, "A") == 0)
            parse_ambient(world, &tokens);
        else if (ft_strcmp(tokens->content, "C") == 0)
            parse_camera(world, &tokens);
        else if (ft_strcmp(tokens->content, "L") == 0)
            parse_light(world, &tokens);
        else if (ft_strcmp(tokens->content, "sp") == 0)
            parse_sphere(world, &tokens);
        else if (ft_strcmp(tokens->content, "pl") == 0)
            parse_plane(world, &tokens);
        else if (ft_strcmp(tokens->content, "cy") == 0)
            parse_cylinder(world, &tokens);
        else
            tokens = tokens->next; // Skip unknown? or Error?
    }
    return (1);
}
