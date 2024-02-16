/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminko <aminko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:01:26 by aminko            #+#    #+#             */
/*   Updated: 2023/09/19 21:48:09 by aminko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->info->dead);
	dead = philo->info->one_dead;
	pthread_mutex_unlock(&philo->info->dead);
	return (dead);
}

void	release_forks(t_philo *philo, bool left, bool right)
{
	if (left)
		pthread_mutex_unlock(&philo->fork_left);
	if (right)
		pthread_mutex_unlock(philo->fork_right);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_left);
		if (ft_print(philo, "has taken a fork"))
			return (release_forks(philo, true, false), 1);
		pthread_mutex_lock(philo->fork_right);
		if (ft_print(philo, "has taken a fork"))
			return (release_forks(philo, true, true), 1);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		if (ft_print(philo, "has taken a fork"))
			return (release_forks(philo, false, true), 1);
		pthread_mutex_lock(&philo->fork_left);
		if (ft_print(philo, "has taken a fork"))
			return (release_forks(philo, true, true), 1);
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (ft_print(philo, "is eating"))
		return (release_forks(philo, true, true), 1);
	ft_usleep(philo, philo->info->eat_time);
	pthread_mutex_lock(&philo->eat);
	philo->last_eat = gettime();
	pthread_mutex_unlock(&philo->eat);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	if (philo->nb_meal == philo->info->need_eat)
	{
		pthread_mutex_lock(&philo->info->meal);
		philo->info->finish_eat++;
		pthread_mutex_unlock(&philo->info->meal);
		return (1);
	}
	return (0);
}

int	ft_sleep_think(t_philo *philo)
{
	if (ft_print(philo, "is sleeping"))
		return (1);
	ft_usleep(philo, philo->info->sleep_time);
	if (ft_print(philo, "is thinking"))
		return (1);
	return (0);
}
