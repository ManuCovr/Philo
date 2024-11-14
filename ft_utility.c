/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:31:01 by mde-maga          #+#    #+#             */
/*   Updated: 2024/11/14 14:12:00 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd >= 0)
	{
		while (s && *s)
		{
			write(fd, &*s, 1);
			s++;
		}
	}
}

void	ft_putnbr_fd(long int len, int fd)
{
	if (len < 0)
	{
		len *= -1;
		ft_putchar_fd('-', fd);
	}
	if (len >= 10)
	{
		ft_putnbr_fd(len / 10, fd);
		ft_putnbr_fd(len % 10, fd);
	}
	else
	{
		if (fd >= 0)
			ft_putchar_fd(len + 48, fd);
	}
}

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
