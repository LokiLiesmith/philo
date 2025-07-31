/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:35:39 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/29 21:38:41 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_monitor(t_table *t)
{
	if (pthread_create(&t->monitor, NULL, &monitor_routine, (void *)t) != 0)
	{
		t->init_flags.monitor_flag = 0;
		return (1);
	}
	t->init_flags.monitor_flag = 1;
	return (0);
}

static int	philo_death(t_table *t)
{
	int i;
	t_philo *philo;
	
	i = 0;
	while (i < (int)t->number_of_philos)
	{
		philo = t->philos[i];
		pthread_mutex_lock(&philo->count_lock);
		if ((get_time_in_ms() - philo->last_meal_time) > t->time_to_die)
		{
			pthread_mutex_unlock(&philo->count_lock);
			log_state(philo, "has died");
			return (1);
		}
		pthread_mutex_unlock(&philo->count_lock);
		i++;
	}
	return (0);
}

static int	all_full(t_table *table)
{
	int	i;

	if (table->must_eats == -1)
		return (0);
	i = 0;
	while(i < (int)table->number_of_philos)
		{
			pthread_mutex_lock(&table->philos[i]->count_lock);
			if (table->philos[i]->meal_count < table->must_eats)
			{
				pthread_mutex_unlock(&table->philos[i]->count_lock);
				return (0);
			}
			pthread_mutex_unlock(&table->philos[i]->count_lock);
			i++;
		}
	printf("ALL FULL\n");
	return (1); 
}

			
static int	sim_end_check(t_table *table)
{
	return (philo_death(table) || all_full(table));
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *) arg;
	// printf("Monitor created.\n");
	wait_for_start(table);
	while (!has_sim_ended(table))
	{
		if(sim_end_check(table))
		{
			pthread_mutex_lock(&table->sim_end_lock);
			table->simulation_ended = 1;
			pthread_mutex_unlock(&table->sim_end_lock);
			printf("GAMEOVER\n");
		}
		usleep(100);
	}
	return (NULL);
}
