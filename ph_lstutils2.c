/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lstutils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:23:50 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/24 12:05:08 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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