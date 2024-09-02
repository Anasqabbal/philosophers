/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lstutils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:23:50 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/01 17:01:10 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_wait(t_list *p)
{
	int	i;

	i = -1;
	while (p && ++i < p->a->num_of_ph)
	{
		pthread_detach(p->id);
		p = p->next;
		if (p && i == p->a->num_of_ph)
			break ;
	}
	i = -1;
	p = hold_ptr(NULL, 1);
	while (++i < p->a->num_of_ph)
	{
		pthread_mutex_destroy(p->mutex);
		p = p->next;
	}
}

static long	get_subs_of_val(struct timeval start, struct timeval end)
{
	long	sec;
	long	usec;

	sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
	return ((sec * 1000000L) + usec);
}

void	pph_usleep(long usec)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;
	long			rem;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = get_subs_of_val(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
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
	arr->mutex = malloc(sizeof(pthread_mutex_t));
	if (!arr->mutex)
		return (NULL);
	return (arr);
}
