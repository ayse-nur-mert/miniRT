/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:14:26 by amert             #+#    #+#             */
/*   Updated: 2026/02/25 16:14:56 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_stash_has_newline(char *stash)
{
	size_t	i;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int	gnl_read_into_buf(int fd, char *buf, ssize_t *bytes, char **stash)
{
	*bytes = read(fd, buf, BUFFER_SIZE);
	if (*bytes < 0)
	{
		free(*stash);
		*stash = NULL;
		return (0);
	}
	buf[*bytes] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buf[BUFFER_SIZE + 1];
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		if (gnl_stash_has_newline(stash))
			return (gnl_extract_line(&stash));
		if (!gnl_read_into_buf(fd, buf, &bytes, &stash))
			return (NULL);
		if (bytes == 0)
			break ;
		stash = gnl_stash_join(stash, buf);
		if (!stash)
			return (NULL);
	}
	return (gnl_extract_line(&stash));
}
