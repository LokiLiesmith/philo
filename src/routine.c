/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:44:33 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/01 15:07:16 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo->table);
	if (philo->table->number_of_philos == 1)
	{
		if (dinner_for_1(philo))
			return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 2);
	while (!has_sim_ended(philo->table))
	{
		if (overeat_check(philo))
			break ;
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

int	take_forks(t_philo *p)
{
	if (p->id == p->table->number_of_philos)
	{
		if (safe_lock(&p->table->forks[p->forks[RIGHT]], p->table, p) != 0)
			return (1);
		if (safe_lock(&p->table->forks[p->forks[LEFT]], p->table, p) != 0)
		{
			pthread_mutex_unlock(&p->table->forks[p->forks[RIGHT]]);
			return (1);
		}
	}
	else
	{
		if (safe_lock(&p->table->forks[p->forks[LEFT]], p->table, p) != 0)
			return (1);
		if (safe_lock(&p->table->forks[p->forks[RIGHT]], p->table, p) != 0)
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

int	eat(t_philo *philo)
{
	if (has_sim_ended(philo->table))
		return (1);
	pthread_mutex_lock(&philo->count_lock);
	philo->last_meal_time = get_time_in_ms();
	if (philo->meal_count >= 0)
		philo->meal_count++;
	pthread_mutex_unlock(&philo->count_lock);
	log_state(philo, "is eating");
	ft_usleep(philo->table->time_to_eat);
	return (0);
}

int	sleep_and_think(t_philo *philo)
{
	if (has_sim_ended(philo->table))
		return (1);
	log_state(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
	log_state(philo, "is thinking");
	return (0);
}
