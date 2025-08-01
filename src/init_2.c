/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:35:31 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/01 15:28:28 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_last_meal_time(t_table *table)
{
	int	i;

	i = 0;
	while (i < (int)table->number_of_philos)
	{
		table->philos[i]->last_meal_time = table->start_of_time;
		i++;
	}
}

int	init_mutex(pthread_mutex_t *mutex, int *flag)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		*flag = 0;
		return (1);
	}
	*flag = 1;
	return (0);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < (int)table->number_of_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, &routine,
				(void *)table->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
