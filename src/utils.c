/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:42:30 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/01 14:36:26 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		result = result * 10 + (*s++ - '0');
	return (sign * result);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long duration)
{
	long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < duration)
		usleep(100);
}

void	log_state(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->print_lock);
	if (has_sim_ended(philo->table))
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return ;
	}
	timestamp = get_time_in_ms() - philo->table->start_of_time;
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_lock);
}

int	destroy_mutex(pthread_mutex_t *mutex, int *flag)
{
	if (*flag == 1)
	{
		pthread_mutex_destroy(mutex);
		*flag = 0;
		return (0);
	}
	return (1);
}
