/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:55:44 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/31 17:25:20 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

//CHECK IF ONLY 0-9 CHARS AND +-
int	is_valid_int_string(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	if (s[i] == '-')
		return (0);
	if (s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

//CHECK IF IN 0 - INT_MAX RANGE
int	is_in_int_range(char *s)
{
	long	n;

	n = ft_atol(s);
	return (n > 0 && n <= 2147483647);
}

int	is_valid_int(char *s)
{
	return (is_valid_int_string(s) && is_in_int_range(s));
}

int	ft_validate_input(char **av, int ac)
{
	if (!is_valid_int(av[1]) || ft_atol(av[1]) > 200)
		ft_error_msg("Invalid number of Philosophers.", ERR_NUMBER_OF_PHILOS);
	if (!is_valid_int(av[2]))
		ft_error_msg(STR_ERR_TO_DIE, ERR_TIME_TO_DIE);
	if (!is_valid_int(av[3]))
		ft_error_msg(STR_ERR_TO_EAT, ERR_TIME_TO_EAT);
	if (!is_valid_int(av[4]))
		ft_error_msg(STR_ERR_TO_SLEEP, ERR_TIME_TO_SLEEP);
	if (ac == 6)
	{
		if (!is_valid_int(av[5]))
			ft_error_msg(STR_ERR_MUST_EATS, ERR_MUST_EATS);
	}
	return (ERR_NONE);
}
