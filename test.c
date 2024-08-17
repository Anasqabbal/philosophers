#include "philo.h"

int start_test(char **av)
{
    t_args ph;
    int ind;

    (void)av;
    ind = 0;
    printf("I m here\n");
    ph.num_of_ph = ph_atoi(av[1], &ind);
    if (ind)
        return (printf("invalid argument in the number of threads\n"), -1);
    ph.tm_to_die = ph_atoi(av[2], &ind);
    if (ind)
        return (printf("invalid argument in the time of the day argument\n"), -1);
    ph.tm_to_eat = ph_atoi(av[3], &ind);
    if (ind)
        return (printf("invalid argument in the time to eat argumetn\n"), -1);
    ph.tm_to_sle = ph_atoi(av[4], &ind);
    if (ind)
        return (printf("invalid argument in time to sleep argumetn\n"), -1);

    printf("numbers of philosophers  == %d\n", ph.num_of_ph);
    printf("time to die  == %d\n", ph.tm_to_die);
    printf("time to eat  == %d\n", ph.tm_to_eat);
    printf("time to sleep  == %d\n", ph.tm_to_sle);
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 1)
        return (printf("entrer a valid arguments\n"), 1);
    else
    {
        if (start_test(av) == -1)
            return (printf("error\n"), 1);
    }
}