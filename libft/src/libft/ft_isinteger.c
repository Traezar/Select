/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 12:28:22 by rsathiad          #+#    #+#             */
/*   Updated: 2019/02/17 12:31:21 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_isinteger(char *string)
{
	int				i;
	long long		value;

	i = -1;
	value = 0;
	while (string[++i] != '\0')
		if (!ft_isdigit(string[i]))
			return (0);
	value = ft_atoi(string);
	if (ft_strcmp(ft_itoa(value), string) == 0)
		return (1);
	return (0);
}
