/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:17:44 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 16:37:45 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../miniRT.h"
# include <string.h>

# define GNL_BUFFER_SIZE 1024

// get_next_line
char		*get_next_line(int fd);

// main entry
bool		parse_file(const char *path, t_scene *scene);

// required by spec
bool		validate_file_content(t_scene *scene);
bool		parse_line_object(const char *line, t_scene *scene);

// internal helpers
const char	*skip_spaces(const char *s);

char		*trim_line(char *line);
char		**split_ws(const char *s);
void		free_tokens(char **tokens);

bool		parse_double_str(const char *s, double *out);
bool		parse_int_str(const char *s, int *out);
bool		parse_vec3(const char *s, t_vec3 *out);
bool		parse_color255(const char *s, t_vec3 *out);
bool		vec3_in_range(const t_vec3 v, double min, double max);
bool		vec3_nonzero(const t_vec3 v);

bool		parse_line_light(const char *line, t_scene *scene);
bool		parse_line_camera(const char *line, t_scene *scene);
bool		parse_line_ambient(const char *line, t_scene *scene);

#endif
