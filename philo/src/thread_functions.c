/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:48:17 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/29 17:32:01 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		pthread_mutex_lock(&philo->info->print);
		if (philo->info->is_dead == 1 || philo->info->is_full == 1)
		{
			pthread_mutex_unlock(&philo->info->print);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->print);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->forks[philo->left_fork]);
	print_philo(philo, "has taken a fork");
	pthread_mutex_lock(&info->forks[philo->right_fork]);
	print_philo(philo, "has taken a fork");
	print_philo(philo, "is eating");
	++(philo->eat_count);
	pthread_mutex_lock(&info->print);
	philo->last_eat_time = ft_get_time();
	if (info->num_of_must_eat > 0 && \
	philo->eat_count >= info->num_of_must_eat)
		philo->full = 1;
	pthread_mutex_unlock(&info->print);
	ft_usleep(info->time_to_eat, info);
	pthread_mutex_unlock(&info->forks[philo->left_fork]);
	pthread_mutex_unlock(&info->forks[philo->right_fork]);
}

void	*ft_eat_case1(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->forks[philo->left_fork]);
	print_philo(philo, "has taken a fork");
	pthread_mutex_unlock(&info->forks[philo->left_fork]);
	return (NULL);
}

void	ft_sleep(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->print);
	if (info->is_dead == 1 || info->is_full == 1)
	{
		pthread_mutex_unlock(&info->print);
		return ;
	}
	pthread_mutex_unlock(&info->print);
	print_philo(philo, "is sleeping");
	ft_usleep(info->time_to_sleep, info);
}

void	ft_think(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->print);
	if (info->is_dead == 1 || info->is_full == 1)
	{
		pthread_mutex_unlock(&info->print);
		return ;
	}
	pthread_mutex_unlock(&info->print);
	print_philo(philo, "is thinking");
}
