/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:14:25 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/30 19:15:11 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_error(char *str, int error_code)
{
	printf("%s\n", str);
	return (error_code);
}

void	ft_free_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		// pthread_mutex_destroy(&info->forks[i]);
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	// pthread_mutex_destroy(&info->print);
	free(info->forks);
	free(philo);
}
