/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:44:32 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/01 21:54:05 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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

int	ft_init_semaphore(t_info *info)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/must_eat");
	sem_unlink("/check");
	sem_unlink("/dead");
	info->forks = sem_open("/forks", O_CREAT, 0644, info->num_of_philo);
	if (info->forks == SEM_FAILED)
		return (SEMAPHORE_ERROR);
	info->print = sem_open("/print", O_CREAT, 0644, 1);
	if (info->print == SEM_FAILED)
		return (SEMAPHORE_ERROR);
	info->stop = sem_open("/stop", O_CREAT, 0644, 1);
	if (info->stop == SEM_FAILED)
		return (SEMAPHORE_ERROR);
	info->must_eat = sem_open("/must_eat", O_CREAT, 0644, 1);
	if (info->must_eat == SEM_FAILED)
		return (SEMAPHORE_ERROR);
	info->check = sem_open("/check", O_CREAT, 0644, 1);
	if (info->must_eat == SEM_FAILED)
		return (SEMAPHORE_ERROR);
	info->dead = sem_open("/dead", O_CREAT, 0644, 1);
	if (info->must_eat == SEM_FAILED)
		return (SEMAPHORE_ERROR);
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
	if (ft_init_semaphore(info))
		return (SEMAPHORE_ERROR);
	info->start_time = ft_get_time();
	return (0);
}

int	ft_init_philo(t_philo **philo, t_info *info)
{
	int		i;
	char	*name;

	*philo = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philo);
	if (!*philo)
		return (MALLOC_ERROR);
	i = 0;
	while (i < info->num_of_philo)
	{
		name = ft_itoa((*philo)[i].id);
		sem_unlink(name);
		(*philo)[i].check = sem_open(name, O_CREAT, 0644, 1);
		free(name);
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
