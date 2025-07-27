/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 23:08:46 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/28 00:34:54 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	free_philos(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (table->philos[i])
			free(table->philos[i]);
		i++;
	}
}

void	destroy_mutexes(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}

void	free_table(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->start_lock);
	if (table->forks)
	{
		destroy_mutexes(table, table->number_of_philos);
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
