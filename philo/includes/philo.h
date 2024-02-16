/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminko <aminko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:29:19 by aminko            #+#    #+#             */
/*   Updated: 2023/09/21 21:05:23 by aminko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

typedef struct s_info
{
	long int		time_start;
	int				limit_die;
	int				eat_time;
	int				sleep_time;
	int				finish_eat;
	int				need_eat;
	int				nb_philo;
	int				one_dead;
	int				finished;
	pthread_t		observer;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	meal;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	long int		last_eat;
	int				nb_meal;
	pthread_mutex_t	eat;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	t_info			*info;
}	t_philo;

int			parsing(int ac, char **av);
int			ft_atoi2(char *str);
int			ft_isdigit(int c);
long int	gettime(void);
int			init_info(t_info *info, char **av);
int			ft_print(t_philo *philo, char *str);
int			check_die(t_philo *philo);
int			take_forks(t_philo *philo);
int			ft_eat(t_philo *philo);
int			ft_sleep_think(t_philo *philo);
void		*ft_routine(void *data);
int			threads(char **av);
void		init_philo(t_philo *philo, t_info *info);
int			ft_usleep(t_philo *philo, long int time);

#endif
