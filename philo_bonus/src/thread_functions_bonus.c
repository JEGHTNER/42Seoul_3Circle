/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:48:17 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/01 21:27:35 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time_to_eat, philo->info);
	if (philo->info->num_of_philo == 1)
		return (ft_eat_case1(philo));
	while (1)
	{
		ft_eat_bonus(philo);
		ft_sleep(philo);
		ft_think(philo);
		sem_wait(philo->info->print);
		if (philo->info->is_dead == 1 || philo->info->is_full == 1)
		{
			sem_post(philo->info->print);
			return (NULL);
		}
		sem_post(philo->info->print);
	}
	return (NULL);
}

void	ft_eat_bonus(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	sem_wait(info->forks);
	print_philo(philo, "has taken a fork");
	sem_wait(info->forks);
	print_philo(philo, "has taken a fork");
	print_philo(philo, "is eating");
	++(philo->eat_count);
	sem_wait(philo->check);
	philo->last_eat_time = ft_get_time();
	if (info->num_of_must_eat > 0 && \
	philo->eat_count == info->num_of_must_eat)
		sem_post(info->must_eat);
	sem_post(philo->check);
	ft_usleep(info->time_to_eat, info);
	sem_post(info->forks);
	sem_post(info->forks);
}

void	*ft_eat_case1(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	sem_wait(info->forks);
	print_philo(philo, "has taken a fork");
	sem_post(info->forks);
	return (NULL);
}

void	ft_sleep(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	sem_wait(info->print);
	if (info->is_dead == 1 || info->is_full == 1)
	{
		sem_post(info->print);
		return ;
	}
	sem_post(info->print);
	print_philo(philo, "is sleeping");
	ft_usleep(info->time_to_sleep, info);
}

void	ft_think(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	sem_wait(info->print);
	if (info->is_dead == 1 || info->is_full == 1)
	{
		sem_post(info->print);
		return ;
	}
	sem_post(info->print);
	print_philo(philo, "is thinking");
}
