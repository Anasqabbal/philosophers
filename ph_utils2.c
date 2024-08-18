/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:05:36 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/18 10:19:11 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ph_mutext_destroy(t_list *p)
{
    while(p)
    {
        pthread_mutex_destroy(&p->mutex);
        p = p->next;
    }
    return (0);
}