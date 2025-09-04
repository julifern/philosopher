/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:07:43 by julifern          #+#    #+#             */
/*   Updated: 2025/09/03 14:26:12 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, t_philo *philo)
{
	int	time;
	
	pthread_mutex_lock(&philo->data->data_mutex);
	time = get_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (time > data->time_to_die)
	{
		// pthread_mutex_unlock(&philo->data->data_mutex);
		pthread_mutex_lock(&data->write_mutex);
		printf("at time(ms) %ld, philosopher %d has died...\n",
			get_time() - data->start_time, philo->philo_id);
		pthread_mutex_unlock(&data->write_mutex);
		pthread_mutex_lock(&data->data_mutex);
		data->end_simulation = 1;
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	// pthread_mutex_unlock(&philo->data->data_mutex);
	return (0);
}

static int	check_full(t_data *data)
{
	int		all_full;
	int		i;

	if (data->total_meals <= 0)
		return (0);
	i = 0;
	all_full = 1;
	pthread_mutex_lock(&data->data_mutex);
	while (i < data->philo_nbr)
	{
		if (data->philos[i].meals < data->total_meals)
			all_full = 0;
		if (!all_full)
			break ;
		i++;
	}
	if (all_full)
		data->end_simulation = 1;
	pthread_mutex_unlock(&data->data_mutex);
	return (all_full);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!get_end_simulation(data))
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			if (check_death(data, &data->philos[i]))
				return (NULL);
			i++;
		}
		if (check_full(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
