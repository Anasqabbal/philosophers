/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_timeofday.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:03:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/11 17:03:51 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int cal_time(int old, int new)
{
    return (new - old);
}

long get_time()
{
    struct timeval v;
    if (gettimeofday(&v, NULL) == -1)
        return (perror("gettmieofday"), -1);
    return ((v.tv_sec * 1000) + v.tv_usec / 1000);
}