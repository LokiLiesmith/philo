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

void static	wait_for_start(t_philo *philo)
{
	while (420)
	{
		pthread_mutex_lock(&philo->table->start_lock);
		if (philo->table->start_flag)
		{
			pthread_mutex_unlock(&philo->table->start_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->start_lock);
		usleep(100);
	}
}

void static	take_forks(t_philo *philo)
{
	if (philo->id == philo->table->number_of_philos)
	{
		pthread_mutex_lock(&philo->table->forks[philo->forks[RIGHT]]);
		log_state(philo, "picked up right fork");
		pthread_mutex_lock(&philo->table->forks[philo->forks[LEFT]]);
		log_state(philo, "picked up left fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->forks[LEFT]]);
		log_state(philo, "picked up left fork.");
		pthread_mutex_lock(&philo->table->forks[philo->forks[RIGHT]]);
		log_state(philo, "picked up right fork.");
	}
}

void static	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->forks[LEFT]]);
	// log_state(philo, "dropped left fork");
	pthread_mutex_unlock(&philo->table->forks[philo->forks[RIGHT]]);
	// log_state(philo, "dropped right fork");
}

void static	eat(t_philo *philo)
{
	log_state(philo, "is eating");
	philo->last_meal_time = get_time_in_ms();
	if (philo->meal_count < 0)
		philo->meal_count++;
}

void	sleep_and_think(t_philo *philo)
{
	log_state(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	log_state(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->table->simulation_ended)
	{
		wait_for_start(philo);
		log_state(philo, "started");
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_and_think(philo);
	}
	// while (!has_simulation_ended(philo->table))
	// {
	// 	take_forks(philo);
	// 	eat(philo);
	// 	release_forks(philo);
	// 	sleep_and_think(philo);
	// }
	// while (420)
	// {
	// 	pthread_mutex_lock(&philo->table->start_lock);
	// 	if (philo->table->start_flag)
	// 	{
	// 		pthread_mutex_unlock(&philo->table->start_lock);
	// 		break ;
	// 	}
	// 	pthread_mutex_unlock(&philo->table->start_lock);
	// 	usleep(100);
	// }
	return (NULL);
}
