/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:01:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/25 17:14:33 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void creat_list(t_args *a, t_list **head)
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
            exit (1);
        }
        p->nb = i;
        p->a = a;
        if (i == 1)
            hold_ptr(p, 0);
        ph_lstadd_back(head, p);
        if (i == a->num_of_ph)
            p->next = hold_ptr(NULL, 1);
    }
    // while(*head)
    //     *head = (*head)->next;
    // *head = hold_ptr(NULL, 1);
    // p = hold_ptr(NULL, 1);
}