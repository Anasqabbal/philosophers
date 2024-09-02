/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:01:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/01 12:52:11 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_struct_philo(t_args *p, char **av, int ac)
{
	int ind;

	ind = 0;
	p->num_of_ph = ph_atoi(av[1], &ind);
	p->tm_to_die = ph_atoi(av[2], &ind);
	p->tm_to_eat = ph_atoi(av[3], &ind) * 1000;
	p->tm_to_sle = ph_atoi(av[4], &ind) * 1000;
	p->nb_of_mls = 0;
	p->die = 1;
	p->to_check = malloc(sizeof(pthread_mutex_t));
	if (!p->to_check)
		return ;
	if (ac == 6)
		p->nb_of_mls = ph_atoi(av[5], &ind);
	else
		p->nb_of_mls = ac;
	p->ac = ac;
}

int	check_arguments(char **av)
{
	int	i;
	int	ind;

	i = 0;
	ind = 0;
	while(av[++i])
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

int	creat_philosophers(t_list *ph)
{
	int	i;

	i = 0;
	size_t t = get_time();
	pthread_mutex_init(ph->a->to_check, NULL);
	while(ph && i < ph->a->num_of_ph)
	{
		pthread_mutex_init(ph->mutex, NULL);
		ph->sta_sim = t;
		ph->sta_ea = ph->sta_sim;
		if (pthread_create(&ph->id, NULL, test, ph))
			return (1);
		ph = ph->next;
		i++;
	}
	return (0);
}

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