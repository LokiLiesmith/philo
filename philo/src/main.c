/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:36:09 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/26 19:47:09 by mrazem           ###   ########.fr       */
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
		// start_dinner(table);
		// end_routine
		//////////////////////////// CHECKS/////////////////////////////////

		int i = 0;
		printf("Philos: %d\n", table.number_of_philos);
		while ( i < (int)table.number_of_philos)
		{
			t_philo *philo = table.philos[i];
			printf("Philo[id]: %d\n", philo->id);
			printf("Left Fork[id]: %d\n", philo->forks[LEFT]);
			printf("Right Fork[id]: %d\n", philo->forks[RIGHT]);
			i++;
		}
		printf("Start of time: %ld\n", table.start_of_time = get_time_in_ms());

		//////////////////////////////////////////////////////////////////
	}
	else
		ft_error_msg(STR_USAGE, ERR_USAGE);
	return (0);
}

