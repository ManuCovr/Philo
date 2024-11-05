/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:21 by mde-maga          #+#    #+#             */
/*   Updated: 2024/11/04 14:45:32 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main	(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return(error_syntax("Wrong amount of arguments, it has to be 5 or 6"));
	
}