/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:38:35 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/01 14:26:42 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_input_error(char *msg, int err)
{
	printf("%s\n", msg);
	exit(err);
}

void	ft_exit_error(char *msg, int err, t_table *table)
{
	free_table(table);
	printf("%s\n", msg);
	exit(err);
}
