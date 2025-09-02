/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:50:35 by julifern          #+#    #+#             */
/*   Updated: 2025/08/28 00:52:00 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_fork(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->left_fork = &forks[(position + 1) % philo_nbr];
	philo->right_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[position];
		philo->left_fork = &forks[(position + 1) % philo_nbr];
	}
}

static void	philo_init(t_data *data)
{
	int	i;
	t_philo	*philo;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->id = i + i;
		philo->full = 0;
		philo->meals = 0;
		philo->data = data;
		assign_fork(philo, data->forks, i);
		i++;
	}
}

int	data_init(t_data *data)
{
	int	i;
	
	i = 0;
	data->end_simulation = 0;
	data->all_treads_ready = 0;
	data->philos = nalloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return (1);
	safe_mutex(&data->data_mutex, INIT);
	safe_mutex(&data->write_mutex, INIT);
	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
		return (1);
	while (i < data->philo_nbr)
	{
		if (safe_mutex(&data->forks[i].fork, INIT))
			return (1);
		data->forks[i].fork_id = i;
		i++;
	}
	philo_init(data);
	return (0);
}
