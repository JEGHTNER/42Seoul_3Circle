/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:01:04 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/30 22:57:44 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_info			info;
	pid_t			pid;
	pthread_t		thread_id;
	// int				status;
	int				i;

	if (argc < 5 || argc > 6)
		return (ft_error("usage : number_of_philosophers \
time_to_die time_to_eat time_to_sleep", ARGUMENT_ERROR));
	if (ft_init_info(&info, argc, argv))
		return (ft_error("Wrong arguments", ARGUMENT_ERROR));
	if (ft_init_philo(&philo, &info))
		return (ft_error("Malloc error", MALLOC_ERROR));
	// sem_wait(info.stop);
	i = -1;
	while (++i < info.num_of_philo)
	{
		pid = fork();
		if (pid < 0)
			return (FORK_ERROR);
		if (pid == 0)
		{
			if (pthread_create(&thread_id, NULL, ft_philo, &philo[i]))
				return (THREAD_ERROR);
			ft_monitor(&philo[i]);
			pthread_join(thread_id, NULL);
			exit (STOP_SIGNAL);
		}
	}
	// sem_post(info.stop);
    while (1)
    {
    	// ft_monitor(philo);
        // waitpid(&status);
		wait(NULL);
        // if (status == STOP_SIGNAL)
        // {
        // 	send_kill_signals;
        // 	break ;
        // }
	}
    return 1;
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
