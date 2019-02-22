/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:34:38 by rsathiad          #+#    #+#             */
/*   Updated: 2019/02/13 16:41:27 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		get_window_size(int *rows, int *cols)
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col <= 0)
		return (-1);
	else
	{
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return (0);
	}
}

int		set_display_len(t_options *input)
{
	int			len;
	int			i;
	char		*str;
	t_options	*list;

	len = 0;
	list = input;
	if (!list)
		sig_stop_handler();
	while (list != NULL)
	{
		i = 0;
		str = list->name;
		while (str[i] != '\0')
		{
			len++;
			i++;
		}
		len += 4;
		i = 0;
		list = list->next;
	}
	len += 5;
	return (len);
}

int		check_print_type(t_options *list)
{
	if (list->deleted)
		return (0);
	if (list->cursor == 1 && list->selected == 1)
	{
		write(2, "\e[4;7m", 6);
		write(2, list->name, ft_strlen(list->name));
		write(2, "\e[0m", 4);
	}
	else if (list->cursor == 1)
	{
		write(2, "\e[4m", 4);
		write(2, list->name, ft_strlen(list->name));
		write(2, "\e[0m", 4);
	}
	else if (list->selected == 1)
	{
		write(2, "\e[7m", 4);
		write(2, list->name, ft_strlen(list->name));
		write(2, "\e[0m", 4);
	}
	else
		write(2, list->name, ft_strlen(list->name));
	return (1);
}

void	print_to_screen(t_select *select)
{
	t_options *list;

	list = select->options;
	while (list != NULL)
	{
		if (check_print_type(list))
		{
			if (list->next != NULL)
				write(2, "\t", 1);
			else
				write(2, "\n", 1);
		}
		else if (list->next == NULL)
			write(2, "\n", 1);
		list = list->next;
	}
	return ;
}
