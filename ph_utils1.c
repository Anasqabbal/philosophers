/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:29:03 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/31 17:53:01 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void one_philo(t_list *ph)
{
	while(1)
	{
		pthread_mutex_lock(ph->a->to_check);
		if (!ph->a->die)
		{
			pthread_mutex_unlock(ph->a->to_check);
			return ;
		}
		pthread_mutex_unlock(ph->a->to_check);
	}
	pthread_mutex_unlock(ph->mutex);
}

void to_set(pthread_mutex_t *mtx, int *var, int val)
{
	pthread_mutex_lock(mtx);
	*var = val;
	pthread_mutex_unlock(mtx);
}

int to_check(pthread_mutex_t *mtx, int *var, int val)
{
	pthread_mutex_lock(mtx);
	if (*var == val)
		return (pthread_mutex_unlock(mtx), 0);
	pthread_mutex_unlock(mtx);
	return (1);
}

int	sub_check(t_list *ph)
{
	if (ph->a->num_of_ph == 1)
	{
		one_philo(ph);
		return (1);
	}
	while(!to_check(ph->a->to_check, &ph->fork, 1) && to_check(ph->a->to_check, &ph->next->fork, 0))
	{
		if (!to_check(ph->a->to_check, &ph->a->die, 0))
			return (1);
	}
	return (0);
}

void ft_eating(t_list *ph)
{
	while(!to_check(ph->a->to_check, &ph->fork, 1))
	{
		if (!to_check(ph->a->to_check, &ph->a->die, 0))
			return ;
	}
	pthread_mutex_lock(ph->mutex);
	to_set(ph->a->to_check, &ph->fork, 1);
	printf("%ld %d has taken a fork\n", (get_time() - ph->sta_sim) , ph->nb);
	if (sub_check(ph))
		return ;
	pthread_mutex_lock(ph->next->mutex);
	to_set(ph->a->to_check, &ph->next->fork, 1);
	printf("%ld %d has taken a fork\n", (get_time() - ph->sta_sim) , ph->nb);
	pthread_mutex_lock(ph->a->to_check);
	ph->sta_ea =  get_time();
	pthread_mutex_unlock(ph->a->to_check);
	printf("%ld %d is eating\n", (get_time() - ph->sta_sim) , ph->nb);
	pph_usleep(ph->a->tm_to_eat);
	pthread_mutex_unlock(ph->mutex);
	to_set(ph->a->to_check, &ph->fork, 0);
	pthread_mutex_unlock(ph->next->mutex);
	to_set(ph->a->to_check, &ph->next->fork, 0);
}