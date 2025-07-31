/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:30:34 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/31 17:25:01 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_table *table)
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
		if (!philo || mutex_init(&philo->count_lock, &philo->count_flag))
		{
			free_philos(table, i);
			return (1);
		}
		table->philos[i]->id = i + 1;
		table->philos[i]->forks[LEFT] = i;
		table->philos[i]->forks[RIGHT] = (i + 1) % table->number_of_philos;
		table->philos[i]->last_meal_time = 0;
		table->philos[i]->table = table;
		table->philos[i]->meal_count = 0;
		i++;
	}
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
			destroy_forks(table, i);
			free(table->forks);
			return (1);
		}
		i++;
	}
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
	if (mutex_init(&table->start_lock, &table->init_flags.start_lock_flag))
		return (1);
	if (mutex_init(&table->print_lock, &table->init_flags.print_lock_flag))
		return (1);
	if (mutex_init(&table->sim_end_lock, &table->init_flags.sim_end_lock_flag))
		return (1);
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
	return (0);
}
