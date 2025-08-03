/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:30:34 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/03 16:04:25 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table	*table, char **av, int ac)
{
	init_vars(table, av, ac);
	if (init_locks(table))
		ft_exit_error("Lock init failed", ERR_LOCKS, table);
	if (init_forks(table))
		ft_exit_error("Fork init failed", ERR_FORK_MALLOC, table);
	if (init_philos(table))
		ft_exit_error("init philos failed", ERR_PHILOS_CREATION, table);
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

int	init_locks(t_table *table)
{
	if (init_mutex(&table->start_lock, &table->init_flags.start_lock_flag))
		return (1);
	if (init_mutex(&table->print_lock, &table->init_flags.print_lock_flag))
		return (1);
	if (init_mutex(&table->sim_end_lock, &table->init_flags.sim_end_lock_flag))
		return (1);
	table->simulation_ended = 0;
	table->start_flag = 0;
	return (0);
}

int	init_forks(t_table *table)
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
			destroy_forks(table, i);
			free(table->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philos = malloc(sizeof(t_philo *) * table->number_of_philos);
	if (!table->philos)
		return (1);
	i = 0;
	while ((unsigned int)i < table->number_of_philos)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		philo = table->philos[i];
		if (!philo || init_mutex(&philo->count_lock, &philo->count_flag))
		{
			free_philos(table, i);
			return (1);
		}
		philo->id = i + 1;
		philo->forks[LEFT] = i;
		philo->forks[RIGHT] = (i + 1) % table->number_of_philos;
		philo->last_meal_time = 0;
		philo->table = table;
		philo->meal_count = 0;
		i++;
	}
	return (0);
}
