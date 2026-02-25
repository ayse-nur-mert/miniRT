/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:17:17 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 16:20:42 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	put_err(const char *msg)
{
	if (!msg)
		return ;
	write(2, msg, strlen(msg));
}

static bool	has_rt_extension(const char *path)
{
	size_t	len;

	if (!path)
		return (false);
	len = strlen(path);
	if (len < 3)
		return (false);
	return (path[len - 3] == '.'
		&& path[len - 2] == 'r'
		&& path[len - 1] == 't');
}

static bool	parse_line_dispatch(const char *line, t_scene *scene)
{
	const char	*s;

	s = skip_spaces(line);
	if (s[0] == 'A' && (s[1] == ' ' || s[1] == '\t'))
		return (parse_line_ambient(s, scene));
	if (s[0] == 'C' && (s[1] == ' ' || s[1] == '\t'))
		return (parse_line_camera(s, scene));
	if (s[0] == 'L' && (s[1] == ' ' || s[1] == '\t'))
		return (parse_line_light(s, scene));
	return (parse_line_object(s, scene));
}

static bool	parse_file_lines(int fd, t_scene *scene)
{
	const char	*s;
	char		*line;
	bool		ok;

	ok = true;
	line = get_next_line(fd);
	while (line)
	{
		trim_line(line);
		s = skip_spaces(line);
		if (s && *s != '\0' && *s != '#'
			&& !parse_line_dispatch(line, scene))
		{
			put_err("Error: invalid scene line\n");
			ok = false;
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (ok);
}

bool	parse_file(const char *path, t_scene *scene)
{
	int		fd;
	bool	ok;

	if (!has_rt_extension(path))
	{
		put_err("Error: invalid file extension (expected .rt)\n");
		return (false);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		put_err("Error: cannot open file\n");
		return (false);
	}
	ok = parse_file_lines(fd, scene);
	close(fd);
	if (ok)
		ok = validate_file_content(scene);
	if (!ok)
		free_scene(scene);
	return (ok);
}
