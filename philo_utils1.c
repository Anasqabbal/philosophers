/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:29:03 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/17 18:06:21 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleeping(t_list *h)
{
	usleep(h->a->tm_to_eat);
	printf("%d %d is sleeping\n", get_time() * 1, h->nb);
}

void ft_eating(t_list *h)
{
	printf("%d %d is eating\n", get_time() * 1, h->nb);
	usleep(h->a->tm_to_eat);
}

void	ft_ready(t_list *h)
{
	h->cu_time = get_time() * 1;
	printf("%d %d has taken a fork\n", h->cu_time, h->nb);
}

void    ft_thinking(t_list *h)
{
    printf("%d %d is thinking\n", h->wait, h->nb);
}