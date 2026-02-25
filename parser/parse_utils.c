#include "parser.h"

static bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

const char	*skip_spaces(const char *s)
{
	while (s && *s && is_space(*s))
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

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char	*ft_substr(const char *s, size_t start, size_t len)
{
	size_t	slen;
	size_t	i;
	char	*dst;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (NULL);
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

void	free_tokens(char **tokens)
{
	size_t	i;

	if (!tokens)
		return;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

char	**split_ws(const char *s)
{
	size_t	i;
	size_t	count;
	size_t	start;
	char	**out;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (!s[i])
			break;
		count++;
		while (s[i] && !is_space(s[i]))
			i++;
	}
	out = (char **)calloc(count + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (!s[i])
			break;
		start = i;
		while (s[i] && !is_space(s[i]))
			i++;
		out[count] = ft_substr(s, start, i - start);
		if (!out[count])
		{
			free_tokens(out);
			return (NULL);
		}
		count++;
	}
	out[count] = NULL;
	return (out);
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
