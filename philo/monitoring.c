/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:49:54 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/26 19:01:30 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (check_dead(philo))
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
		if (!philo[i].full)
			is_full = 0;
		i++;
	}
	if (is_full)
	{
		philo->info->is_full = 1;
		pthread_mutex_lock(&philo->info->print);
		printf("All philo is full\n");
		pthread_mutex_unlock(&philo->info->print);
	}
	return (is_full);
}

int	print_philo(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->print);
	if (philo->info->is_dead || philo->info->is_full)
	{
		pthread_mutex_unlock(&philo->info->print);
		return (1);
	}
	printf("%d %d %s\n", ft_get_time() - \
	philo->info->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}

int	check_dead(t_philo *philo)
{
	int		time;
	int		i;
	t_info	*info;

	i = 0;
	info = philo->info;
	while (i < info->num_of_philo)
	{
		time = ft_get_time();
		if (time - philo[i].last_eat_time > info->time_to_die && !philo[i].full)
		{
			if (!info->is_dead)
			{
				info->is_dead = 1;
				pthread_mutex_lock(&info->print);
				printf("died time:%d\n", time - philo[i].last_eat_time);
				printf("%d %d died\n", time - info->start_time, philo[i].id);
				pthread_mutex_unlock(&info->print);
			}
			return (1);
		}
		i++;
	}
	return (0);
}
