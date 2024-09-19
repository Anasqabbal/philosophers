/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:15:02 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/19 08:17:19 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

typedef struct s_args
{
	pthread_mutex_t	to_check;
	pthread_mutex_t	to_print;
	pthread_mutex_t	to_count;
	long long		num_of_ph;
	long long		tm_to_eat;
	long long		tm_to_sle;
	long long		tm_to_die;
	int				nb_of_mls;
	int				ac;
	int				die;
}	t_args;

typedef struct s_list
{
	pthread_mutex_t	last_eat;
	pthread_mutex_t	mutex;
	void			*content;
	t_args			*a;
	pthread_t		id;
	int				nb;
	int				count;
	long			sta_ea;
	long			sta_sim;
	struct s_list	*next;
}	t_list;

long		to_get(pthread_mutex_t *mtx, t_list *ph, int ind);
void		*hold_ptr(void *pt, int get);
long long	ph_atoi(const char *str, int *ind);
void		ph_putstr_fd(char *s, int fd);
void		ph_error(char *str);
void		ph_lstadd_back(t_list **lst, t_list *new);
void		ph_lstclear(t_list **lst, int len);
t_list		*ph_lstnew(void *content);
int			ph_lstsize(t_list *lst);
long		get_time(void);
void		ft_sleeping(t_list *ph);
void		ft_eating(t_list *ph);
void		ft_thinking(t_list *ph);
int			ft_printf(char *s, pthread_mutex_t *mtx1,
				pthread_mutex_t *mtx2, t_list *ph);
int			creat_list(t_args *a, t_list **head);
void		*ft_monitor(void *p);
void		ph_usleep(long usec, t_list *ph);
void		ft_usleep(long long tt_sleep);
int			initialize_struct_philo(t_args *p, char **av, int ac);
int			creat_philosophers(t_list *ph);
int			check_arguments(char **av);
void		*ft_routine(void *t);
void		ph_wait(t_list *p);
void		to_set(pthread_mutex_t *mtx, int *var, int val);
int			to_check(pthread_mutex_t *mtx, int *var, int val);
int			init_des_global_mutex(t_args *a, int ind);
int			init_local_mutex(t_list *ph, int ind);
void		destroy_local_mutex(t_list *ph, int len, int ind, int origine_len);
#endif