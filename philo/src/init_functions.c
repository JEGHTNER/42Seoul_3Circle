/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:44:32 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/28 14:21:17 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_argv(int argc, char **argv, t_info *info)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (ARGUMENT_ERROR);
			if (ft_atoi(argv[i]) < 0)
				return (ARGUMENT_ERROR);
			j++;
		}
		i++;
	}
	if (info->num_of_philo < 1 || info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0)
		return (ARGUMENT_ERROR);
	if (argc == 6 && info->num_of_must_eat < 1)
		return (ARGUMENT_ERROR);
	return (0);
}

int	ft_init_mutex(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (MUTEX_ERROR);
	}
	if (pthread_mutex_init(&info->print, NULL))
		return (MUTEX_ERROR);
	return (0);
}

int	ft_init_info(t_info *info, int argc, char **argv)
{
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->num_of_must_eat = 0;
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[5]);
	info->is_dead = 0;
	info->is_full = 0;
	if (check_argv(argc, argv, info))
		return (ARGUMENT_ERROR);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->forks)
		return (MALLOC_ERROR);
	if (ft_init_mutex(info))
		return (MUTEX_ERROR);
	info->start_time = ft_get_time();
	return (0);
}

int	ft_init_philo(t_philo **philo, t_info *info)
{
	int	i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philo);
	if (!*philo)
		return (MALLOC_ERROR);
	i = 0;
	while (i < info->num_of_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].eat_count = 0;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % info->num_of_philo;
		(*philo)[i].last_eat_time = ft_get_time();
		(*philo)[i].full = 0;
		(*philo)[i].info = info;
		i++;
	}
	return (0);
}

// int	ft_init_philo(t_philo *philo, t_info *info)
// {
// 	int	i;

// 	i = 0;
// 	while (i < info->num_of_philo)
// 	{
// 		(philo)[i].id = i + 1;
// 		(philo)[i].eat_count = 0;
// 		(philo)[i].left_fork = i;
// 		(philo)[i].right_fork = (i + 1) % info->num_of_philo;
// 		(philo)[i].last_eat_time = ft_get_time();
// 		(philo)[i].full = 0;
// 		(philo)[i].info = info;
// 		i++;
// 	}
// 	return (0);
// }
