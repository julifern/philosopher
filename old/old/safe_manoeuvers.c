/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_manoeuvers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julifern <julifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:14:26 by julifern          #+#    #+#             */
/*   Updated: 2025/08/30 11:09:18 by julifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int handle_mutex_error(int status, int code)
{
	if (!status)
		return (0);
	if (status == EINVAL && (code == LOCK || code == UNLOCK || code == DESTROY))
		return (error_message_exit("mutex value is invalid"));
	else if (status == EINVAL && code == INIT)
		return (error_message_exit("attr value is invalid"));
	else if (status == EDEADLK)
		return (error_message_exit("deadlock would occur"));
	else if (status == EPERM)
		return (error_message_exit("curr thread not locked"));
	else if (status == ENOMEM)
		return (error_message_exit("no mem"));
	else if (status == EBUSY)
		return (error_message_exit("locked mutex"));
	return (0);
}

int	safe_mutex(t_mtx *mutex, int code)
{
	if (code == LOCK)
		return (handle_mutex_error(pthread_mutex_lock(mutex), code));
	else if (code == UNLOCK)
		return (handle_mutex_error(pthread_mutex_unlock(mutex), code));
	else if (code == DESTROY)
		return (handle_mutex_error(pthread_mutex_destroy(mutex), code));
	else if (code == INIT)
		return (handle_mutex_error(pthread_mutex_init(mutex, NULL), code));
	else
		return (error_message_exit("Wrong code for mutex"));
	return (0);
}

static int	handle_thread_errors(int status, int code)
{
	if (!status)
		return (0);
	if (status == EAGAIN)
		return (error_message_exit("no ressources to create thread"));
	else if (status == EPERM)
		return (error_message_exit("inapropriate permission"));
	else if (status == EINVAL && code == CREATE)
		return (error_message_exit("invalid attr value"));
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		return (error_message_exit("thread value is not joinable"));
	else if (status == ESRCH)
		return (error_message_exit("no such thread given by thread ID"));
	else if (status == EDEADLK)
		return (error_message_exit("deadlock detected"));
	return (0);
}

int	safe_thread(pthread_t *thread, void *(*function)(void *),
		void *data, int code)
{
	if (code == CREATE)
		return (handle_thread_errors(pthread_create(thread, NULL, function, data), code));
	else if (code == JOIN)
		return (handle_thread_errors(pthread_join(*thread, NULL), code));
	else if (code == DETACH)
		return (handle_thread_errors(pthread_detach(*thread), code));
	return (0);
}

