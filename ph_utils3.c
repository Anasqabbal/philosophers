/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 08:56:01 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/14 10:43:54 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	to_get(pthread_mutex_t *mtx, t_list *ph, int ind)
{
	long	res;

	if (ind == 0)
	{
		pthread_mutex_lock(mtx);
		res = ph->sta_ea;
		pthread_mutex_unlock(mtx);
	}
	if (ind == 1)
	{
		pthread_mutex_lock(mtx);
		res = ph->a->tm_to_die;
		pthread_mutex_unlock(mtx);
	}
	if (ind == 2)
	{
		pthread_mutex_lock(mtx);
		res = get_time();
		pthread_mutex_unlock(mtx);
	}
	return (res);
}

void	to_set(pthread_mutex_t *mtx, int *var, int val)
{
	pthread_mutex_lock(mtx);
	*var = val;
	pthread_mutex_unlock(mtx);
}

int	to_check(pthread_mutex_t *mtx, int *var, int val)
{
	pthread_mutex_lock(mtx);
	if (*var == val)
		return (pthread_mutex_unlock(mtx), 0);
	pthread_mutex_unlock(mtx);
	return (1);
}

void	ft_usleep(long long tt_sleep)
{
	long long	start;

	start = get_time();
	while (get_time() - start < tt_sleep)
		usleep(500);
}
