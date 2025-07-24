/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:55:44 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/24 22:57:18 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

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

//CHECK IF IN INT MAX-MIN RANGE
int	is_in_int_range(char *s)
{
	long	n;

	n = ft_atol(s);
	return (n >= -2147483648 && n <= 2147483647);
}

int	is_valid_int(char *s)
{
	return (is_valid_int_string(s) && is_in_int_range(s));
}

int	ft_validate_input(char **av, int ac)
{
	if (!is_valid_int(av[1]))
		ft_error_msg("Invalid number of Philosophers.", ERR_NUMBER_OF_PHILOS);
	if (!is_valid_int(av[2]))
		ft_error_msg("Invalid input: Time to die must be a positive number.");
	if (!is_valid_int(av[3]))
		ft_error_msg("Invalid input: Time to eat must be a positive number.");
	if (!is_valid_int(av[4]))
		ft_error_msg("Invalid input: Time to sleep must be a positive number.");
	if (ac == 6)
	{
		if (!is_valid_int(av[5]))
			ft_error_msg("Invalid number of times each philosopher must eat.");
	}
	return (ERR_NONE);
}
