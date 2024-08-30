/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:01:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/30 16:51:57 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int creat_list(t_args *a, t_list **head)
{
    t_list *p;
    int     i;

    i = 0;
    while(++i <= a->num_of_ph)
    {
        p  = ph_lstnew(NULL);
        if (!p)
        {
            ph_lstclear(hold_ptr(NULL, 1), free);
            return (-1);
        }
        p->nb = i;
        p->a = a;
        p->die = 1;
        p->count = a->nb_of_mls;
        p->fork = 0;
        if (i == 1)
            hold_ptr(p, 0);
        ph_lstadd_back(head, p);
        if (i == a->num_of_ph)
            p->next = hold_ptr(NULL, 1);
    }
    return (0);
}