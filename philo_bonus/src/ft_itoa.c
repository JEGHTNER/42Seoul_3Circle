/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:18:39 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/01 17:19:04 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static long long	get_abs(int number)
{
	long long	lnum;

	lnum = (long long)number;
	if (lnum < 0)
		return (lnum * -1);
	return (lnum);
}

static int	count_digits(int number)
{
	int			digits;
	long long	lnum;

	lnum = (long long)number;
	if (lnum == 0)
		return (1);
	digits = 0;
	if (lnum < 0)
		digits += 1;
	lnum = get_abs(number);
	while (lnum > 0)
	{
		lnum /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int number)
{
	int			digits;
	long long	lnum;
	char		*tmp_string;

	lnum = (long long)number;
	digits = count_digits(number);
	tmp_string = malloc(sizeof(char) * (digits + 1));
	if (!tmp_string)
		return (0);
	if (lnum == 0)
		tmp_string[0] = '0';
	if (lnum < 0)
		tmp_string[0] = '-';
	lnum = get_abs(number);
	tmp_string[digits] = '\0';
	while (lnum > 0)
	{
		tmp_string[--digits] = (lnum % 10) + '0';
		lnum /= 10;
	}
	return (tmp_string);
}