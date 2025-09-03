/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:10:09 by julifern          #+#    #+#             */
/*   Updated: 2025/09/03 10:22:57 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	put_forks_down(t_philo *philo)
{
	if (get_end_simulation(philo->data))
		return (1);
	pthread_mutex_lock(&philo->left_fork->fork);
	philo->left_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->right_fork->fork);
	philo->right_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->right_fork->fork);
	return (0);
}

static void	philo_action(t_philo *philo, int time)
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
	while (philo->fork_check != 3)
	{
		if (!take_forks(philo))
			return (0);
	}
	philo->fork_check = 0;
	print_message(philo, EATING);
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal_time = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	philo_action(philo, philo->data->time_to_eat);
	if (put_forks_down(philo))
		return (0);
	print_message(philo, SLEEPING);
	philo_action(philo, philo->data->time_to_sleep);
	if (get_end_simulation(philo->data))
		return (0);
	print_message(philo, THINKING);
	philo_action(philo, (philo->data->time_to_die - philo->data->time_to_eat
			- philo->data->time_to_sleep) / 10);
	usleep(100);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_nbr == 1)
	{
		print_message(philo, "has taken the fork");
		philo_action(philo, philo->data->time_to_die);
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
		if (!philo_routine(philo))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
