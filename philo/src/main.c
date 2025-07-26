/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:36:09 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/25 23:20:01 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	set_forks(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philos);
	printf("allocated %lu\n", sizeof(pthread_mutex_t) * table->number_of_philos); //// REMOVE
	if (!table->forks)
		return (1);
	return (0);
}

int	create_philos(t_table *table)
{
	int		i;

	table->philos = malloc(sizeof(t_philo *) * table->number_of_philos);
	if (!table->philos)
		return (1);
	i = 0;
	while ((unsigned int)i < table->number_of_philos)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		if (!table->philos[i])
		{
			free_philos(table, i);
			return (1);
		}
		table->philos[i]->id = i + 1;
		table->philos[i]->forks[LEFT] = i;
		table->philos[i]->forks[RIGHT] = (i + 1) % table->number_of_philos;
		table->philos[i]->last_meal_time = 0;
		table->philos[i]->table = table;
		i++;
	}
	return (0);
}
// nr_of_philos time_to_die time_to_eat time_to_sleep [nr_of_tms_each_phi_must_eat]

int	init_table(t_table	*table, char **av, int ac)
{
	table->number_of_philos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		table->must_eats = ft_atol(av[5]);
	else
		table->must_eats = -1;
	table->start_of_time = 0;
	if (set_forks(table))
		ft_error_msg("FORK MALLOC FAILED", ERR_FORK_MALLOC);
	if (create_philos(table))
		ft_error_msg("Failed at creating philos.", ERR_PHILOS_CREATION);


	printf("number of philos: %d\n", table->number_of_philos);
	printf("time to die: %ld\n", table->time_to_die);
	printf("time_to_eat: %ld\n", table->time_to_eat);
	printf("time to sleep: %ld\n", table->time_to_sleep);
	printf("must eats: %d\n", table->must_eats);
	return (0);
}


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

		//////////////////////////////////////////////////////////////////
	}
	else
		ft_error_msg(STR_USAGE, ERR_USAGE);
	return (0);
}

