/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:23:34 by rsathiad          #+#    #+#             */
/*   Updated: 2019/02/13 15:27:40 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../includes/ft_select.h"

int		select_usage(void)
{
	ft_printf("ft_select: usage: ./ft_select arg1 arg2 .....argN \n");
	return (0);
}

int		perror_exit(char *str)
{
	write(STDERR_FILENO, "\x1b[2J", 4);
	write(STDERR_FILENO, "\x1b[H", 3);
	ft_printf("ft_select: %s", str);
	exit(1);
}

void	screen_clear(void)
{
	write(2, "\x1b[2J\x1b[H", 7);
}
