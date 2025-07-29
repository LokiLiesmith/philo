/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:16:50 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/28 23:59:59 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# define STR_USAGE "Invalid Input\n\
Correct usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> [number_of_times_each_philosopher_must_eat]"
# define STR_ERR_TO_DIE "Invalid input: Time to die must be a positive number."
# define STR_ERR_TO_EAT "Invalid input: Time to eat must be a positive number."
# define STR_ERR_TO_SLEEP "Invalid input: Time to sleep must be a \
positive number."
# define STR_ERR_MUST_EATS "Invalid number of times each philosopher must eat."

struct	s_philo;

enum e_fork_side
{
	LEFT = 0,
	RIGHT = 1,
};

typedef enum e_input_err
{
	ERR_NONE = 0,
	ERR_NUMBER_OF_PHILOS,
	ERR_TIME_TO_DIE,
	ERR_TIME_TO_EAT,
	ERR_TIME_TO_SLEEP,
	ERR_MUST_EATS,
	ERR_USAGE,
	ERR_FORK_MALLOC,
	ERR_PHILOS_CREATION,
	ERR_LOCKS,
}	t_input_err;

typedef struct s_init_flags
{
	int				start_lock_flag;
	int				print_lock_flag;
	int				sim_end_lock_flag;
	int				monitor_flag;
}	t_init_flags;

typedef struct s_table
{
	long			start_of_time;
	unsigned int	number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	unsigned int	must_eats;
	pthread_mutex_t	*forks;
	struct s_philo	**philos;
	pthread_mutex_t	start_lock;
	int				start_flag;
	pthread_mutex_t	print_lock;
	int				simulation_ended;
	pthread_mutex_t	sim_end_lock;
	t_init_flags	init_flags;
	pthread_t		monitor;
}	t_table;

typedef struct s_philo
{
	unsigned int	id; //index + 1
	long			last_meal_time;
	pthread_t		thread;
	unsigned int	forks[2];
	t_table			*table;
	pthread_mutex_t	count_lock;
	int				count_flag;
	long			meal_count;
}	t_philo;


int		start_dinner(t_table *table);

///  utils.c
long	ft_atol(const char *s);
long	get_time_in_ms(void);
void	log_state(t_philo *philo, char *msg);
int 	destroy_mutex (pthread_mutex_t *mutex, int *flag);
int		mutex_init (pthread_mutex_t *mutex, int *flag);

// init.c
int		init_table(t_table	*table, char **av, int ac);
int		init_vars(t_table *table, char**av, int ac);
int		set_forks(t_table *table);
int		create_philos(t_table *table);

///  parsing.c ///
int		is_valid_int_string(char *s);
int		is_in_int_range(char *s);
int		is_valid_int(char *s);
int		ft_validate_input(char **av, int ac);

// errors.c
// char	*ft_input_error(t_input_err err);
void	ft_error_msg(char *msg, int err_no);

//routine.c
void	*routine(void *arg);

//sync.c
int		has_sim_ended (t_table *table);
void	wait_for_start(t_table *table);


//monitor.c
void *monitor_routine(void *arg);
int	create_monitor(t_table *table);


// cleanup.c
void	free_philos(t_table *table, int count);
void	destroy_forks(t_table *table, int count);
void	free_table(t_table *table);
void	destroy_locks(t_table *table);
int		check_lock_inits(t_init_flags *init_flags);



#endif
