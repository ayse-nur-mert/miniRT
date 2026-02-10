#include "../../include/engine.h"

int ft_strlen(const char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}

int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strdup(const char *s)
{
    int     len;
    char    *dest;
    int     i;

    len = ft_strlen(s);
    dest = malloc(sizeof(char) * (len + 1));
    if (!dest)
        return (NULL);
    i = 0;
    while (s[i])
    {
        dest[i] = s[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

/* 
 * Robust string to double converter 
 * Handles negative signs and decimals
 */
double ft_atof(const char *s)
{
    double  res;
    double  sign;
    double  fraction;
    int     i;

    res = 0.0;
    sign = 1.0;
    i = 0;
    if (s[i] == '-')
    {
        sign = -1.0;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
        res = res * 10 + (s[i++] - '0');
    if (s[i] == '.')
    {
        i++;
        fraction = 0.1;
        while (s[i] >= '0' && s[i] <= '9')
        {
            res += (s[i++] - '0') * fraction;
            fraction *= 0.1;
        }
    }
    return (res * sign);
}

void *ft_memset(void *b, int c, size_t len)
{
    unsigned char *ptr;
    
    ptr = (unsigned char *)b;
    while (len-- > 0)
        *ptr++ = (unsigned char)c;
    return (b);
}

