/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:44:33 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/28 23:36:52 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_lock(pthread_mutex_t *mutex, t_table *table)
{
	pthread_mutex_lock(mutex);
	if(!has_sim_ended(table))
	{
		return (0);
	}
	return (1);
}
int	safe_unlock(pthread_mutex_t *mutex, t_table *table)
{
	if(!has_sim_ended(table))
	{
		pthread_mutex_unlock(mutex);
		return (0);
	}
	return (1);
}


static void	take_forks(t_philo *philo)
{
	if (philo->id == philo->table->number_of_philos)
	{
		pthread_mutex_lock(&philo->table->forks[philo->forks[RIGHT]]);
		pthread_mutex_lock(&philo->table->forks[philo->forks[LEFT]]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->forks[LEFT]]);
		pthread_mutex_lock(&philo->table->forks[philo->forks[RIGHT]]);
	}
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->forks[LEFT]]);
	pthread_mutex_unlock(&philo->table->forks[philo->forks[RIGHT]]);
}

static void	eat(t_philo *philo)
{
	if(!has_sim_ended(philo->table))
	{
		log_state(philo, "is eating");
		philo->last_meal_time = get_time_in_ms();
		if (philo->meal_count < 0)
			philo->meal_count++;
	}
}

void	sleep_and_think(t_philo *philo)
{
	if(!has_sim_ended(philo->table))
	{
		log_state(philo, "is sleeping");
		usleep(philo->table->time_to_sleep * 1000);
		log_state(philo, "is thinking");
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo->table);
	log_state(philo, "started");
	while (!has_sim_ended(philo->table))
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
