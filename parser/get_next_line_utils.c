#include "get_next_line.h"

static size_t	gnl_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*gnl_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dst;

	len = gnl_strlen(s);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*gnl_substr(const char *s, size_t start, size_t len)
{
	size_t	slen;
	size_t	i;
	char	*dst;

	if (!s)
		return (NULL);
	slen = gnl_strlen(s);
	if (start >= slen)
		return (gnl_strdup(""));
	if (len > slen - start)
		len = slen - start;
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

static char	*gnl_strjoin(const char *s1, const char *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	char	*dst;

	l1 = gnl_strlen(s1);
	l2 = gnl_strlen(s2);
	dst = (char *)malloc(l1 + l2 + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		dst[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < l2)
	{
		dst[l1 + i] = s2[i];
		i++;
	}
	dst[l1 + l2] = '\0';
	return (dst);
}

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
