/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:38:35 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/24 22:56:32 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// char	*ft_input_error(t_input_err err)
// {
// 	if (err == ERR_NUMBER_OF_PHILOS)
// 		return ("Wrong number of philosophers, must be at least 1.");
// 	else if (err == ERR_TIME_TO_DIE)
// 		return ("Time to die must be a positive number.");
// 	else if (err == ERR_TIME_TO_EAT)
// 		return ("Time to eat must be a positive number.");
// 	else if (err == ERR_TIME_TO_SLEEP)
// 		return ("Time to sleep must be a positive number.");
// 	else if (err == ERR_MUST_EATS)
// 		return ("Number of times each philos must eat has to be 0 or more.");
// 	return ("Unknown error.");
// }

void	ft_error_msg(char *msg, int err)
{
	printf("%s\nERR_NO:%d\n", msg, err);
	exit(err);
}
