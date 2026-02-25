/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:16:16 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 16:35:46 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_extract_line(char **stash)
{
	char	*nl;
	char	*line;
	char	*rest;

	if (!stash || !*stash || **stash == '\0')
		return (NULL);
	nl = gnl_strchr(*stash, '\n');
	if (nl)
	{
		line = gnl_substr(*stash, 0, (size_t)(nl - *stash + 1));
		rest = gnl_strdup(nl + 1);
		free(*stash);
		*stash = rest;
		return (line);
	}
	line = gnl_strdup(*stash);
	free(*stash);
	*stash = NULL;
	return (line);
}

char	*gnl_stash_join(char *stash, const char *buf)
{
	char	*joined;

	if (!stash)
		return (gnl_strdup(buf));
	joined = gnl_strjoin(stash, buf);
	free(stash);
	return (joined);
}
