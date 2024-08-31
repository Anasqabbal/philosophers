/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:12:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/31 18:11:57 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_thinking(t_list *h)
{
	long	res;

	res = h->a->tm_to_die - (h->a->tm_to_sle / 1000 + h->a->tm_to_eat / 1000);
	if (res > 0)
    	printf("%ld %d is thinking\n", (get_time() - h->sta_sim) , h->nb);
}

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
	pph_usleep(h->a->tm_to_sle);
}

void *ft_monitor(void *p)
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

void	ph_wait(t_list *p)
{
	int	i;

	i = -1;
	while(p && ++i < p->a->num_of_ph)
	{
		pthread_join(p->id , NULL);
		p = p->next;
		if (p && i == p->a->num_of_ph)
			break ;
	}
	i = -1;
	p = hold_ptr(NULL, 1);
	while (++i < p->a->num_of_ph)
	{
		pthread_mutex_destroy(p->mutex);
		p = p->next;
	}
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

// int	check_arguments(char **av)
// {
// 	int	i;
// 	int	ind;

// 	i = 0;
// 	ind = 0;
// 	while(av[++i])
// 	{
// 		if (av[i][0] == '\0')
// 		{
// 			ind++;
// 			ph_error(av[i]);
// 			break ;
// 		}
// 		ph_atoi(av[i], &ind);
// 		if (ind == 1)
// 		{
// 			ph_error(av[i]);
// 			break ;
// 		}
// 	}
// 	if (ind)
// 		return (1);
// 	return (0);
// }

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
		pthread_mutex_lock(ph->a->to_check);
		if (!ph->a->die)
		{
			pthread_mutex_unlock(ph->a->to_check);
			break ;
		}
		if (ph->a->ac == 6)
			ph->count--;
		pthread_mutex_unlock(ph->a->to_check);
	}
	return (t);
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