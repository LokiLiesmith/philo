/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:32:42 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/31 17:01:31 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_sim_ended(t_table *table)
{
	int	ended;

	pthread_mutex_lock(&table->sim_end_lock);
	ended = table->simulation_ended;
	pthread_mutex_unlock(&table->sim_end_lock);
	return (ended);
}

void	wait_for_start(t_table *table)
{
	while (420)
	{
		pthread_mutex_lock(&table->start_lock);
		if (table->start_flag)
		{
			pthread_mutex_unlock(&table->start_lock);
			break ;
		}
		pthread_mutex_unlock(&table->start_lock);
		usleep(100);
	}
}
