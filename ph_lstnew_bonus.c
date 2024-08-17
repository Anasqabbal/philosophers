/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:28:26 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/12 15:01:01 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
