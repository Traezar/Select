/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:02:28 by rsathiad          #+#    #+#             */
/*   Updated: 2019/02/13 16:15:26 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include "../includes/ft_select.h"

int			main(int ac, char **av)
{
	t_select	select;
	int			count;

	count = -1;
	select.choice = NULL;
	if (ac <= 1)
		select_usage();
	select.termtype = getenv("TERM");
	if (tgetent(NULL, select.termtype))
		select.choice = selection(&select, av, ac);
	else
		perror_exit("Terminal not found!");
	disable_raw_mode(g_original);
	display_cursor();
	while (select.choice[++count] != NULL)
	{
		ft_printf("%s", select.choice[count]);
		if (select.choice[count + 1] != NULL)
			ft_printf(" ");
	}
	free_select(&select);
	return (0);
}

char		**selection(t_select *select, char **av, int ac)
{
	char **selected;

	selected = NULL;
	g_original = enable_raw_mode();
	select->options = copy_arguments_to_linked_list(av, ac);
	select->original_options = NULL;
	g_display = set_display_len(select->options);
	duplicate_list(select->options, &select->original_options);
	selected = display_list_and_wait_for_selection(&select);
	return (selected);
}

char		**display_list_and_wait_for_selection(t_select **select)
{
	char c;

	c = 0;
	print_to_screen(*select);
	g_state = **select;
	signal(SIGTSTP, &sig_handler_select);
	signal(SIGINT, &sig_handler_select);
	signal(SIGCONT, &sig_handler_select);
	signal(SIGWINCH, &sig_handler_select);
	signal(0, &sig_handler_select);
	while (1)
	{
		process_input(select);
		g_state = **select;
		screen_clear();
		print_to_screen(*select);
		if ((*select)->choice != NULL)
			return ((*select)->choice);
	}
}

void		intitalise_select_display(t_select **ptr_select)
{
	int		row;
	int		col;

	row = (*ptr_select)->screenrows;
	col = (*ptr_select)->screenrows;
	init_cursor(ptr_select);
	if (get_window_size(&row, &col) == -1)
		perror_exit("GET WINDOW SIZE RETURNED -1");
}

void		return_choice(t_select **select)
{
	t_options	*list;
	char		**ret;
	int			count;

	count = 0;
	list = (*select)->options;
	while (list != NULL)
	{
		if (list->selected)
			count++;
		list = list->next;
	}
	ret = malloc((sizeof(char*) * count) + 1);
	ret[count] = NULL;
	count = -1;
	list = (*select)->options;
	while (list != NULL)
	{
		if (list->selected)
		{
			ret[++count] = ft_strdup(list->name);
		}
		list = list->next;
	}
	(*select)->choice = ret;
}
