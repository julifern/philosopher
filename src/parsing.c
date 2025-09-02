/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:12:06 by julifern          #+#    #+#             */
/*   Updated: 2025/09/02 11:53:25 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	invalid_input(char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

long	ft_atol(char *nptr)
{
	long	i;
	long	sign;
	long	res;

	if (invalid_input(nptr))
		return (0);
	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	res *= sign;
	return (res);
}

void	check_input(t_data *data)
{
	if (data->philo_nbr == 1)
		error_message("warning, only one philosopher");
	else if (data->time_to_die < 60)
		error_message("warning, small time input");
	else if (data->time_to_eat < 60)
		error_message("warning, small time input");
	else if (data->time_to_sleep < 60)
		error_message("warning, small time input");
	if (data->philo_nbr > 200)
		error_message("thats a lot of philosophers");
}

int	parse_input(t_data *data, char **av)
{
	data->philo_nbr = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->total_meals = ft_atol(av[5]);
	else
		data->total_meals = -1;
	check_input(data);
	if (data->philo_nbr > INT_MAX || data->time_to_die > INT_MAX
		|| data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX
		|| data->total_meals > INT_MAX)
		return (error_message("value too big"));
	if (!data->philo_nbr || !data->time_to_die
		|| !data->time_to_eat || !data->time_to_sleep
		|| !data->total_meals)
		return (error_message("invalid input"));
	data->start_time = get_time();
	return (0);
}
