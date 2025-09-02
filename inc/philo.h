#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
};

enum e_time
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS
};

enum e_states
{
	EATING,
	SLEEPING,
	THINKING,
	FIRST_FORK,
	SECOND_FORK,
	DED
};

typedef pthread_mutex_t t_mtx;

typedef struct s_data t_data;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			philo_id;
	long		meals;
	int			full;
	long		last_meal_time;
	int			is_dead;
	t_fork		*right_fork;
	t_fork		*left_fork;
	pthread_t	thread_id;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	total_meals;
	long	start_time;
	int		end_simulation;
	int		all_threads_ready;
	t_philo	*philos;
	t_fork	*forks;
	t_mtx	data_mutex;
	t_mtx	write_mutex;
}	t_data;

// init
int		data_init(t_data *data);
// parsing
int		parse_input(t_data *data, char **av);
long	ft_atol(char *nptr);
// spaghetti
void	*routine(void *arg);
// forking
int	take_forks(t_philo *philo);
// utils
int		error_message(char *error);
long	get_time(void);
void	ft_usleep(long time);
int	get_end_simulation(t_data *data);
// output
void	print_message(t_philo *philo, char *message);
void	print_meal(t_philo *philo);
// monitor
void	*monitor(void *arg);
// cleanup
void	free_all(t_data *data);

#endif