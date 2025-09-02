/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:47:58 by julifern          #+#    #+#             */
/*   Updated: 2025/08/28 01:01:03 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	write_status(int state, t_philo *philo)
{
	if (safe_mutex(&philo->data->write_mutex, LOCK))
		return (1);

}