/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:36:09 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:18 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int ac, char **av)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (ac == 5 || ac == 6)
	{
		ft_validate_input(av, ac);
		init_table(&table, av, ac);
		start_dinner(&table);
		join_threads(&table);
		free_table(&table);
	}
	else
		ft_exit_error(STR_USAGE, ERR_USAGE, &table);
	return (0);
}

int	start_dinner(t_table *table)
{
	if (create_threads(table))
		ft_exit_error("Failed to create thread", 1, table);
	if (create_monitor(table))
		ft_exit_error("Failed to create monitor_thread", 1, table);
	usleep(100);
	pthread_mutex_lock(&table->start_lock);
	table->start_of_time = get_time_in_ms();
	init_last_meal_time(table);
	table->start_flag = 1;
	pthread_mutex_unlock(&table->start_lock);
	return (0);
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < (int)table->number_of_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}
