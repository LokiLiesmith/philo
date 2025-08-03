/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:04:10 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/03 20:18:54 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dinner_for_1(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->forks[LEFT]]);
	log_state(philo, "has taken a fork");
	while (!has_sim_ended(philo->table))
		usleep(100);
	pthread_mutex_unlock(&philo->table->forks[philo->forks[LEFT]]);
	return (1);
}

int	safe_lock(pthread_mutex_t *mutex, t_table *table, t_philo *p)
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
	log_state(p, "has taken a fork");
	return (0);
}

int	overeat_check(t_philo *p)
{
	pthread_mutex_lock(&p->count_lock);
	if (p->table->must_eats != -1 && p->meal_count >= p->table->must_eats)
	{
		pthread_mutex_unlock(&p->count_lock);
		return (1);
	}
	pthread_mutex_unlock(&p->count_lock);
	return (0);
}
