/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:36:09 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/23 12:54:24 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// nr_of_philos time_to_die time_to_eat time_to_sleep [nr_of_tms_each_phi_must_eat]
int	init_table(t_table *table, char **av, int ac)
{
	table->number_of_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eats = ft_atoi(av[5]);
	else
		table->must_eats = -1;

	printf("number of philos: %d\n", table->number_of_philos);
	printf("time to die: %ld\n", table->time_to_die);
	printf("time_to_eat: %ld\n", table->time_to_eat);
	printf("time to sleep: %ld\n", table->time_to_sleep);
	printf("must eats: %d\n", table->must_eats);
	return (0);
}

void	create_philos(t_table *table)
{
	int	nr;

	nr = table->number_of_philos;
	while (nr > 0)
		printf("%d\n", nr--);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong argument count\n", 21), 1);
	if(ft_validate_input(av, ac) == 1)
		return (1);
	init_table(&table, av, ac);
	create_philos(&table);
	// start_dinner(table);
	// end_routine
	return (0);
}

