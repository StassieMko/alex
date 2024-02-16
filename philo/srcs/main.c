/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminko <aminko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:50:21 by aminko            #+#    #+#             */
/*   Updated: 2023/09/21 18:56:26 by aminko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(t_info *info, char **av)
{
	info->limit_die = atoi(av[2]);
	info->eat_time = atoi(av[3]);
	info->sleep_time = atoi(av[4]);
	if (av[5])
		info->need_eat = atoi(av[5]);
	else
		info->need_eat = -1;
	info->nb_philo = atoi(av[1]);
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->dead, NULL);
	pthread_mutex_init(&info->meal, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die \
				time_to_eat time_to_sleep \
				[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (parsing(ac, av))
		return (1);
	threads(av);
	return (0);
}
