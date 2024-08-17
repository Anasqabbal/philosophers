/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:56:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/11 18:08:12 by anqabbal         ###   ########.fr       */
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
