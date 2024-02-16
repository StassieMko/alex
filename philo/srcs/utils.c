/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminko <aminko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:40:25 by aminko            #+#    #+#             */
/*   Updated: 2023/09/19 21:48:00 by aminko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print(t_philo *philo, char *str)
{
	if (check_die(philo))
		return (1);
	pthread_mutex_lock(&philo->info->print);
	printf("%08ld %d %s\n", gettime() - philo->info->time_start, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}

long int	gettime(void)
{
	struct timeval	time;
	long int		timein_ms;

	gettimeofday(&time, NULL);
	timein_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timein_ms);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi2(char *str)
{
	int		sign;
	int		i;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (0);
		i++;
	}
	if (str[i])
		return (0);
	return (result * sign);
}

/* void	destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i++ < philo->info->nb_philo)
		pthread_mutex_destroy(&philo->fork_left);
	pthread_mutex_destroy(&philo->info->print);
	pthread_mutex_destroy(&philo->info->dead);
	pthread_mutex_destroy(&philo->info->meal);
} */

int	ft_usleep(t_philo *philo, long int time)
{
	long int	start;

	start = gettime();
	while (gettime() - start < time)
	{
		if (check_die(philo))
			return (1);
		usleep(10);
	}
	return (0);
}

/*void	ft_usleep(long time_to_sleep)
{
	long	begin;

	begin = gettime();
	while (gettime() - begin < time_to_sleep)
		usleep(5);
}*/
