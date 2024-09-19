/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:29:03 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/18 16:57:17 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_local_mutex(t_list *ph, int ind)
{
	int	i;

	i = -1;
	while (++i < ph->a->num_of_ph)
	{
		if (ind == 1)
		{
			if (pthread_mutex_init(&ph->last_eat, NULL))
				return (destroy_local_mutex(hold_ptr(NULL, 1)
						, i, 1, ph->a->num_of_ph), -1);
		}
		if (ind == 2)
			if (pthread_mutex_init(&ph->mutex, NULL))
				return (destroy_local_mutex(hold_ptr(NULL, 1)
						, i, 2, ph->a->num_of_ph), -1);
		ph = ph->next;
	}
	return (0);
}

static void	one_philo(t_list *ph)
{
	while (to_check(&ph->a->to_check, &ph->a->die, 0))
		;
	pthread_mutex_unlock(&ph->mutex);
}

int	ft_printf(char *s, pthread_mutex_t *mtx1, pthread_mutex_t *mtx2, t_list *ph)
{
	pthread_mutex_lock(&ph->a->to_print);
	if (!to_check(&ph->a->to_check, &ph->a->die, 0))
	{
		pthread_mutex_unlock(&ph->a->to_print);
		if (mtx1)
			pthread_mutex_unlock(mtx1);
		if (mtx2)
			pthread_mutex_unlock(mtx2);
		return (1);
	}
	printf("%ld %d %s\n", (get_time() - ph->sta_sim), ph->nb, s);
	pthread_mutex_unlock(&ph->a->to_print);
	return (0);
}

int	init_des_global_mutex(t_args *a, int ind)
{
	if (pthread_mutex_init(&a->to_check, NULL) && ind == 0)
		return (-1);
	if (pthread_mutex_init(&a->to_print, NULL) && ind == 0)
	{
		pthread_mutex_destroy(&a->to_check);
		return (-1);
	}
	if (pthread_mutex_init(&a->to_count, NULL) && ind == 0)
	{
		pthread_mutex_destroy(&a->to_check);
		pthread_mutex_destroy(&a->to_print);
		return (-1);
	}
	if (ind == 1)
	{
		pthread_mutex_destroy(&a->to_check);
		pthread_mutex_destroy(&a->to_print);
		pthread_mutex_destroy(&a->to_count);
	}
	return (0);
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
