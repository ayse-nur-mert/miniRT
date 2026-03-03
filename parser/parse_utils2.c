/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:17:38 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 18:29:56 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static const char	*skip_sep_spaces(const char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

static bool	parse_part(const char **s, double *out)
{
	char	*end;

	*out = ft_strtod(*s, &end);
	if (end == *s)
		return (false);
	*s = skip_sep_spaces(end);
	return (true);
}

bool	parse_vec3(const char *s, t_vec3 *out)
{
	double	x;
	double	y;
	double	z;

	if (!s || !out)
		return (false);
	if (!parse_part(&s, &x))
		return (false);
	if (*s++ != ',')
		return (false);
	s = skip_sep_spaces(s);
	if (!parse_part(&s, &y))
		return (false);
	if (*s++ != ',')
		return (false);
	s = skip_sep_spaces(s);
	if (!parse_part(&s, &z))
		return (false);
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
	if (c.x < 0 || c.x > 255
		|| c.y < 0 || c.y > 255
		|| c.z < 0 || c.z > 255)
		return (false);
	*out = c;
	return (true);
}
