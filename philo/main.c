/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:01:04 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/22 16:37:43 by jehelee          ###   ########.fr       */
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

int	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// int	ft_usleep(long long time)
// {
// 	long long	finish_time;

// 	finish_time = time + ft_get_time();
// 	while (finish_time > ft_get_time())
// 		usleep(100);
// 	return (0);
// }

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
	return(0);
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
	info->dead_id = 0;
	info->is_full = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->forks)
		return (MALLOC_ERROR);
	info->print = malloc(sizeof(pthread_mutex_t));
	if (!info->print)
		return (MALLOC_ERROR);
	info->dead = malloc(sizeof(pthread_mutex_t));
	if (!info->dead)
		return (MALLOC_ERROR);
	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (MUTEX_ERROR);
		i++;
	}
	// if (pthread_mutex_init(info->is_full, NULL))
	// 	return (MUTEX_ERROR);
	// if (pthread_mutex_init(info->forks, NULL))
	// 	return (MUTEX_ERROR);
	if (pthread_mutex_init(info->print, NULL))
		return (MUTEX_ERROR);
	if (pthread_mutex_init(info->dead, NULL))
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
		(*philo)[i].forks = info->forks;
		(*philo)[i].print = info->print;
		(*philo)[i].dead = info->dead;
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
	// info->start_time = ft_get_time();
	while (i < info->num_of_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, ft_philo, &philo[i]))
			return (THREAD_ERROR);
		// pthread_detach(philo[i].thread_id);
		// pthread_join(philo[i].thread_id, NULL);
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
		// printf("%d is full: %d\t",philo[i].id, philo[i].full);
		if (!philo[i].full)
			is_full = 0;
		i++;
	}
	if (is_full)
	{
		philo->info->is_full = 1;
		pthread_mutex_lock(philo->info->print);
		printf("All philo is full\n");
		// pthread_mutex_unlock(philo->info->print);
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
			time = ft_get_time();
			pthread_mutex_lock(info->print);
			if (time - philo[i].last_eat_time > info->time_to_die && !philo[i].full)
			{
				// pthread_mutex_lock(info->print);
				// pthread_mutex_lock(info->dead);
				if (!info->is_dead)
				{
					info->is_dead = 1;
					// pthread_mutex_lock(info->print);
					printf("died time:%d\n",time - philo[i].last_eat_time);
					printf("%d %d died\n", time - info->start_time, philo[i].id);
					// usleep(100000);
					// pthread_mutex_unlock(info->print);
				}
				// pthread_mutex_unlock(info->dead);
				return ;
			}
			pthread_mutex_unlock(info->print);
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

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time_to_eat, philo->info);
	// pthread_mutex_lock(philo->dead);
	while (1)
	{
		pthread_mutex_lock(philo->dead);
		if (philo->info->is_dead || philo->info->is_full)
		{
			pthread_mutex_unlock(philo->dead);
			return (NULL);
		}
		pthread_mutex_unlock(philo->dead);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	// pthread_mutex_unlock(philo->dead);
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
	pthread_mutex_lock(philo->forks + philo->left_fork);
	pthread_mutex_lock(philo->forks + philo->right_fork);
	// philo->last_eat_time = ft_get_time();
	pthread_mutex_lock(philo->info->print);
	// printf("%d %d has taken a fork\n", philo->last_eat_time - info->start_time,
	// 		philo->id);
	// printf("%d %d has taken a fork\n", philo->last_eat_time - info->start_time,
	// 		philo->id);
	// printf("%d %d is eating %d\n", philo->last_eat_time - info->start_time,
	// 		philo->id, philo->eat_count);
	printf("%d %d has taken a fork\n", ft_get_time() - info->start_time,
			philo->id);
	printf("%d %d has taken a fork\n", ft_get_time() - info->start_time,
			philo->id);
	// philo->last_eat_time = ft_get_time();
	// printf("%d %d is eating %d\n", philo->last_eat_time - info->start_time,
	// 		philo->id, ++(philo->eat_count));
	printf("%d %d is eating %d\n", ft_get_time() - info->start_time,
			philo->id, ++(philo->eat_count));
	pthread_mutex_unlock(philo->info->print);
	philo->last_eat_time = ft_get_time();
	ft_usleep(info->time_to_eat, info);
	// philo->last_eat_time = ft_get_time();
	// philo->eat_count++;
	pthread_mutex_unlock(philo->forks + philo->left_fork);
	pthread_mutex_unlock(philo->forks + philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (info->is_dead == 1 || info->is_full == 1)
		return ;
	pthread_mutex_lock(philo->info->print);
	printf("%d %d is sleeping\n", ft_get_time() - info->start_time, philo->id);
	pthread_mutex_unlock(philo->info->print);
	ft_usleep(info->time_to_sleep, info);
}

void	ft_think(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (info->is_dead == 1 || info->is_full == 1)
		return ;
	pthread_mutex_lock(philo->info->print);
	printf("%d %d is thinking\n", ft_get_time() - info->start_time, philo->id);
	pthread_mutex_unlock(philo->info->print);
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
	// pthread_mutex_unlock(info->print);
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
