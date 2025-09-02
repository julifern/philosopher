/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:10:09 by julifern          #+#    #+#             */
/*   Updated: 2025/09/02 13:29:19 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_forks_down(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	philo_action(t_philo *philo, int time)
{
	long	start;
	
	start = get_time();
	while (!get_end_simulation(philo->data))
	{
		if (get_time() - start >= time)
			break ;
		usleep(1000);
	}
}

int	philo_routine(t_philo *philo)
{
	if (get_end_simulation(philo->data))
		return (0);
	if (!take_forks(philo))
		return (0);
	if (get_end_simulation(philo->data))
	{
		put_forks_down(philo);
		return (0);
	}
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal_time = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	print_meal(philo);
	philo_action(philo, philo->data->time_to_eat);
	put_forks_down(philo);
	if (get_end_simulation(philo->data))
		return (0);
	print_message(philo, "is sleeping");
	philo_action(philo, philo->data->time_to_sleep);
	if (get_end_simulation(philo->data))
		return (0);
	print_message(philo, "is thinking");
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	if (philo->data->philo_nbr == 1)
	{
		print_message(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->end_simulation)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		philo_routine(philo);
	}
	return (NULL);
}