/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:36:09 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/22 21:37:00 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}

// number_of_philosophers time_to_die time_to_eat time_to_sleep [nr_of_times_each_philosopher_must_eat]
int	init_table(t_table *table, char **av)
{
	table->number_of_philosophers = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->must_eats = ft_atoi(av[5]);

	printf("number of philos: %d\n", table->number_of_philosophers);
	printf("time to die: %ld\n", table->time_to_die);
	printf("time_to_eat: %ld\n", table->time_to_eat);
	printf("time to sleep: %ld\n", table->time_to_sleep);
	printf("must eats: %d\n", table->must_eats);

	return (0);
}

void create_philos(t_table *table)
{
	int nr = table->number_of_philos;
	while (nr > 0)
		
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		// validate_input(av);
		init_table(&table, av);
		// start_dinner(table);
	}
	// end_routine
	return (0);
}
