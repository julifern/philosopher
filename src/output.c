/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 20:13:55 by julifern          #+#    #+#             */
/*   Updated: 2025/09/02 13:30:55 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	long	time;
	
	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->data->end_simulation)
		printf("at time(ms) %ld, philosopher %d %s.\n", time, philo->philo_id, message);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	print_meal(t_philo *philo)
{
	long	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->data->end_simulation)
		printf("at time(ms) %ld, philosopher %d finished meal %ld.\n", time, philo->philo_id, philo->meals);
	pthread_mutex_unlock(&philo->data->write_mutex);
}