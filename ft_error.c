/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:27 by mde-maga          #+#    #+#             */
/*   Updated: 2024/11/04 14:44:48 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_syntax(char *str)
{
	int lenght;
	lenght = 0;

	while(str[lenght])
		lenght++;
	write(2, "Error: ", 7);
	write(2, str, lenght);
	write(2, "\n", 1);
	return (1);
}

int	karen(int flag)
{
	if (flag == 1)
		return(error_syntax("At least one wrong argument."));
	if (flag == 2)
		return(error_syntax("Fatal error, shuting down."));
	return (1);
}