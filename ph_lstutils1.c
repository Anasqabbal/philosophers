/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lstutils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:22:07 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/14 15:36:03 by anqabbal         ###   ########.fr       */
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

void	ph_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ph_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	ph_lstclear(t_list **lst, void (*del)(void *), int len)
{
	t_list	*temp;
	t_list	*cur;
	int		i;

	i = 0;
	if (!lst || !del)
		return ;
	cur = *lst;
	while (cur != NULL && i < len)
	{
		del(cur->content);
		cur->content = NULL;
		temp = cur;
		cur = cur->next;
		free(temp);
		i++;
	}
	*lst = NULL;
}
