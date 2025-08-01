/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:55:44 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/01 15:27:57 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

//Check if input consists of positive numbers
int	ft_validate_input(char **av, int ac)
{
	if (!is_valid_int(av[1]) || ft_atol(av[1]) > 200)
		ft_input_error("Invalid number of Philosophers.", ERR_NUMBER_OF_PHILOS);
	if (!is_valid_int(av[2]))
		ft_input_error(STR_ERR_TO_DIE, ERR_TIME_TO_DIE);
	if (!is_valid_int(av[3]))
		ft_input_error(STR_ERR_TO_EAT, ERR_TIME_TO_EAT);
	if (!is_valid_int(av[4]))
		ft_input_error(STR_ERR_TO_SLEEP, ERR_TIME_TO_SLEEP);
	if (ac == 6)
	{
		if (!is_valid_int(av[5]))
			ft_input_error(STR_ERR_MUST_EATS, ERR_MUST_EATS);
	}
	return (ERR_NONE);
}

//Check if an int string and in [0 - INT_MAX] range
int	is_valid_int(char *s)
{
	return (is_valid_int_string(s) && is_in_int_range(s));
}

//Check if in [0 - INT_MAX] range
int	is_in_int_range(char *s)
{
	long	n;

	n = ft_atol(s);
	return (n > 0 && n <= 2147483647);
}

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
