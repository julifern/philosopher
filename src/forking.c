/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:58:27 by julifern          #+#    #+#             */
/*   Updated: 2025/09/04 12:08:35 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->end_simulation)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		pthread_mutex_unlock(fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (1);
}

static int	take_forks_odd(t_philo *philo)
{
	if (!lock_fork(philo, &philo->right_fork->fork))
		return (0);
	if (!philo->right_fork->is_taken)
	{
		philo->right_fork->is_taken = 1;
		philo->fork_check |= 1;
	}
	pthread_mutex_unlock(&philo->right_fork->fork);
	if (!lock_fork(philo, &philo->left_fork->fork))
		return (0);
	if (!philo->left_fork->is_taken)
	{
		philo->left_fork->is_taken = 1;
		philo->fork_check |= 2;
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (1);
}

static int	take_forks_even(t_philo *philo)
{
	if (!lock_fork(philo, &philo->left_fork->fork))
		return (0);
	if (!philo->left_fork->is_taken) 
	{
		philo->left_fork->is_taken = 1;
		philo->fork_check |= 2;
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
	if (!lock_fork(philo, &philo->right_fork->fork))
		return (0);
	if (!philo->right_fork->is_taken)
	{
		philo->right_fork->is_taken = 1;
		philo->fork_check |= 1;
	}
	pthread_mutex_unlock(&philo->right_fork->fork);
	return (1);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->end_simulation)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (philo->philo_id % 2 == 0 && !take_forks_even(philo))
		return (0);
	else if (!take_forks_odd(philo))
		return (0);
	if (philo->fork_check == 3)
	{
		print_message(philo, LEFT_FORK);
		print_message(philo, RIGHT_FORK);
		return (1);
	}
	else if (philo->fork_check == 1)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		philo->fork_check = 0;
		philo->right_fork->is_taken = 0;
		pthread_mutex_unlock(&philo->right_fork->fork);
	}
	else if (philo->fork_check == 2)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		philo->fork_check = 0;
		philo->left_fork->is_taken = 0;
		pthread_mutex_unlock(&philo->left_fork->fork);
	}
	return (1);
}
