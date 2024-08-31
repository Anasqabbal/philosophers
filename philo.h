/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:15:02 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/31 17:59:58 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h> /* for the function strerror()*/

typedef pthread_mutex_t pth_m_t;

typedef struct s_args
{
    pthread_mutex_t *to_check;
    int     num_of_ph;
    long    tm_to_eat;
    long    tm_to_sle;
    long    tm_to_die;
    int     nb_of_mls;
    int     ac;
    int     die;
}   t_args;

typedef struct s_list
{
    void            *content;
    pthread_mutex_t *mutex;
    pthread_mutex_t *pre_ra;
    t_args          *a;
    pthread_t       id;
    int             fork;
    int             nb;
    int             count;
    long            sta_ea;
    int             die;
    long            sta_sim;
    struct s_list   *next;
} t_list;

typedef struct s_exec
{
    t_list *ph;
    pthread_mutex_t mtx;
}t_exec ;

void	*hold_ptr(void *pt, int get);
int     ph_atoi(const char *str, int *ind);
void    ph_putstr_fd(char *s, int fd);
void    ph_error(char *str);
void    ph_lstadd_back(t_list **lst, t_list *new);
void    ph_lstadd_front(t_list **lst, t_list *new);
void    ph_lstclear(t_list **lst, void (*del)(void *));
void    ph_lstdelone(t_list *lst, void (*del)(void *));
t_list  *ph_lstlast(t_list *lst);
t_list  *ph_lstnew(void *content);
int     ph_lstsize(t_list *lst);
long    get_time();
int     cal_time(int old, int new);
void	ft_sleeping(t_list *h);
void    ft_eating(t_list *ph);
void    ft_thinking(t_list *h);
int     creat_list(t_args *a, t_list **head);
void    *ft_monitor(void *p);
void    pph_usleep(long usec) ;
void	initialize_struct_philo(t_args *p, char **av, int ac);
int     creat_philosophers(t_list *ph);
int     check_arguments(char **av);
void    *test(void *t);

#endif