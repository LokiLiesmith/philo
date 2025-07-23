/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:55:44 by mrazem            #+#    #+#             */
/*   Updated: 2025/07/23 12:08:16 by mrazem           ###   ########.fr       */
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

//check if they are numbers only if no 6th arg then set 6th to -1
int	ft_validate_input(char **av)
{
	int	i;
	
	i = 1;
	while (is_valid_int(av[i]) && av[i])
		i++;
	if (i <= 5)
	{
		printf("Error: %s", ft_input_error(i));
		return (1);
	}
	else if (i == 6)
	{
		printf("Error: %s", ft_input_error(i));
		return (1);
	}
	return (0);
}
