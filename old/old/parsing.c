/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:42:15 by julifern          #+#    #+#             */
/*   Updated: 2025/08/27 23:47:31 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	invalid_input(char *message)
{
	error_message_exit("message");
	return (0);
}

static int	*valid_input(char *str)
{
	int	len;

	len = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (invalid_input("only positive numbers"));
	if (!ft_isdigit(*str))
		return (invalid_input("not digit"));
	while (ft_isdigit(*str++))
		len++;
	if (len > 10)
		return (invalid_input("too big"));
	return (1);
}

int	parse_input(t_data *data, char **av)
{
	if (valid_input(av[1]))
	data->philo_nbr = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]) * 1e3;
	data->time_to_eat = ft_atol(av[3]) * 1e3;
	data->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (data->philo_nbr > INT_MAX || data->time_to_die > INT_MAX
		|| data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX)
		return (error_message_exit("value too big"));
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4
		|| data->time_to_sleep < 6e4)
		return (error_message_exit("need times longer than 60ms"));
	if (av[5])
		data->nbr_limit_meals = ft_atol(av[5]);
	else
		data->nbr_limit_meals = -1;
	return (0);
}
