/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:12:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/25 16:57:16 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_wait(t_list *p)
{
	pthread_t t;
	while(p)
	{
		pthread_mutex_destroy(p->mutex);
		t = (p->id);
		pthread_join(t, NULL);
		p = p->next;
	}
}

void *routine(void *p)
{
	t_list *ph;
	int		i;
	
	ph = p;
	i = 1;
	ph->sta_sim = get_time();
	usleep (250000);
	if (!(ph->nb % 2))
		usleep (250000); 
	while(1)
	{
		ft_eating(ph);
		ft_sleeping(ph);
		ft_thinking(ph);
		if (get_time() - ph->sta_ea >= ph->a->tm_to_die)
		{
			printf("the philo %d is died\n", ph->nb);
			exit(0);
		}
		sleep(1);
	}
	return (p);
}

void *execute_this(void *p)
{
	// t_list *ph;

	// ph = p;
	// if (!ph->next)
	// 	ph->next = hold_ptr(NULL, 1);
	// while(ph)
	// {
	// 	if (!ph->next)
	// 		ph->next = hold_ptr(NULL, 1);
	// 	ph = ph->next;
	// }
	// printf("the philo number %d\n", ph->nb);
	// sleep(10);
	// pthread_mutex_unlock(ph->mutex);
	return (p);
}

int	creat_philosophers(t_list *ph)
{
	int	i;

	i = 0;
	while (ph)
	{
		pthread_mutex_init(ph->mutex, NULL);
		if (pthread_create(&ph->id, NULL, routine, ph))
			return (printf("pthread_creat failed\n"), 1);
		ph = ph->next;
	}
	ph_wait(hold_ptr(NULL, 1));
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
	if (ac  == 6)
		p->nb_of_mls = ph_atoi(av[4], &ind);
	p->ac = ac;
}

static int	start_philo(char **av, int ac)
{
	t_args a;
	t_list *ph;

	ph = NULL;
	initialize_struct_philo(&a, av, ac);
	creat_list(&a, &ph);
	creat_philosophers(hold_ptr(NULL, 1));
	
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