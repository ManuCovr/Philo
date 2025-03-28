/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:38:06 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/28 17:06:09 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	string_to_long(const char *s)
{
	long	res;
	int		i;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
		res = res * 10 + (s[i++] - '0');
	return (res * sign);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	is_invalid_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	ft_bzero(void *p, size_t s)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)p;
	while (s > 0)
	{
		str[i] = '\0';
		s--;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	s;

	if (nmemb == 0 || size == 0)
	{
		nmemb++;
		size++;
	}
	s = nmemb * size;
	p = malloc(s);
	if (!p)
		return (NULL);
	ft_bzero(p, s);
	return (p);
}
