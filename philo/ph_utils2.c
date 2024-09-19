/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:38:22 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/18 13:23:03 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thinking(t_list *ph)
{
	printf("%ld %d is thinking\n", get_time() - ph->sta_sim, ph->nb);
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

void	ft_sleeping(t_list *ph)
{
	ft_printf("is sleeping", NULL, NULL, ph);
	ph_usleep(ph->a->tm_to_sle, ph);
}
