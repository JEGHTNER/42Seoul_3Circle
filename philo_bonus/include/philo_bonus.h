/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:01:28 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/30 20:43:50 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

enum	e_errno
{
	SUCCESS,
	ARGUMENT_ERROR,
	THREAD_ERROR,
	SEMAPHORE_ERROR,
	MALLOC_ERROR,
	FORK_ERROR,
	STOP_SIGNAL
};

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				left_fork;
	int				right_fork;
	int				full;
	long long		last_eat_time;
	pthread_t		thread_id;
	struct s_info	*info;
}				t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				is_dead;
	int				is_full;
	long long		start_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*stop;
}				t_info;

//free_error_utils.c
int			ft_error(char *str, int error_code);
void		ft_free_philo(t_philo *philo, t_info *info);

//ft_atoi.c
int			ft_isdigit(int c);
int			ft_atoi(const char *string);

//init_functions.c
int			check_argv(int argc, char **argv, t_info *info);
int			ft_init_info(t_info *info, int argc, char **argv);
int			ft_init_philo(t_philo **philo, t_info *info);
int			ft_init_semaphore(t_info *info);

//monitoring.c
void		ft_monitor(t_philo *philo);
int			check_is_full(t_philo *philo);
int			print_philo(t_philo *philo, char *str);
int			check_dead(t_philo *philo, t_info *info);

//thread_functions.c
int			ft_start_philo(t_philo *philo, t_info *info);
void		*ft_philo(void *arg);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		*ft_eat_case1(t_philo *philo);


//time_utils.c
long long	ft_get_time(void);
int			ft_usleep(long long time_to_sleep, t_info *info);

#endif
