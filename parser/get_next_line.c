#include "get_next_line.h"

char	*gnl_extract_line(char **stash);
char	*gnl_stash_join(char *stash, const char *buf);

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
		if (stash)
		{
			for (size_t i = 0; stash[i]; i++)
				if (stash[i] == '\n')
					return (gnl_extract_line(&stash));
		}
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buf[bytes] = '\0';
		if (bytes == 0)
			break;
		stash = gnl_stash_join(stash, buf);
		if (!stash)
			return (NULL);
	}
	return (gnl_extract_line(&stash));
}
