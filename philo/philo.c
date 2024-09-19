/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:12:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/19 08:58:57 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor(void *p)
{
	t_list	*ph;

	ph = p;
	while (ph && to_check(&ph->a->to_count, &ph->count, 0))
	{
		if (get_time() - to_get(&ph->last_eat, ph, 0) > ph->a->tm_to_die)
		{
			to_set(&ph->a->to_check, &ph->a->die, 0);
			pthread_mutex_lock(&ph->a->to_print);
			printf("%ld %d died\n", get_time() - ph->sta_sim, ph->nb);
			pthread_mutex_unlock(&ph->a->to_print);
			return (p);
		}
		ph = ph->next;
	}
	return (p);
}

int	check_death(t_list *ph, void (*f)(t_list *))
{
	if (!to_check(&ph->a->to_check, &ph->a->die, 0))
		return (1);
	f(ph);
	return (0);
}

void	*ft_routine(void *t)
{
	t_list	*ph;
	int		i;

	i = -1;
	ph = t;
	if (ph->nb % 2 == 0)
		usleep(400);
	while (ph->count && to_check(&ph->a->to_check, &ph->a->die, 0))
	{
		if (check_death(ph, ft_eating))
			break ;
		if (check_death(ph, ft_sleeping))
			break ;
		if (check_death(ph, ft_thinking))
			break ;
		if (ph->a->ac == 6)
			to_set(&ph->a->to_count, &ph->count, ph->count - 1);
	}
	return (t);
}

static int	start_philo(char **av, int ac)
{
	t_args	a;
	t_list	*ph;
	int		i;

	ph = NULL;
	i = -1;
	if (initialize_struct_philo(&a, av, ac) < 0)
		return (-1);
	if (creat_list(&a, &ph) == -1)
		return (-1);
	if (creat_philosophers(hold_ptr(NULL, 1)) < 0)
		return (ph_lstclear(&ph, ph->a->num_of_ph), -1);
	ft_monitor(hold_ptr(NULL, 1));
	ph_wait(hold_ptr(NULL, 1));
	init_des_global_mutex(&a, 1);
	ph = hold_ptr(NULL, 1);
	while (++i < a.num_of_ph)
	{
		pthread_mutex_destroy(&ph->last_eat);
		ph = ph->next;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_list	*ph;

	if (ac < 5 || ac > 6)
		return (ph_putstr_fd("invalide arguments\n", 2), 1);
	if (check_arguments(av))
		return (1);
	if (start_philo(av, ac) < 0)
		return (1);
	ph = hold_ptr(NULL, 1);
	ph_lstclear(&ph, ph->a->num_of_ph);
	return (0);
}
