/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:36:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/11 18:08:41 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*ph_lstlast(t_list *lst)
{
	int		res;
	int		i;
	t_list	*cur;

	if (lst == NULL)
		return (0);
	cur = lst;
	res = ph_lstsize(cur);
	i = 0;
	while (i < res - 1 && cur != NULL)
	{
		cur = cur->next;
		i++;
	}
	return (cur);
}
