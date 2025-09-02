/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:49:50 by julifern          #+#    #+#             */
/*   Updated: 2025/08/30 19:50:39 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaining;
	
	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec)
	{
		if (simulation_finished(data))
			break ;
		elapsed = gettime(MICROSECONDS) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (gettime(MICROSECONDS) - start < usec)
				;
		}
	}

}

long	ft_atol(const char *nptr)
{
	long	i;
	long	sign;
	long	res;

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

long	get_time(int time)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (error_message_exit("gettimeofday failed") - 2);
	if (time == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time == MILLISECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1e3));
	else if (time == MICROSECONDS)
		return (tv.tv_sec + (tv.tv_usec));
	else
		return (error_message_exit("wrong input gettime") - 2);
	return (-1);
}

int		error_message_exit(char *error)
{
	printf("%s\n", error);
	return (1);
}