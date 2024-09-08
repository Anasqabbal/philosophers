/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyses.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:01:55 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/03 16:22:40 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdio.h>

void free2d(char **res)
{
    int i = -1;
    if (res)
    {
        printf("hna\n");
        while (res[++i])
            free(res[i]);
        free(res);
    }
}

void print2d(char **res)
{
    int i = -1;
    while (res[++i])
        printf(" the value of res == %s\n", res[i]);
}
void to_free(char ***res, int  f_len)
{
    int i = -1;
    if (f_len == 0)
        return ;
    printf("the value of f_len == %d\n", f_len);
    while (++i < f_len)
    {
        printf("before free the value of i == %d\n your res is \n\n", i);
        print2d(*(res + i));
        free2d(*(res + i));
    }
    free(res);
}

int file_len()
{
    char *res;
    int i = 0;
    int fd = open("out_file2", O_RDONLY);
    if (fd < 0)
        return (perror("error") ,1);
    while (1)
    {
        res = get_next_line(fd);
        if (!res)
            break ;
        free(res);
        i++;
    }
    close(fd);
    return (i);
}


void f()
{
    system("leaks outfd");
}

int main()
{
    atexit(f);
    int f_len;
    int fd;
    char *re;
    char ***res;
    char *tmp;
    int i;
    
    f_len = file_len();
    res = malloc(sizeof(char **) * f_len);
    if (!res)
        return (perror("malloc"), 1);
    fd = open("out_file2", O_RDONLY);
    if (fd < 0)
        return (perror("open"), 1);
    i = 0;
    while(i < f_len)
    {
        re = get_next_line(fd);
        if (!re)
            break;
        tmp = re;
        res[i] = ft_split(re, ' ');
        if (!res[i] && i != f_len - 1)
            to_free(res, f_len);
        free(tmp);
        print2d(res[i]);   
    }
    printf("AT TEH END\n");
    to_free(res, f_len);
}