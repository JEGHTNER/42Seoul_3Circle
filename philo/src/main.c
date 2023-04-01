/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:01:04 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/01 19:43:07 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_info	info;

	if (argc < 5 || argc > 6)
		return (ft_error("usage : number_of_philosophers \
time_to_die time_to_eat time_to_sleep", ARGUMENT_ERROR));
	if (ft_init_info(&info, argc, argv))
		return (ft_error("Wrong arguments", ARGUMENT_ERROR));
	if (ft_init_philo(&philo, &info))
		return (ft_error("Malloc error", MALLOC_ERROR));
	if (ft_start_philo(philo, &info))
		return (ft_error("Thread error", THREAD_ERROR));
	ft_free_philo(philo, &info);
	return (SUCCESS);
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
