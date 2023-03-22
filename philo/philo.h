/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:01:28 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/22 14:57:53 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				is_eating;
	int				left_fork;
	int				right_fork;
	int				last_eat_time;
	int				full;
	pthread_t		thread_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
	struct s_info	*info;
}				t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				start_time;
	int				is_dead;
	int				dead_id;
	int				is_full;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
}				t_info;

int		ft_atoi(const char *string);
int		ft_error(char *str);
void	ft_putstr_fd(char *str);



#endif
