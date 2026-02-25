#include "parser.h"

static const char	*skip_sep_spaces(const char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

bool	parse_vec3(const char *s, t_vec3 *out)
{
	char	*end;
	double	x;
	double	y;
	double	z;

	if (!s || !out)
		return (false);
	x = strtod(s, &end);
	if (end == s)
		return (false);
	s = skip_sep_spaces(end);
	if (*s != ',')
		return (false);
	s = skip_sep_spaces(s + 1);
	y = strtod(s, &end);
	if (end == s)
		return (false);
	s = skip_sep_spaces(end);
	if (*s != ',')
		return (false);
	s = skip_sep_spaces(s + 1);
	z = strtod(s, &end);
	if (end == s)
		return (false);
	s = skip_sep_spaces(end);
	if (*s != '\0')
		return (false);
	*out = (t_vec3){x, y, z};
	return (true);
}

bool	parse_color255(const char *s, t_vec3 *out)
{
	t_vec3	c;

	if (!parse_vec3(s, &c))
		return (false);
	if (c.x < 0 || c.x > 255 || c.y < 0 || c.y > 255 || c.z < 0 || c.z > 255)
		return (false);
	*out = c;
	return (true);
}

bool	vec3_in_range(const t_vec3 v, double min, double max)
{
	return (v.x >= min && v.x <= max && v.y >= min && v.y <= max && v.z >= min && v.z <= max);
}

bool	vec3_nonzero(const t_vec3 v)
{
	return (!(v.x == 0.0 && v.y == 0.0 && v.z == 0.0));
}
