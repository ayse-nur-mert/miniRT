#ifndef PARSER_H
# define PARSER_H

# include "../../include/engine.h"

typedef struct s_token
{
    char            *content;
    int             type; // 0=word, 1=newline/separator (optional usage)
    struct s_token  *next;
} t_token;

/* Tokenizer */
t_token *tokenize_file(const char *filename);
void    free_tokens(t_token *tokens);

/* Parser */
int     parse_scene(t_world *world, t_token *tokens);
int     parse_ambient(t_world *world, t_token **tokens);
int     parse_camera(t_world *world, t_token **tokens);
int     parse_light(t_world *world, t_token **tokens);
int     parse_sphere(t_world *world, t_token **tokens);
int     parse_plane(t_world *world, t_token **tokens);
int     parse_cylinder(t_world *world, t_token **tokens);

/* parser utils */
double  parse_double(t_token **tokens);
t_v3    parse_vec3(t_token **tokens);
t_color parse_color(t_token **tokens);

#endif
