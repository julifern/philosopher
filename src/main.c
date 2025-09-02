/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:03:26 by julifern          #+#    #+#             */
/*   Updated: 2025/09/02 13:37:17 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simul(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;
	
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, routine, &data->philos[i]))
			return (error_message("error while creating philo thread"));
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data))
		return (error_message("error while creating philo thread"));
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->philo_nbr)
		pthread_join(data->philos[i++].thread_id, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (ac == 5 || ac == 6)
	{
		if (parse_input(&data, av))
			return (1);
		if (data_init(&data))
			return (1);
		if (start_simul(&data))
			return (1);
		free_all(&data);
	}
	else
		return (error_message("Wrong argument number"));
	return (0);
}