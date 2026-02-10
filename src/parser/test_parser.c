#include "parser.h"
#include <stdio.h>

void print_vec(t_v3 v)
{
    printf("(%.2f, %.2f, %.2f)", v.x, v.y, v.z);
}

void print_color(t_color c)
{
    printf("RGB(%.2f, %.2f, %.2f)", c.r, c.g, c.b);
}

int main(void)
{
    t_world world = {0};
    t_token *tokens;
    t_object *obj;

    printf("--- Tokenizing sample.rt ---\n");
    tokens = tokenize_file("sample.rt");
    if (!tokens)
    {
        printf("Error: Failed to tokenize file\n");
        return (1);
    }
    printf("Tokenization successful.\n");

    printf("--- Parsing Scene ---\n");
    parse_scene(&world, tokens);
    
    // Validate Data
    printf("Ambient: %.2f ", world.ambient.ratio);
    print_color(world.ambient.color);
    printf("\n");

    printf("Camera: Pos=");
    print_vec(world.camera.pos);
    printf(" FOV=%.1f\n", world.camera.fov);

    if (world.lights)
    {
        printf("Light: Pos=");
        print_vec(world.lights[0].pos);
        printf(" Ratio=%.2f\n", world.lights[0].ratio);
    }

    printf("--- Objects ---\n");
    obj = world.objects;
    while (obj)
    {
        printf("Object Type: %d ", obj->type);
        if (obj->type == SPHERE)
        {
            t_sphere *s = (t_sphere *)obj->data;
            printf("[SPHERE] R=%.2f Center=", s->radius);
            print_vec(s->center);
        }
        else if (obj->type == PLANE)
            printf("[PLANE]");
        else if (obj->type == CYLINDER)
            printf("[CYLINDER]");
        
        printf(" Color=");
        print_color(obj->color);
        printf("\n");
        obj = obj->next;
    }

    free_tokens(tokens);
    return (0);
}
