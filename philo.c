/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:12:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/01 17:12:20 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor(void *p)
{
	t_list *ph;

	ph = p;
	while(ph)
	{
		pthread_mutex_lock(ph->a->to_check);
		if (!ph->count)
		{
			pthread_mutex_unlock(ph->a->to_check);
			break ;
		}
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

int check_death(t_list *ph, t_args *a,void (*f)(t_list *))
{
	(void) a;
	pthread_mutex_lock(a->to_check);
	if (ph->a->die == 0)
		return (pthread_mutex_unlock(ph->a->to_check), 0);
	pthread_mutex_unlock(a->to_check);
	f(ph);
	return (0);
}
void *test(void *t)
{
	
	t_list *ph;
	int		i;

	i = -1;
	ph = t;
	if (ph->nb % 2 == 0)
		usleep(400);
	while(ph->count)
	{
		if (check_death(ph, ph->a, ft_eating))
			break ;
		if (check_death(ph, ph->a, ft_sleeping))
			break ;
		if (check_death(ph, ph->a, ft_thinking))
			break ;
		if (!to_check(ph->a->to_check, &ph->a->die, 0))
			break ;
		if (ph->a->ac == 6)
			to_set(ph->a->to_check, &ph->count, ph->count - 1);
	}
	return (t);
}

static int	start_philo(char **av, int ac)
{
	t_args a;
	t_list *ph;

	ph = NULL;
	initialize_struct_philo(&a, av, ac);
	if (creat_list(&a, &ph) == -1)
		return (-1);
	creat_philosophers(hold_ptr(NULL, 1));
	ft_monitor(hold_ptr(NULL, 1));
	ph_wait(hold_ptr(NULL, 1));
	pthread_mutex_destroy(ph->a->to_check);
	return (0);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	if (ac < 5)
		return (ph_putstr_fd("invalide arguments\n", 2), 1);
	if (check_arguments(av))
		return (1);
	start_philo(av, ac);
}