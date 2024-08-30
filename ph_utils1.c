/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:29:03 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/30 18:09:43 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*hold_ptr(void *pt, int get)
{
	static void	*head;

	if (get)
		return (head);
	else
		head = pt;
	return (0);
}

void	ft_sleeping(t_list *h)
{
	printf("%ld %d is sleeping\n", (get_time() - h->sta_sim) , h->nb);
	ph_usleep(h->a->tm_to_sle);
}

void *ft_monitor(void *p)
{
	t_list *ph;

	ph = p;
	while(ph && ph->count)
	{
		pthread_mutex_lock(ph->a->to_check);
		if (get_time() - ph->sta_ea > ph->a->tm_to_die)
		{
			pthread_mutex_unlock(ph->a->to_check);
			printf("%ld %d is died\n", get_time() - ph->sta_sim, ph->nb);
			pthread_mutex_lock(ph->a->to_check);
			ph->a->die = 0;
			pthread_mutex_unlock(ph->a->to_check);
			return (p);
		}
		pthread_mutex_unlock(ph->a->to_check);
		ph = ph->next;
	}
	return (p);
}

void    ph_usleep(long  time)
{   
	struct timeval start;
	struct timeval end;
    long diff;

    diff = 0;
    gettimeofday(&start, NULL);
    while(1)
    {
        gettimeofday(&end, NULL);
        diff = time - ((end.tv_sec * 1000000L + end.tv_usec) - (start.tv_sec * 1000000L + start.tv_usec));
        if (diff > 1000)
            usleep(diff / 2);
        else
		{
			usleep(diff - 50);
            break;
		}
    }
    gettimeofday(&end, NULL);
}

void one_philo(t_list *ph)
{
	while(1)
	{
		pthread_mutex_lock(ph->a->to_check);
		if (!ph->a->die)
		{
			pthread_mutex_unlock(ph->a->to_check);
			return ;
		}
		pthread_mutex_unlock(ph->a->to_check);
	}
	pthread_mutex_unlock(ph->mutex);
}


void ft_eating(t_list *ph)
{
	pthread_mutex_lock(ph->mutex);
	printf("%ld %d has taken a fork\n", (get_time() - ph->sta_sim) , ph->nb);
	if (ph->a->num_of_ph == 1)
	{
		one_philo(ph);
		return ;
	}
	pthread_mutex_lock(ph->next->mutex);
	printf("%ld %d has taken a fork\n", (get_time() - ph->sta_sim) , ph->nb);
	pthread_mutex_lock(ph->a->to_check);
	ph->sta_ea =  get_time();
	pthread_mutex_unlock(ph->a->to_check);
	printf("%ld %d is eating\n", (get_time() - ph->sta_sim) , ph->nb);
	ph_usleep(ph->a->tm_to_eat);
	pthread_mutex_unlock(ph->mutex);
	pthread_mutex_unlock(ph->next->mutex);
}

void    ft_thinking(t_list *h)
{
	long	res;

	res = h->a->tm_to_die - (h->a->tm_to_sle / 1000 + h->a->tm_to_eat / 1000);
	if (res > 0)
    	printf("%ld %d is thinking\n", (get_time() - h->sta_sim) , h->nb);
}

void	ft_ready(t_list *h)
{
	printf("%ld %d has taken a fork\n", get_time() , h->nb);
}