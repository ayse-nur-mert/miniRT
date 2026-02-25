/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:17:33 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 18:29:56 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

const char	*skip_spaces(const char *s)
{
	while (s && *s
		&& (*s == ' ' || *s == '\t' || *s == '\n'
			|| *s == '\r' || *s == '\v' || *s == '\f'))
		s++;
	return (s);
}

char	*trim_line(char *line)
{
	size_t	len;

	if (!line)
		return (NULL);
	len = 0;
	while (line[len])
		len++;
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
	return (line);
}

void	free_tokens(char **tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

bool	parse_double_str(const char *s, double *out)
{
	char	*end;
	double	v;

	if (!s || !out)
		return (false);
	v = strtod(s, &end);
	if (end == s)
		return (false);
	while (*end == ' ' || *end == '\t')
		end++;
	if (*end != '\0')
		return (false);
	*out = v;
	return (true);
}

bool	parse_int_str(const char *s, int *out)
{
	char	*end;
	long	v;

	if (!s || !out)
		return (false);
	v = strtol(s, &end, 10);
	if (end == s)
		return (false);
	while (*end == ' ' || *end == '\t')
		end++;
	if (*end != '\0')
		return (false);
	if (v < -2147483648L || v > 2147483647L)
		return (false);
	*out = (int)v;
	return (true);
}
