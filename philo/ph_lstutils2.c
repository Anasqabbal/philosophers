/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lstutils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:23:50 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/18 14:17:43 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_wait(t_list *ph)
{
	int	i;

	i = -1;
	while (ph && ++i < ph->a->num_of_ph)
	{
		if (pthread_join(ph->id, NULL))
			pthread_detach(ph->id);
		ph = ph->next;
		if (ph && i == ph->a->num_of_ph)
			break ;
	}
	i = -1;
	ph = hold_ptr(NULL, 1);
	while (++i < ph->a->num_of_ph)
	{
		pthread_mutex_destroy(&ph->mutex);
		ph = ph->next;
	}
}

void	ph_usleep(long usec, t_list *ph)
{
	long	str;

	str = get_time();
	usec /= 1000;
	while (get_time() - str < usec)
	{
		if (!to_check(&ph->a->to_check, &ph->a->die, 0))
			break ;
		usleep(500);
	}
}

int	ph_lstsize(t_list *lst)
{
	int		i;
	t_list	*cur;

	if (lst == NULL)
		return (0);
	cur = lst;
	i = 0;
	while (cur != NULL)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

t_list	*ph_lstnew(void *content)
{
	t_list	*arr;

	arr = malloc(sizeof(t_list));
	if (!arr)
		return (0);
	arr->content = content;
	arr->next = NULL;
	arr->a = NULL;
	return (arr);
}
