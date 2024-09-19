/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:42:34 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/19 08:59:33 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_sign(const char *str, int *i, int *sign)
{
	if (str[(*i)] == '-' || str[(*i)] == '+')
	{
		if (str[(*i)++] == '-')
			(*sign) *= -1;
	}
}

static long long	a_return_with(const char *str
	, long long res, int sign, int *ind)
{
	if (str[0] == '\0' && sign == 1)
	{
		if (res * sign == 0 || res < 0 || (res * sign) < 0)
			return (*ind = 1, 1);
		return (*ind = 0, res * sign);
	}
	else
		return (*ind = 1, 1);
}

static long long	return_check(const char *str
	, long long res, int *ind, int sign)
{
	long long	old_res;
	int			i;

	i = 0;
	old_res = res;
	while ((str[i] >= 48 && str[i] <= 57))
	{
		if (res >= old_res && (str[i] >= 48 && str[i] <= 57))
		{
			old_res = res;
			res = res * 10 + (str[i++] - 48);
		}
		else if ((str[i] >= 48 && str[i] <= 57))
		{
			if (sign < 0)
				return (0);
			else
				return (-1);
		}
	}
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (a_return_with(str + i, res, sign, ind));
}

long long	ph_atoi(const char *str, int *ind)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	check_sign(str, &i, &sign);
	return (return_check(str + i, res, ind, sign));
}
