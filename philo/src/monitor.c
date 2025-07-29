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

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *) arg;
	printf("Monitor created.\n");
	wait_for_start(table);
	while (!has_sim_ended(table))
	{
		usleep(500000);
		pthread_mutex_lock(&table->sim_end_lock);
		table->simulation_ended = 1;
		pthread_mutex_unlock(&table->sim_end_lock);
		printf("GAMEOVER\n");
	}
	return (NULL);
}
