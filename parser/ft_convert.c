/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:00:00 by amert             #+#    #+#             */
/*   Updated: 2026/03/03 12:00:00 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

double	ft_strtod(const char *s, char **endptr)
{
	double	result;
	double	fraction;
	double	divisor;
	int		sign;

	result = 0.0;
	sign = 1;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (*s == '-' || *s == '+')
		sign = (*s++ == '-') ? -1 : 1;
	while (ft_isdigit(*s))
		result = result * 10.0 + (*s++ - '0');
	if (*s == '.')
	{
		s++;
		fraction = 0.0;
		divisor = 1.0;
		while (ft_isdigit(*s))
		{
			fraction = fraction * 10.0 + (*s++ - '0');
			divisor *= 10.0;
		}
		result += fraction / divisor;
	}
	if (endptr)
		*endptr = (char *)s;
	return (result * sign);
}

long	ft_strtol(const char *s, char **endptr)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (*s == '-' || *s == '+')
		sign = (*s++ == '-') ? -1 : 1;
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	if (endptr)
		*endptr = (char *)s;
	return (result * sign);
}
