/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_ws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:00:00 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 18:29:56 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

static size_t	word_count(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && !is_space(s[i]))
			i++;
	}
	return (count);
}

static char	*word_dup(const char *s, size_t start, size_t end)
{
	size_t	i;
	size_t	len;
	char	*dst;

	len = end - start;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static bool	split_fill(char **out, const char *s)
{
	size_t	i;
	size_t	start;
	size_t	idx;

	i = 0;
	idx = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && !is_space(s[i]))
			i++;
		out[idx] = word_dup(s, start, i);
		if (!out[idx])
			return (false);
		idx++;
	}
	out[idx] = NULL;
	return (true);
}

char	**split_ws(const char *s)
{
	size_t	count;
	char	**out;

	if (!s)
		return (NULL);
	count = word_count(s);
	out = (char **)calloc(count + 1, sizeof(char *));
	if (!out)
		return (NULL);
	if (!split_fill(out, s))
		return (free_tokens(out), NULL);
	return (out);
}
