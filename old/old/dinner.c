/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:41:43 by julifern          #+#    #+#             */
/*   Updated: 2025/08/28 00:41:45 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	while (!simulation_finished)
	{
		if (philo->full)
			break ;
		eat();
		// slep
		
		thinking();
	}
	return (NULL);
}

int	dinner_start(t_data *data)
{
	int	i;

	i = 0;
	if (data->nbr_limit_meals == 0)
		return (1);
	else if (data->philo_nbr == 1)
		; //TODO
	else
	{
		while (i < data->philo_nbr)
		{
			safe_thread(&data->philos[i].thread_id, dinner_simulation,
					&data->philos[i], CREATE);
			i++;
		}
	}
	data->start_simulation = gettime(MILLISECONDS);
	set_bool(&data->data_mutex, &data->all_treads_ready, 1);
	i = 0;
	while (i < data->philo_nbr)
	{
		safe_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	// all philos full
}