#include "parser.h"

static void	put_err(const char *msg)
{
	if (!msg)
		return;
	write(2, msg, (size_t)strlen(msg));
}

static bool	has_rt_extension(const char *path)
{
	size_t	len;

	if (!path)
		return (false);
	len = strlen(path);
	if (len < 3)
		return (false);
	return (path[len - 3] == '.' && path[len - 2] == 'r' && path[len - 1] == 't');
}

static bool	is_empty_or_comment(const char *s)
{
	s = skip_spaces(s);
	return (!s || *s == '\0' || *s == '#');
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

bool	parse_file(const char *path, t_scene *scene)
{
	int		fd;
	char	*line;
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
	ok = true;
	line = get_next_line(fd);
	while (line)
	{
		trim_line(line);
		if (!is_empty_or_comment(line))
		{
			if (!parse_line_dispatch(line, scene))
			{
				put_err("Error: invalid scene line\n");
				ok = false;
				break;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	if (ok)
		ok = validate_file_content(scene);
	if (!ok)
		free_scene(scene);
	return (ok);
}
