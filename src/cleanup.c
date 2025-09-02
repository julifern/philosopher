/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:26:02 by julifern          #+#    #+#             */
/*   Updated: 2025/09/02 15:26:46 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutex(t_fork *fork, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(&fork[i++].fork);
}

void	free_all(t_data *data)
{
	destroy_mutex(data->forks, data->philo_nbr);
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	free(data->philos);
	free(data->forks);
}
