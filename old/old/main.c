/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:42:11 by julifern          #+#    #+#             */
/*   Updated: 2025/08/27 23:48:19 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (parse_input(&data, av))
			return (1);
		if (data_init(&data))
			return (1);
		if (dinner_start(&data))
			dinner_cleanup(&data);
		// leak prevention : all philo fulls || 1 philo dead
		
	}
	else
	{
		// wrong! error + exit
		error_message_exit("Wrong input");
	}
	return (0);
}