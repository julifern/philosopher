/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:58:37 by julifern          #+#    #+#             */
/*   Updated: 2025/08/28 01:12:44 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_bool(t_mtx *mutex, int *dest, int value)
{
	if (safe_mutex(mutex, LOCK))
		return (1);
	*dest = value;
	if (safe_mutex(mutex, UNLOCK))
		return (1);
	return (0);
}

int		get_bool(t_mtx *mutex, int *value, int *out)
{
	if (safe_mutex(mutex, LOCK))
		return (1);
	out = *value;
	if (safe_mutex(mutex, UNLOCK))
		return (1);
	return (0);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	safe_mutex(mutex, LOCK);
	ret = *value;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

int		simulation_finished(t_data *data)
{
	int	finished;

	if (get_bool(&data->data_mutex, data->end_simulation, &finished))
		return (1);
	return (finished);
}