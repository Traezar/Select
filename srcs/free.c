/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 21:23:08 by rsathiad          #+#    #+#             */
/*   Updated: 2019/02/17 12:27:13 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	free_select(t_select *select)
{
	free_options(select->options);
	free_options(select->original_options);
}

void	free_options(t_options *ref)
{
	t_options *list;

	list = ref;
	if (list == NULL)
		return ;
	while (list != NULL)
	{
		free(list->name);
		free(list);
		list = list->next;
	}
}

void	sig_handler_select(int signo)
{
	if (signo == SIGTSTP)
		sig_handler_suspend();
	else if (signo == SIGINT)
		sig_handler_stop();
	else if (signo == SIGCONT)
		sig_handler_cont();
	else if (signo == SIGWINCH)
		sig_handler_window();
	else if (signo == 0)
		sig_handler_default();
}
