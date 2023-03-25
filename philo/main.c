/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:01:04 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/25 20:08:37 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

enum	e_errno
{
	ARGUMENT_ERROR,
	THREAD_ERROR,
	MUTEX_ERROR,
	MALLOC_ERROR
};

void	*ft_philo(void *arg);
void	ft_monitor(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_free_philo(t_philo *philo, t_info *info);
int		print_philo(t_philo *philo, char *str);

int	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(long long time_to_sleep, t_info *info)
{
	long long	start;

	start = ft_get_time();
	while (1)
	{
		if (ft_get_time() - start >= time_to_sleep)
			break ;
		usleep(info->num_of_philo * 2);
	}
	return (0);
}

int	ft_init_info(t_info *info, int argc, char **argv)
{
	int	i;
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->num_of_must_eat = -1;
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[5]);
	info->start_time = ft_get_time();
	info->is_dead = 0;
	info->is_full = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->forks)
		return (MALLOC_ERROR);
	info->print = malloc(sizeof(pthread_mutex_t));
	if (!info->print)
		return (MALLOC_ERROR);
	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (MUTEX_ERROR);
		i++;
	}
	if (pthread_mutex_init(info->print, NULL))
		return (MUTEX_ERROR);
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
		(*philo)[i].is_eating = 0;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % info->num_of_philo;
		(*philo)[i].last_eat_time = ft_get_time();
		(*philo)[i].full = 0;
		(*philo)[i].info = info;
		i++;
	}
	return (0);
}

int	ft_start_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, ft_philo, &philo[i]))
			return (THREAD_ERROR);
		i++;
	}
	ft_monitor(philo);
	return (0);
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
		pthread_mutex_lock(philo->info->print);
		printf("All philo is full\n");
		pthread_mutex_unlock(philo->info->print);
	}
	return (is_full);
}

void	ft_monitor(t_philo *philo)
{
	int		i;
	int		time;
	t_info	*info;

	info = philo->info;
	while (1)
	{
		if (info->num_of_must_eat != -1)
		{
			if (check_is_full(philo))
				return ;
		}
		i = 0;
		while (i < info->num_of_philo)
		{
			// pthread_mutex_lock(info->print);
			time = ft_get_time();
			if (time - philo[i].last_eat_time > info->time_to_die && !philo[i].full)
			{
				if (!info->is_dead)
				{
					info->is_dead = 1;
					pthread_mutex_lock(info->print);
					printf("died time:%d\n",time - philo[i].last_eat_time);
					printf("%d %d died\n", time - info->start_time, philo[i].id);
					pthread_mutex_unlock(info->print);
				}
				// pthread_mutex_unlock(info->dead);
				// pthread_mutex_unlock(info->print);
				return ;
			}
			// pthread_mutex_unlock(info->print);
			i++;
		}
		// if (info->is_dead == 1)
		// {
		// 	pthread_mutex_lock(info->print);
		// 	printf("%d %d died\n", ft_get_time() - info->start_time, info->dead_id);
		// 	return ;
		// }
	}
}

int	print_philo(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->info->print);
	if (philo->info->is_dead || philo->info->is_full)
	{
		pthread_mutex_unlock(philo->info->print);
		return (1);
	}
	printf("%d %d %s\n", ft_get_time() - philo->info->start_time, philo->id, str);
	pthread_mutex_unlock(philo->info->print);
	return (0);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time_to_eat, philo->info);
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (info->num_of_must_eat != -1 && philo->eat_count >= info->num_of_must_eat)
	{
		philo->full = 1;
		// return ;
	}
	pthread_mutex_lock(info->forks + philo->left_fork);
	print_philo(philo, "has taken a fork");
	pthread_mutex_lock(info->forks + philo->right_fork);
	print_philo(philo, "has taken a fork");
	// pthread_mutex_lock(philo->info->print);
	// printf("%d %d has taken a fork\n", ft_get_time() - info->start_time,
	// 		philo->id);
	// printf("%d %d has taken a fork\n", ft_get_time() - info->start_time,
	// 		philo->id);
	print_philo(philo, "is eating");
	++(philo->eat_count);
	// printf("%d %d is eating %d\n", ft_get_time() - info->start_time,
	// 		philo->id, ++(philo->eat_count));
	// pthread_mutex_unlock(philo->info->print);
	philo->last_eat_time = ft_get_time();
	// pthread_mutex_unlock(philo->info->print);

	ft_usleep(info->time_to_eat, info);
	pthread_mutex_unlock(info->forks + philo->left_fork);
	pthread_mutex_unlock(info->forks + philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (info->is_dead == 1 || info->is_full == 1)
		return ;
	print_philo(philo, "is sleeping");
	// printf("%d %d is sleeping\n", ft_get_time() - info->start_time, philo->id);
	// pthread_mutex_unlock(philo->info->print);
	ft_usleep(info->time_to_sleep, info);
}

void	ft_think(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (info->is_dead == 1 || info->is_full == 1)
		return ;
	print_philo(philo, "is thinking");
	// printf("%d %d is thinking\n", ft_get_time() - info->start_time, philo->id);
	// pthread_mutex_unlock(philo->info->print);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_info	info;

	if (argc < 5 || argc > 6)
		return (ft_error("usage : number_of_philosophers \
time_to_die time_to_eat time_to_sleep"));
	if (ft_init_info(&info, argc, argv))
		return (ft_error("Wrong arguments"));
	if (ft_init_philo(&philo, &info))
		return (ft_error("Malloc error"));
	if (ft_start_philo(philo, &info))
		return (ft_error("Thread error"));
	ft_free_philo(philo, &info);
	return (0);
}

void	ft_free_philo(t_philo *philo, t_info *info)
{
	int	i;

	usleep(1000);
	pthread_mutex_unlock(info->print);
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(info->forks + i);
		pthread_detach(philo[i].thread_id);
		i++;
	}
	free(info->forks);
	free(philo);
}
