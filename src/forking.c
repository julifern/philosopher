/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:58:27 by julifern          #+#    #+#             */
/*   Updated: 2025/09/02 13:30:05 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_fork(t_philo *philo, pthread_mutex_t *fork, char *message)
{
	pthread_mutex_lock(fork);
	if (philo->data->end_simulation)
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	print_message(philo, message);
	return (1);
}

static int take_forks_odd(t_philo *philo)
{
	if (!lock_fork(philo, &philo->right_fork->fork, "has taken a fork"))
		return (0);
	if (!lock_fork(philo, &philo->left_fork->fork, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (0);
	}
	return (1);
}

static int	take_forks_even(t_philo *philo)
{
	if (!lock_fork(philo, &philo->left_fork->fork, "has taken the left fork"))
		return (0);
	if (!lock_fork(philo, &philo->right_fork->fork, "has taken the right fork"))
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (0);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->data->end_simulation)
		return (0);
	if (philo->philo_id % 2 == 0)
		return (take_forks_even(philo));
	else
		return (take_forks_odd(philo));
}
