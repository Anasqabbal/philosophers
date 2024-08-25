/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:15:02 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/25 17:10:11 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef pthread_mutex_t pth_m_t;

typedef struct s_args
{
    int num_of_ph;
    long tm_to_eat;
    long tm_to_sle;
    long tm_to_die;
    int nb_of_mls;
    int ac;
}   t_args;

typedef struct s_list
{
    void            *content;
    pthread_mutex_t *mutex;
    pthread_mutex_t *pre_ra;
    t_args          *a;
    pthread_t       id;
    int             in_mutex;
    int             nb;
    long             sta_ea;
    int             wait;
    int             count;
    long             sta_sim;
    int             ind;
    struct s_list   *next;
} t_list;



void	*hold_ptr(void *pt, int get);
int     ph_atoi(const char *str, int *ind);
void    ph_putstr_fd(char *s, int fd);
void    ph_error(char *str);
void    ph_lstadd_back(t_list **lst, t_list *new);
void    ph_lstadd_front(t_list **lst, t_list *new);
void    ph_lstclear(t_list **lst, void (*del)(void *));
void    ph_lstdelone(t_list *lst, void (*del)(void *));
void    ph_lstiter(t_list *lst, void (*f)(void *));
t_list  *ph_lstlast(t_list *lst);
t_list  *ph_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list  *ph_lstnew(void *content);
int     ph_lstsize(t_list *lst);
long    get_time();
int     cal_time(int old, int new);
void	ft_sleeping(t_list *h);
void    ft_eating(t_list *h);
void	ft_ready(t_list *h);
void    ft_thinking(t_list *h);
void creat_list(t_args *a, t_list **head);

#endif