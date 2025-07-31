/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:36:09 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/31 17:25:04 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		ft_validate_input(av, ac);
		init_table(&table, av, ac);
		start_dinner(&table);
		wait_for_threads(&table);
		free_table(&table);
	}
	else
		ft_error_msg(STR_USAGE, ERR_USAGE);
	return (0);
}

void	wait_for_threads(t_table *table)
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

static void	init_last_meal_time(t_table *table)
{
	int	i;

	i = 0;
	while (i < (int)table->number_of_philos)
	{
		table->philos[i]->last_meal_time = table->start_of_time;
		i++;
	}
}

int	start_dinner(t_table *table)
{
	int		i;

	i = 0;
	while (i < (int)table->number_of_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, &routine,
				(void *)table->philos[i]) != 0)
		{
			free_table(table);
			ft_error_msg("Failed to create thread", 1);
		}
		i++;
	}
	if (create_monitor(table))
		free_table(table);
	pthread_mutex_lock(&table->start_lock);
	table->start_of_time = get_time_in_ms();
	init_last_meal_time(table);
	table->start_flag = 1;
	pthread_mutex_unlock(&table->start_lock);
	return (0);
}
