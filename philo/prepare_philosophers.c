/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:01:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/19 08:34:00 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_struct_philo(t_args *p, char **av, int ac)
{
	int	ind;

	ind = 0;
	p->num_of_ph = ph_atoi(av[1], &ind);
	if (p->num_of_ph > 2147483647 || p->num_of_ph <= 0)
	{
		ph_putstr_fd("number of philos is not valid\n", 2);
		return (-1);
	}
	p->tm_to_die = ph_atoi(av[2], &ind);
	p->tm_to_eat = ph_atoi(av[3], &ind) * 1000;
	p->tm_to_sle = ph_atoi(av[4], &ind) * 1000;
	p->nb_of_mls = 0;
	p->die = 1;
	if (ac == 6)
		p->nb_of_mls = ph_atoi(av[5], &ind);
	else
		p->nb_of_mls = ac;
	p->ac = ac;
	return (0);
}

int	check_arguments(char **av)
{
	int	i;
	int	ind;

	i = 0;
	ind = 0;
	while (av[++i])
	{
		if (av[i][0] == '\0')
		{
			ind++;
			ph_error(av[i]);
			break ;
		}
		ph_atoi(av[i], &ind);
		if (ind == 1)
		{
			ph_error(av[i]);
			break ;
		}
	}
	if (ind)
		return (1);
	return (0);
}

void	destroy_local_mutex(t_list *ph, int len, int ind, int origine_len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (ind == 1 || ind == 2)
			pthread_mutex_destroy(&ph->last_eat);
		if (ind == 2)
			pthread_mutex_destroy(&ph->mutex);
		ph = ph->next;
	}
	if (len != origine_len && ind == 2)
	{
		while (i < origine_len)
		{
			pthread_mutex_destroy(&ph->last_eat);
			i++;
		}
	}
}

int	creat_philosophers(t_list *ph)
{
	int		i;
	size_t	t;

	i = 0;
	if (init_des_global_mutex(ph->a, 0) < 0)
		return (-1);
	t = get_time();
	if (init_local_mutex(ph, 1) < 0)
		return (-1);
	if (init_local_mutex(ph, 2) < 0)
		return (-1);
	while (ph && i < ph->a->num_of_ph)
	{
		ph->sta_sim = t;
		ph->sta_ea = ph->sta_sim;
		if (pthread_create(&ph->id, NULL, ft_routine, ph))
			return (-1);
		ph = ph->next;
		i++;
	}
	return (0);
}

int	creat_list(t_args *a, t_list **head)
{
	t_list	*p;
	int		i;

	i = 0;
	while (++i <= a->num_of_ph)
	{
		p = ph_lstnew(NULL);
		if (!p)
		{
			ph_lstclear(hold_ptr(NULL, 1), i);
			return (-1);
		}
		p->nb = i;
		p->a = a;
		p->count = a->nb_of_mls;
		if (i == 1)
			hold_ptr(p, 0);
		ph_lstadd_back(head, p);
		if (i == a->num_of_ph)
			p->next = hold_ptr(NULL, 1);
	}
	return (0);
}
