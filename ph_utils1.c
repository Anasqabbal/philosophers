/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:29:03 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/08 11:55:14 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void one_philo(t_list *ph)
{
	while(1)
	{
		if (!to_check(ph->a->to_check, &ph->a->die, 0))
			break ;
	}
	pthread_mutex_unlock(ph->mutex);
}

void to_set(pthread_mutex_t *mtx, int *var, int val, char *f)
{
	(void)f;
	pthread_mutex_lock(mtx);
	*var = val;
	pthread_mutex_unlock(mtx);
}

int to_check(pthread_mutex_t *mtx, int *var, int val)
{
	pthread_mutex_lock(mtx);
	if (*var == val)
		return (pthread_mutex_unlock(mtx), 0);
	pthread_mutex_unlock(mtx);
	return (1);
}

int	sub_check(t_list *ph)
{
	if (ph->a->num_of_ph == 1)
	{
		one_philo(ph);
		return (1);
	}
	// while(!to_check(ph->a->to_check, &ph->fork, 1) && to_check(ph->a->to_check, &ph->next->fork, 0))
	// {
	// 	if (!to_check(ph->a->to_check, &ph->a->die, 0))
	// 		return (1);
	// }
	return (0);
}
void ft_printf(int ind, t_list *ph, char *s)
{
	(void) ind;
	if (!to_check(ph->a->to_check, &ph->a->die, 0))
		return ;
	pthread_mutex_lock(ph->a->to_print);
	printf("%ld %d %s\n", (get_time() - ph->sta_sim) , ph->nb, s);
	pthread_mutex_unlock(ph->a->to_print);
}

/*
typedef enum	e_stat{
	DIED,
	TOOK_A_FORK,
	EATING,
	THINKING,
	SLEEPING,
}	t_stat;
t_stat philo_status
ft_printf(DIED)
*/
void ft_eating(t_list *ph)
{
	while(!to_check(ph->a->to_check, &ph->fork, 1))
	{
		if (!to_check(ph->a->to_check, &ph->a->die, 0))
			return ;
	}
	pthread_mutex_lock(ph->mutex);
	to_set(ph->a->to_check, &ph->fork, 1, "ft_eating");
	if (!to_check(ph->a->to_check, &ph->a->die, 0))
	{
		// printf("from here 0\n");
		return ;
	}
	ft_printf(0, ph, "has taken a fork");
	if (sub_check(ph))
	{
		// printf("from here 1\n");
		return ;
	}
	pthread_mutex_lock(ph->next->mutex);
	to_set(ph->a->to_check, &ph->next->fork, 1, "ft_eating 2");
	if (!to_check(ph->a->to_check, &ph->a->die, 0))
	{
		// printf("from here 2\n");
		return ;
	}
	ft_printf(1, ph, "has taken a fork");
	pthread_mutex_lock(ph->a->to_check);
	ph->sta_ea =  get_time();
	pthread_mutex_unlock(ph->a->to_check);
	ft_printf(2, ph, "is eating");
	pph_usleep(ph->a->tm_to_eat);
	pthread_mutex_unlock(ph->mutex);
	to_set(ph->a->to_check, &ph->fork, 0, "ft_eating 3");
	pthread_mutex_unlock(ph->next->mutex);
	to_set(ph->a->to_check, &ph->next->fork, 0, "ft_eating 4");
}
