/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:30:34 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/28 23:59:53 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	printf("Created Philos.\n");
	return (0);
}

int	set_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philos);
	if (!table->forks)
		return (1);
	while (i < (int)table->number_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_mutexes(table, i);
			free(table->forks);
			return (1);
		}
		i++;
	}
	printf("Set forks.\n");
	return (0);
}

int	init_vars(t_table *table, char**av, int ac)
{
	table->number_of_philos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		table->must_eats = ft_atol(av[5]);
	else
		table->must_eats = -1;
	return (0);
}

int	check_lock_inits(t_lock_inits *lock_inits)
{
	if (lock_inits->print_lock_init == 0)
		return (1);
	if (lock_inits->start_lock_init == 0)
		return (1);
	if (lock_inits->sim_end_lock_init == 0)
		return (1);
	return (0);
}

void	destroy_locks(t_table *table)
{
	if (table->lock_inits.print_lock_init)
		pthread_mutex_destroy(&table->print_lock);
	if (table->lock_inits.start_lock_init)
		pthread_mutex_destroy(&table->start_lock);
	if (table->lock_inits.sim_end_lock_init)
		pthread_mutex_destroy(&table->sim_end_lock);
}

int	init_locks(t_table *table)
{
	if (pthread_mutex_init(&table->start_lock, NULL) == 0)
		table->lock_inits.start_lock_init = 1;
	if (pthread_mutex_init(&table->print_lock, NULL) == 0)
		table->lock_inits.print_lock_init = 1;
	if (pthread_mutex_init(&table->sim_end_lock, NULL) == 0)
		table->lock_inits.sim_end_lock_init = 1;
	if (check_lock_inits(&table->lock_inits))
		return (1);
	printf("\n\n////// STARTLOCK:%d\n", table->lock_inits.start_lock_init);
	printf("\n\n////// PRINTLOCK:%d\n", table->lock_inits.print_lock_init);
	printf("\n\n////// SIMENDLOCK:%d\n", table->lock_inits.sim_end_lock_init);
	table->simulation_ended = 0;
	table->start_flag = 0;
	return (0);
}

int	init_table(t_table	*table, char **av, int ac)
{
	init_vars(table, av, ac);
	if (init_locks(table))
	{
		free_table(table);	
		ft_error_msg("Locks failed", ERR_LOCKS);
	}
	if (set_forks(table))
	{
		free_table(table);
		ft_error_msg("FORK MALLOC FAILED", ERR_FORK_MALLOC);
	}
	if (create_philos(table))
	{
		free_table(table);
		ft_error_msg("Failed at creating philos.", ERR_PHILOS_CREATION);
	}
	printf("Init Complete.\n");
	return (0);
}
