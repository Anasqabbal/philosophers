/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:12:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/18 21:21:49 by anqabbal         ###   ########.fr       */
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

// void	check_forks(t_list *h)
// {
// 	t_list *head;

// 	(void) h;
// 	head = hold_ptr(NULL, 1);
// 	while (head)
// 	{
// 		if (head->next)
// 		{
// 			if (!head->mutex)
// 				printf("available fork");
// 		}
// 		head = head->next;
// 	}
// }

// int	ph_lock_mutex(t_list *cur, t_list *next)
// {
	
// }

int	another_routine(t_list *h, int x)
{

	if (h->nb % 2 == x)
		ft_eating(h);
	else
		ft_sleeping(h);
	return (0);
}

void	*start_eating(void *pt)
{
	t_list *h;
	static int i;
	int	res;

	h = pt;
	if (h->nb % 2 == 0)
		usleep(100);
	pthread_mutex_init(&h->mutex, NULL);
	if (h->a->num_of_ph == 1)
	{
		printf("here\n");
		while(h->a->nb_of_mls)
		{
			another_routine(h, 1);
			res = cal_time(h->sta_ea, get_time() );
			if (res >= h->a->tm_to_die)
			{
				printf("%d %d died\n", get_time() , h->nb);
				exit (1);
			}
			printf("%d\n", i++);
			if (h->a->ac == 6)
				h->a->nb_of_mls--;
		}
	}
	else
	{
		while(h->a->nb_of_mls)
		{
			another_routine(h, 1);
			another_routine(h, 0);
			res = cal_time(h->sta_ea, get_time() );
			if (res >= h->a->tm_to_die)
			{
				printf("%d %d died\n", get_time() , h->nb);
				exit (1);
			}
			i++;
			if (h->a->ac == 6)
				h->a->nb_of_mls--;
		}
	}
	pthread_mutex_destroy(&h->mutex);
	return (0);
}

void	ph_wait(t_list *p)
{
	pthread_t t;
	while(p)
	{
		t = (p->id);
		pthread_join(t, NULL);
		p = p->next;
	}
}

int	creat_philosophers(t_args *a)
{
	int	i;
	t_list *p;
	t_list *head;

	i = 1;
	head = NULL;
	while (i)
	{
		if (i <= a->num_of_ph)
		{
			p = ph_lstnew(NULL);
			if (!p)
				return (ph_lstclear(hold_ptr(NULL, 1), free), 1);
			p->a = a;
			if (i == 1)
				hold_ptr(p, 0);
			p->nb = i;
			ph_lstadd_back(&head, p);
			if (pthread_create(&(p->id), NULL, start_eating, p))
				return (ph_lstclear(hold_ptr(NULL, 1), free), 1);
			i++;
		}
		// if (i  - 1 == a->num_of_ph)
		// 	break ;
	}
	return (0);
}

void	initialize_struct_philo(t_args *p, char **av, int ac)
{
	int ind;

	ind = 0;
	p->num_of_ph = ph_atoi(av[1], &ind);
	p->tm_to_die = ph_atoi(av[2], &ind);
	p->tm_to_eat = ph_atoi(av[3], &ind);
	p->tm_to_sle = ph_atoi(av[4], &ind);
	p->nb_of_mls = 0;
	if (ac  == 6)
		p->nb_of_mls = ph_atoi(av[4], &ind);
	p->ac = ac;
}

static int	start_philo(char **av, int ac)
{
	t_args a;

	initialize_struct_philo(&a, av, ac);
	creat_philosophers(&a);
	
	return (0);
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

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	if (ac < 5)
		return (ph_putstr_fd("invalide arguments\n", 2), 1);
	if (check_arguments(av))
		return (1);
	if (start_philo(av, ac))
		return (1);
}