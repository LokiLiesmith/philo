/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:16:50 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/22 20:42:38 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

struct	s_philos;

typedef struct s_table
{
	time_t			start_of_time;
	unsigned int	number_of_philosophers;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	unsigned int	must_eats;
	pthread_mutex_t	*forks;
	struct s_philos	**philos;
}	t_table;

typedef struct s_philos
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	fork[2];

}	t_philos;

#endif

//number_of_philosophers 
//time_to_die
//time_to_eat
//time_to_sleep 
//[number_of_times_each_philosopher_must_eat]