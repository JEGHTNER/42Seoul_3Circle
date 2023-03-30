/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:43:34 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/30 23:22:57 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	ft_get_time(void)
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
