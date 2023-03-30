/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:49:54 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/30 22:56:48 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_monitor(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	while (1)
	{
		if (info->num_of_must_eat != 0)
		{
			if (check_is_full(philo))
				return ;
		}
		if (check_dead(philo, info))
			return ;
	}
}

int	check_is_full(t_philo *philo)
{
	int	i;
	int	is_full;

	i = 0;
	is_full = 1;
	while (i < philo->info->num_of_philo)
	{
		sem_wait(philo->info->print);
		if (!philo[i].full)
			is_full = 0;
		sem_post(philo->info->print);
		i++;
	}
	if (is_full)
	{
		philo->info->is_full = 1;
		sem_wait(philo->info->print);
		printf("All philo is full\n");
		sem_post(philo->info->print);
	}
	return (is_full);
}

int	print_philo(t_philo *philo, char *str)
{
	sem_wait(philo->info->stop);
	sem_wait(philo->info->print);
	if (philo->info->is_dead || philo->info->is_full)
	{

		sem_post(philo->info->stop);
		sem_post(philo->info->print);
		return (1);
	}
	sem_post(philo->info->stop);
	printf("%lld %d %s\n", ft_get_time() - \
	philo->info->start_time, philo->id, str);
	sem_post(philo->info->print);
	return (0);
}

int	check_dead(t_philo *philo, t_info *info)
{
	long long	time;
	long long	last_eat_time;

	sem_wait(info->print);
	last_eat_time = philo->last_eat_time;
	sem_post(info->print);
	time = ft_get_time();
	if (time - last_eat_time > info->time_to_die && !philo->full)
	{
		if (!info->is_dead)
		{
			sem_wait(info->stop);
			sem_wait(info->print);
			info->is_dead = 1;
			printf("%lld %d died\n", time - info->start_time, philo->id);
			sem_post(info->print);
		}
		return (1);
	}
	return (0);
}
