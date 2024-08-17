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

void    ph_error(char *str)
{
    ph_putstr_fd("your argument: ", 2);
    ph_putstr_fd(str, 2);
    ph_putstr_fd(": is invalid\n", 2);
}