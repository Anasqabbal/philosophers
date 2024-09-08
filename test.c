#include "philo.h"

int init_general_info(char **av, t_args **in, int ac)
{
    t_args *info;
    int     ind;

    ind = 0;
    info = malloc(sizeof(t_args));
    if (!info)
        return (-1);
    info->to_check = malloc(sizeof(pthread_mutex_t));
    if (!info->to_check)
        return (-1);
    info->to_print = malloc(sizeof(pthread_mutex_t));
    if (!info->to_print)
        return (free(info->to_check), -1);
    info->die = 1;
    info->ac = ac;
    info->num_of_ph = ph_atoi(av[1], &ind);
    info->tm_to_die= ph_atoi(av[2], &ind);
    info->tm_to_eat= ph_atoi(av[3], &ind) * 1000;
    info->tm_to_sle= ph_atoi(av[4], &ind) * 1000;
    if (ac == 6)
    {
        info->nb_of_mls = ph_atoi(av[5], &ind);
        if (ind)
            return (free(info->to_check), free(info->to_print), free(info), -1);
    }
    else
        info->nb_of_mls = ac;
    *in = info;
    return (0);
}

void printf_general_info(t_args *info)
{
    if(info->to_check)
        printf("yoru to_check is not NULL\n");
    if(info->to_print)
        printf("yoru to_print is not NULL\n");
    printf ("the nb of philo is %d\n", info->num_of_ph);
    printf ("your time to die is %ld\n", info->tm_to_die);
    printf ("your time to eat is %ld\n", info->tm_to_eat);
    printf ("your time to sleep is %ld\n", info->tm_to_sle);
    if (info->ac == 6)
        printf ("the nmber of mls is %d\n", info->nb_of_mls); 
}

void print_list(t_list *head)
{
    int i = 0;
    while(i++ < head->a->num_of_ph)
    {
        printf("the nb of philos is %d\n", head->a->num_of_ph);
        head = head->next;
    }
}

int ph_creat_the_list(t_args *in, t_list **ph)
{
    t_list  *philo;
    int     i;

    i = 1;
    while (i <= in->num_of_ph)
    {
        philo = ph_lstnew(NULL);
        if (!philo)
            return (-1); /* clear list before return */
        philo->last_eat = malloc(sizeof(pthread_mutex_t));
        if (!philo->last_eat)
            return (-1);
        philo->nb = i;
        philo->a = in;
        philo->count = in->nb_of_mls;
        if (i == 1)
            hold_ptr(philo, 0);
        ph_lstadd_back(ph, philo);
        if (i == in->num_of_ph)
            philo->next = hold_ptr(NULL, 1);
        i++;
        printf("the value of i == %d\n", philo->nb);
    }
    return (0);
}

void ph_print(t_list *ph, int ind)
{
    if (ind == 0)
    {
        pthread_mutex_lock(ph->a->to_print);
        printf("%ld %d has taken a fork\n", get_time() - ph->sta_sim, ph->nb);
        pthread_mutex_lock(ph->a->to_print);
    }
}

int ph_eating(t_list *ph)
{
    pthread_mutex_lock(&ph->mutex);
    ph_print(ph, 0);
    pthread_mutex_unlock(&ph->mutex);
    return (0);
}

void *routine(void *r)
{
    t_list *ph;

    ph = r;
    while(ph->a->die && ph->count)
    {
        printf("eating\n");
        printf("sleeping\n");
        printf("thinking\n");
        sleep (1);
    }
    return (r);
}

void ph_monitor(t_list *p)
{
    (void)p;
    return ;
}

void ph_join(t_list *p)
{
    int i;

    i = -1;
    (void) p;
    while (++i < p->a->num_of_ph)
    {
        pthread_detach(p->id);
        p = p->next;
    }
    return ;
}

int ph_creat_philos(t_list *ph)
{
    int i;
    long long t;

    i = 0;
    t = get_time();
    printf("the value of address == %p its next %p\n", ph, ph->next);
    pthread_mutex_init(ph->a->to_print, NULL);
    pthread_mutex_init(ph->a->to_check, NULL);
    while (i < ph->a->num_of_ph)
    {
        pthread_mutex_init(&ph->mutex, NULL);
        if (pthread_create(&ph->id, NULL, routine, ph))
            return (-1);
        ph->sta_sim = t;
        ph->sta_ea = t;
        ph = ph->next;
        i++;
        if (i == ph->a->num_of_ph)
            break ;
    }
    ph_monitor(hold_ptr(NULL, 1));
    ph_join(hold_ptr(NULL, 1));
    return (0);
}

int ft_start_philo(int ac, char **av)
{
    t_args *info;
    t_list *philo;

    info = NULL;
    philo = NULL;
    if (init_general_info(av, &info, ac) < 0)
        return (1);
    if (ph_creat_the_list(info, &philo))
        return (1);
    // printf_general_info(info);
    print_list(hold_ptr(NULL, 1));
    if (ph_creat_philos(hold_ptr(NULL, 1)))
        return (1);
    return (0);
}


int main(int ac, char **av)
{
    if (ac < 5 || ac > 6)
        printf("number of args is invalid\n");
    if (check_arguments(av))
        return (1);
    if (ft_start_philo(ac, av))
        return (1);
}