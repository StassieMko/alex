/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminko <aminko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:33:08 by aminko            #+#    #+#             */
/*   Updated: 2023/09/21 20:59:36 by aminko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->info->nb_philo == 1)
	{
		ft_print(philo, "has taken a fork");
		usleep(philo->info->limit_die * 1000);
		ft_print(philo, "died");
	}
	if (philo->id % 2 == 1)
		ft_usleep(philo, philo->info->eat_time * 0.25);
	while (1)
	{
		if (philo->info->nb_philo % 2 != 0 && philo->nb_meal)
			ft_usleep(philo, philo->info->eat_time / 7);
		if (take_forks(philo))
			break ;
		if (ft_eat(philo))
			break ;
		if (ft_sleep_think(philo))
			break ;
	}
	return (NULL);
}

void	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead);
	philo->info->one_dead = 1;
	pthread_mutex_unlock(&philo->info->dead);
	pthread_mutex_lock(&philo->info->print);
	printf("%08ld %d has died\n",
		gettime() - philo->info->time_start, philo->id);
	pthread_mutex_unlock(&philo->info->print);
}

void	ft_observer(t_philo *philo)
{
	int			i;
	int			finish_eat;
	long int	time;

	while (1)
	{
		i = -1;
		while (++i < philo->info->nb_philo)
		{
			pthread_mutex_lock(&philo[i].eat);
			time = gettime() - philo[i].last_eat;
			pthread_mutex_unlock(&philo[i].eat);
			if (time >= philo->info->limit_die)
			{
				is_dead(&philo[i]);
				return ;
			}
		}
		pthread_mutex_lock(&philo->info->meal);
		finish_eat = philo->info->finish_eat;
		pthread_mutex_unlock(&philo->info->meal);
		if (finish_eat == philo->info->nb_philo)
			return ;
		usleep(100);
	}
}

void	end_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nb_philo)
		pthread_join(philo[i++].tid, NULL);
	free(philo);
}

int	threads(char **av)
{
	t_info	info;
	t_philo	*philo;

	memset(&info, 0, sizeof(t_info));
	if (init_info(&info, av))
		return (1);
	philo = calloc(sizeof(t_philo), ft_atoi2(av[1]));
	if (!philo)
		return (1);
	init_philo(philo, &info);
	ft_observer(philo);
	end_simulation(philo);
	return (0);
}
