/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:26:17 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/26 15:45:41 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	check_space_sign(const char *string, int *sign)
{
	int	i;

	i = 0;
	while ((string[i] >= 9 && string[i] <= 13) || string[i] == 32)
			i++;
	if (string[i] == '-' || string[i] == '+')
	{
		if (string[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

static int	check_overflow(unsigned long long result)
{
	if (result != 0 && (result * 10 <= result))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *string)
{
	int							sign;
	int							i;
	int							over_flow;
	unsigned long long			result;

	sign = 1;
	result = 0;
	over_flow = 0;
	i = check_space_sign(string, &sign);
	while (ft_isdigit(string[i]))
	{
		over_flow = check_overflow(result);
		result = result * 10 + string[i] - '0' ;
		over_flow = check_overflow(result);
		if (sign == 1 && over_flow)
			return (-1);
		else if (sign == -1 && over_flow)
			return (0);
		i++;
	}
	return (result * sign);
}
