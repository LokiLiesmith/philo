/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:44:33 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/29 23:19:18 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_lock(pthread_mutex_t *mutex, t_table *table)
{
	if (has_sim_ended(table))
		return (1);
	if (pthread_mutex_lock(mutex) != 0)
		return (1);
	if (has_sim_ended(table))
	{
		pthread_mutex_unlock(mutex);
		return (1);
	}
	return (0);
}

static int	take_forks(t_philo *p)
{
	if (p->id == p->table->number_of_philos)
	{
		if (safe_lock(&p->table->forks[p->forks[RIGHT]], p->table))
			return (1);
		if (safe_lock(&p->table->forks[p->forks[LEFT]], p->table) != 0)
		{
			pthread_mutex_unlock(&p->table->forks[p->forks[RIGHT]]);
			return (1);
		}
	}
	else
	{
		if (safe_lock(&p->table->forks[p->forks[LEFT]], p->table) != 0)
			return (1);
		if (safe_lock(&p->table->forks[p->forks[RIGHT]], p->table) != 0)
		{
			pthread_mutex_unlock(&p->table->forks[p->forks[LEFT]]);
			return (1);
		}
	}
	return (0);
}

int	release_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->table->forks[philo->forks[LEFT]]) != 0)
		return (1);
	if (pthread_mutex_unlock(&philo->table->forks[philo->forks[RIGHT]]) != 0)
		return (1);
	return (0);
}

static int	eat(t_philo *philo)
{
	if (!has_sim_ended(philo->table))
	{
		log_state(philo, "is eating");
		philo->last_meal_time = get_time_in_ms();
		if (philo->meal_count < 0)
			philo->meal_count++;
		return (0);
	}
	return (1);
}

int	sleep_and_think(t_philo *philo)
{
	if (!has_sim_ended(philo->table))
	{
		log_state(philo, "is sleeping");
		usleep(philo->table->time_to_sleep * 1000);
		log_state(philo, "is thinking");
		return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo->table);
	log_state(philo, "started");
	while (!has_sim_ended(philo->table))
	{
		if (take_forks(philo))
			return (NULL);
		if (eat(philo))
			return (NULL);
		if (release_forks(philo))
			return (NULL);
		if (sleep_and_think(philo))
			return (NULL);
	}
	return (NULL);
}
