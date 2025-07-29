/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 23:08:46 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/28 23:57:58 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	free_philos(t_table *table, int count)
{
	int	i;
	t_philo *philo;

	i = 0;
	while (i < count)
	{
		philo = table->philos[i];
		if (philo)
		{
			destroy_mutex(&philo->count_lock, &philo->count_flag);
			free(philo);
		}
		i++;
	}
}

void	destroy_forks(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}

// void	destroy_locks(t_table *table)
// {
// 	if (table->init_flags.print_lock_flag)
// 		pthread_mutex_destroy(&table->print_lock);
// 	if (table->init_flags.start_lock_flag)
// 		pthread_mutex_destroy(&table->start_lock);
// 	if (table->init_flags.sim_end_lock_flag)
// 		pthread_mutex_destroy(&table->sim_end_lock);
// }

void	destroy_locks(t_table *table)
{
	destroy_mutex(&table->start_lock, &table->init_flags.start_lock_flag);
	destroy_mutex(&table->print_lock, &table->init_flags.print_lock_flag);
	destroy_mutex(&table->sim_end_lock, &table->init_flags.sim_end_lock_flag);
}

void	free_table(t_table *table)
{
	if (table)
		destroy_locks(table);
	if (table->forks)
	{
		destroy_forks(table, table->number_of_philos);
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philos)
	{
		free_philos(table, table->number_of_philos);
		free(table->philos);
		table->philos = NULL;
	}
}
