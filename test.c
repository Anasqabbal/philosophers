#include "philo.h"

void find_usleep(long time)
{
    struct timeval start, end;
    long res;
    long diff;

    diff = 0;
    gettimeofday(&start, NULL);
    printf("the time before  with seconds %ld\n", start.tv_sec * 1000000L + start.tv_usec);
    printf("the time with ms == %d\n", start.tv_usec);
    int i = 0;
    while(1)
    {
        gettimeofday(&end, NULL);
        diff = time - ((end.tv_sec * 1000000L + end.tv_usec) - (start.tv_sec * 1000000L + start.tv_usec));
        if (diff > 1000)
            usleep(500);
        else
            break;
    }
    gettimeofday(&end, NULL);
    printf("the time after %d\n", end.tv_usec);
    printf("the diff %d\n", end.tv_usec - start.tv_usec);
}

int main(int ac, char **av)
{
    long res;
    if (ac)
        res = atoi(av[1]) * 1000;
    find_usleep(res);
}