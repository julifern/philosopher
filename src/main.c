/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:03:26 by julifern          #+#    #+#             */
/*   Updated: 2025/09/04 16:59:19 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_and_join(t_data *data, int i)
{
	pthread_mutex_lock(&data->data_mutex);
	data->end_simulation = 1;
	pthread_mutex_unlock(&data->data_mutex);
	while (i > 0)
		pthread_join(data->philos[i--].thread_id, NULL);
}

static int	start_simul(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				routine, &data->philos[i]))
		{
			stop_and_join(data, i - 1);
			return (error_message("Error while creating philo thread"));
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data))
		return (error_message("Error while creating philo thread"));
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
	{
		free_all(&data);
		return (error_message("Wrong argument number"));
	}
	return (0);
}
