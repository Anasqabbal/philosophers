/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:33:58 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/17 17:50:47 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*cur;

	if (!lst || !del)
		return ;
	cur = *lst;
	while (cur != NULL)
	{
		temp = cur;
		del(cur->content);
		cur = cur->next;
		free(temp);
	}
	*lst = NULL;
}
