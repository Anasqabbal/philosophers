/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:29:03 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/25 17:11:01 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*hold_ptr(void *pt, int get)
{
	static void	*head;

	if (get)
		return (head);
	else
		head = pt;
	return (0);
}

void	ft_sleeping(t_list *h)
{
	usleep(h->a->tm_to_sle);
	printf("%ld %d is sleeping\n", (get_time() - h->sta_sim) , h->nb);
}

void ft_eating(t_list *h)
{
	printf("you taken the fork at %ld\n", get_time() - h->sta_sim );
	printf("%ld %d has taken a fork\n", (get_time() - h->sta_sim) , h->nb);
	pthread_mutex_lock(h->mutex);
	pthread_mutex_lock(h->next->mutex);
	if (!h->next)
		h->next = hold_ptr(NULL, 1);
	h->sta_ea =  get_time();
	printf("%ld %d is eating\n", (get_time() - h->sta_sim) , h->nb);
	usleep(h->a->tm_to_eat);
	pthread_mutex_unlock(h->mutex);
	pthread_mutex_unlock(h->next->mutex);
	h->in_mutex = 0;
}

void    ft_thinking(t_list *h)
{
	if ((h->a->tm_to_die - h->a->tm_to_sle) > 0)
	{
		usleep(h->a->tm_to_die - h->a->tm_to_sle);
    	printf("%ld %d is thinking\n", (get_time() - h->sta_sim) , h->nb);
	}
}

void	ft_ready(t_list *h)
{
	printf("%ld %d has taken a fork\n", get_time() , h->nb);
}