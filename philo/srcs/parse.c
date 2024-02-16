/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminko <aminko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:28:26 by aminko            #+#    #+#             */
/*   Updated: 2023/09/21 20:58:35 by aminko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int	parsing(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j] && av[i][j] == ' ')
			j++;
		if (!av[i][j])
			return (printf("Error: empty argument\n"), 1);
		if (av[i][j] == '-')
			return (printf("Error: invalid argument\n"), 1);
		if (av[i][j] == '+' && ft_isdigit(av[i][++j]) == 0)
			return (printf("Error: invalid argument\n"), 1);
		if (av[i][j] && (av[i][j] == '-' || av[i][j] == '+'))
			return (printf("Error: invalid argument\n"), 1);
		if (ft_atoi2(&av[i][j]) == 0)
			return (printf("Error: invalid argument\n"), 1);
		if (check_num(&av[i][j]) == 0)
			return (printf("Error: invalid argument\n"), 1);
	}
	return (0);
}

void	init_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = -1;
	info->time_start = gettime();
	while (++i < info->nb_philo)
	{
		philo[i].id = i + 1;
		pthread_mutex_init(&philo[i].fork_left, NULL);
		pthread_mutex_init(&philo[i].eat, NULL);
		philo[i].info = info;
		philo[i].last_eat = info->time_start;
		if (i == info->nb_philo - 1)
			philo[i].fork_right = &philo[0].fork_left;
		else
			philo[i].fork_right = &philo[i + 1].fork_left;
	}
	i = -1;
	while (++i < info->nb_philo)
		pthread_create(&philo[i].tid, NULL, ft_routine, (void *)&philo[i]);
}
