/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lstutils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:22:07 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/18 16:56:13 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp -> next)
		tmp = tmp -> next;
	tmp -> next = new;
}

void	ph_lstclear(t_list **lst, int len)
{
	t_list	*temp;
	t_list	*cur;
	int		i;

	i = 0;
	if (!lst)
		return ;
	cur = *lst;
	while (cur != NULL && i < len)
	{
		temp = cur;
		cur = cur->next;
		free(temp);
		i++;
	}
	*lst = NULL;
}
