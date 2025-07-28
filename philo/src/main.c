/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:36:09 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/28 20:45:42 by mrazem           ###   ########.fr       */
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
		sleep(1);
		// end_routine
		// //////////////////////////// CHECKS/////////////////////////////////

		// int i = 0;
		// printf("Philos: %d\n", table.number_of_philos);
		// while ( i < (int)table.number_of_philos)
		// {
		// 	t_philo *philo = table.philos[i];
		// 	printf("Philo[id]: %d\n", philo->id);
		// 	printf("Left Fork[id]: %d\n", philo->forks[LEFT]);
		// 	printf("Right Fork[id]: %d\n", philo->forks[RIGHT]);
		// 	i++;
		// }
		// printf("Start of time: %ld\n", table.start_of_time = get_time_in_ms());
// 
		//////////////////////////////////////////////////////////////////
	}
	else
		ft_error_msg(STR_USAGE, ERR_USAGE);
	return (0);
}


int	start_dinner(t_table *table)
{
	int		i;

	i = 0;
	table->start_of_time = get_time_in_ms();
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
	//STARTFLAG SET to GO
	pthread_mutex_lock(&table->start_lock);
	table->start_of_time = get_time_in_ms();
	table->start_flag = 1;
	pthread_mutex_unlock(&table->start_lock);
	return (0);
}
