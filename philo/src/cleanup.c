/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 23:08:46 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/25 23:19:59 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	free_philos(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (table->philos[i])
			free(table->philos[i]);
		i++;
	}
}
