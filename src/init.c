/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:51:56 by julifern          #+#    #+#             */
/*   Updated: 2025/09/02 16:56:23 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->right_fork = &forks[position];
	philo->left_fork = &forks[(position + 1) % philo_nbr];
}

static int	philo_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->philo_id = i + 1;
		philo->meals = 0;
		philo->data = data;
		assign_forks(philo, data->forks, i);
		philo->last_meal_time = get_time();
		philo->fork_check = 0;
		i++;
	}
	return (0);
}

int	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->end_simulation = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
		return (1);
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (1);
		data->forks[i].fork_id = i;
		data->forks[i].is_taken = 0;
		i++;
	}
	if (pthread_mutex_init(&data->data_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (1);
	if (philo_init(data))
		return (error_message("Error while creating threads"));
	return (0);
}
