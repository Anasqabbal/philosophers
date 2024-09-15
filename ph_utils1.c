/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:29:03 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/15 17:03:18 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_list *ph)
{
	while (to_check(&ph->a->to_check, &ph->a->die, 0))
		;
	pthread_mutex_unlock(&ph->mutex);
}

void	to_set_pro(pthread_mutex_t *mtx, long *var, long val)
{
	pthread_mutex_lock(mtx);
	*var = val;
	pthread_mutex_unlock(mtx);
}

int	sub_check(t_list *ph)
{
	if (ph->a->num_of_ph == 1)
	{
		one_philo(ph);
		return (1);
	}
	return (0);
}

int	ft_printf(char *s, pthread_mutex_t *mtx1, pthread_mutex_t *mtx2, t_list *ph)
{
	if (!to_check(&ph->a->to_check, &ph->a->die, 0))
	{
		if (mtx1)
			pthread_mutex_unlock(mtx1);
		if (mtx2)
			pthread_mutex_unlock(mtx2);
		return (1);
	}
	printf("%ld %d %s\n", (get_time() - ph->sta_sim), ph->nb, s);
	return (0);
}

long	*to_get_address(pthread_mutex_t *mtx, t_list *ph, int ind)
{
	long	*addr;

	addr = NULL;
	pthread_mutex_lock(mtx);
	if (ind == 0)
		addr = &ph->sta_ea;
	pthread_mutex_unlock(mtx);
	return (addr);
}

void	ft_eating(t_list *ph)
{
	pthread_mutex_lock(&ph->mutex);
    ft_printf("has taken a fork", &ph->mutex, NULL, ph);
	if (ph->a->num_of_ph == 1)
	{
		one_philo(ph);
		return ;
    }
	pthread_mutex_lock(&ph->next->mutex);
    ft_printf("has taken a fork", &ph->mutex, &ph->next->mutex, ph);
	pthread_mutex_lock(&ph->last_eat);
	ph->sta_ea = get_time();
	pthread_mutex_unlock(&ph->last_eat);
    ft_printf("is eating", &ph->mutex, &ph->next->mutex, ph);
	ph_usleep(ph->a->tm_to_eat, ph);
	pthread_mutex_unlock(&ph->mutex);
	pthread_mutex_unlock(&ph->next->mutex);
}
