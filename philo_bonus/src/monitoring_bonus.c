/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:49:54 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/01 21:56:31 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_monitor(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	while (1)
	{
		if (check_dead(philo, info))
			return ;
	}
}

void	ft_kill(t_philo *philo)
{
	t_info	*info;
	int		i;

	info = philo->info;
	sem_wait(info->stop);
	sem_wait(info->check);
	info->is_dead = 1;
	sem_post(info->check);
	i = 0;
	while (i < info->num_of_philo)
		kill(philo[i++].pid, SIGTERM);
	sem_close(info->forks);
	sem_close(info->print);
	sem_close(info->stop);
	sem_post(info->must_eat);
	sem_close(info->must_eat);
	sem_close(info->check);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/must_eat");
	sem_unlink("/check");
	free(philo);
	return ;
}

void	*check_is_full(void *arg)
{
	t_info	*info;
	int		i;

	info = arg;
	i = 0;
	while (i++ < info->num_of_philo)
	{
		sem_wait(info->check);
		if (info->is_dead == 1)
		{
			sem_post(info->check);
			return (NULL);
		}
		sem_post(info->check);
		sem_wait(info->must_eat);
	}
	sem_wait(info->print);
	printf("All philos are full\n");
	sem_post(info->stop);
	sem_post(info->print);
	return (NULL);
}

int	print_philo(t_philo *philo, char *str)
{
	sem_wait(philo->info->print);
	if (philo->info->is_dead || philo->info->is_full)
	{
		sem_post(philo->info->print);
		return (1);
	}
	printf("%lld %d %s\n", ft_get_time() - \
	philo->info->start_time, philo->id, str);
	sem_post(philo->info->print);
	return (0);
}

int	check_dead(t_philo *philo, t_info *info)
{
	long long	time;
	long long	last_eat_time;

	sem_wait(philo->check);
	last_eat_time = philo->last_eat_time;
	sem_post(philo->check);
	time = ft_get_time();
	sem_wait(info->print);
	if (time - last_eat_time > info->time_to_die && !philo->full)
	{
		printf("%lld %d died\n", time - info->start_time, philo->id);
		sem_post(info->stop);
		return (1);
	}
	sem_post(info->print);
	return (0);
}
