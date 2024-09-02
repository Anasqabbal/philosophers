/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:26:54 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/06 14:26:54 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	v;

	if (gettimeofday(&v, NULL) == -1)
		return (perror("gettmieofday"), -1);
	return ((v.tv_sec * 1000) + v.tv_usec / 1000);
}

static void	ph_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ph_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0 || !s)
		return ;
	while (*(s + i))
	{
		ph_putchar_fd(*(s + i), fd);
		i++;
	}
}

void	ph_error(char *str)
{
	ph_putstr_fd("your argument: ", 2);
	ph_putstr_fd(str, 2);
	ph_putstr_fd(": is invalid\n", 2);
}
