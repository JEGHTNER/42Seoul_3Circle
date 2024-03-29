/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:01:04 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/01 21:37:33 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_info			*info = malloc(sizeof(t_info));
	pthread_t		thread_id;
	pthread_t		thread_id2;


	int				i;

	if (argc < 5 || argc > 6)
		return (ft_error("usage : number_of_philosophers \
time_to_die time_to_eat time_to_sleep", ARGUMENT_ERROR));
	if (ft_init_info(info, argc, argv))
		return (ft_error("Wrong arguments", ARGUMENT_ERROR));
	if (ft_init_philo(&philo, info))
		return (ft_error("Malloc error", MALLOC_ERROR));
	i = -1;
	sem_wait(info->stop);
	while (++i < info->num_of_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (FORK_ERROR);
		if (philo[i].pid == 0)
		{
			if (pthread_create(&thread_id, NULL, ft_philo, &philo[i]))
				return (THREAD_ERROR);
			ft_monitor(&philo[i]);
			pthread_join(thread_id, NULL);
			exit (STOP_SIGNAL);
		}
	}
	if (info->num_of_must_eat != 0 && info->num_of_philo > 1)
	{
		pthread_create(&thread_id2, NULL, check_is_full, info);
		pthread_detach(thread_id2);
	}
	ft_kill(philo);
    return (0);
}
