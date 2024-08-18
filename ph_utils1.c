/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:29:03 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/18 21:22:40 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleeping(t_list *h)
{
	usleep(h->a->tm_to_sle);
	printf("%d %d is sleeping\n", get_time() , h->nb);
}

void ft_eating(t_list *h)
{
	
	printf("%d %d has taken a fork\n", get_time() , h->nb);
	if (h->next)
	{
		pthread_mutex_lock(&h->mutex);
		h->in_mutex = 1;
		if (h->next->in_mutex)
		{
			h->sta_ea =  get_time() ;
			printf("%d %d is eating\n", h->sta_ea, h->nb);
			usleep(h->a->tm_to_eat);
		}
		pthread_mutex_unlock(&h->mutex);
		h->in_mutex = 0;
	}
}

void    ft_thinking(t_list *h)
{
	usleep(h->a->tm_to_eat);
    printf("%d %d is thinking\n", get_time() , h->nb);
}

void	ft_ready(t_list *h)
{
	printf("%d %d has taken a fork\n", get_time() , h->nb);
}