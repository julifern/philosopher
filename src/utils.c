/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:41:47 by julifern          #+#    #+#             */
/*   Updated: 2025/09/02 15:33:24 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_end_simulation(t_data *data)
{
	int	ended;

	pthread_mutex_lock(&data->data_mutex);
	ended = data->end_simulation;
	pthread_mutex_unlock(&data->data_mutex);
	return (ended);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
		pthread_mutex_destroy(&data->forks[i].fork);
}

int	error_message(char *error)
{
	printf("%s\n", error);
	return (1);
}
