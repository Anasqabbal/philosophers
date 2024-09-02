/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:38:22 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/01 12:58:08 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_thinking(t_list *h)
{
	long	res;

	res = h->a->tm_to_die - (h->a->tm_to_sle / 1000 + h->a->tm_to_eat / 1000);
	if (res > 0)
    	printf("%ld %d is thinking\n", (get_time() - h->sta_sim) , h->nb);
}

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
	printf("%ld %d is sleeping\n", (get_time() - h->sta_sim) , h->nb);
	pph_usleep(h->a->tm_to_sle);
}
