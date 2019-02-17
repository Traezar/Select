/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:28:16 by rsathiad          #+#    #+#             */
/*   Updated: 2019/02/13 15:55:41 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include <ctype.h>

void	escape_program(t_select **select)
{
	disable_raw_mode(g_original);
	screen_clear();
	ft_printf("ft_selected exited!\n");
	(void)select;
	exit(0);
}

void	select_deselect(t_select **select)
{
	t_options *list;

	list = (*select)->options;
	while (list && !list->cursor)
		list = list->next;
	if (list->selected)
		list->selected = 0;
	else if (!(list->selected))
		list->selected = 1;
	screen_clear();
	print_to_screen(*select);
}

void	delete_option(t_select **select)
{
	t_options *list;
	t_options *del;

	ft_printf("Entered Delete option\n");
	list = (*select)->options;
	if (list->next == NULL)
		escape_program(select);
	if (list->cursor == 1)
	{
		del = list;
		(*select)->options = list->next;
		list = list->next;
	}
	else
	{
		while (list && !(list->next->cursor))
			list = list->next;
		del = list->next;
		list->next = list->next->next;
	}
	g_display -= (ft_strlen(del->name));
	free_option_node(del);
	list->cursor = 1;
	screen_clear();
	print_to_screen(*select);
}

char	readinput(void)
{
	int		readnum;
	char	c;
	char	seq[3];

	while ((readnum = read(0, &c, 1)) != 1)
		;
	if (c == 10)
		return (10);
	else if (c == 27)
	{
		if (read(STDIN_FILENO, &seq[0], 1) != 1)
			return (27);
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return (27);
		if (seq[0] == '[')
		{
			if ((read(STDIN_FILENO, &seq[2], 1) == 1))
				return (seq[2]);
			else
				return (seq[1]);
		}
	}
	if (c == 127 || c == 126)
		return (30);
	return (c & 0x1f);
}

void	process_input(t_select **select)
{
	char	c;
	int		i;

	i = -1;
	c = readinput();
	if (c == 31 || c == 51 || c == 126)
		c = 30;
	while (++i < 6)
	{
		if (g_dispatch[i].key == c)
		{
			g_dispatch[i].f(select);
			break ;
		}
	}
}
