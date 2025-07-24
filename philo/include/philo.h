/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:16:50 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/24 22:49:09 by mrazem           ###   ########.fr       */
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

struct	s_philo;

typedef enum e_input_err
{
	ERR_NONE = 0,
	ERR_NUMBER_OF_PHILOS,
	ERR_TIME_TO_DIE,
	ERR_TIME_TO_EAT,
	ERR_TIME_TO_SLEEP,
	ERR_MUST_EATS,
}	t_input_err;

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
}	t_table;

typedef struct s_philo
{
	int				id;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eats;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			table;
}	t_philo;




///  util.c
int		ft_atoi(const char *str);
long	ft_atol(const char *s);

///  parsing.c ///
int		is_valid_int_string(char *s);
int		is_in_int_range(char *s);
int		is_valid_int(char *s);
int		ft_validate_input(char **av, int ac);

// errors.c
// char	*ft_input_error(t_input_err err);
void	ft_error_msg(char *msg);


#endif
