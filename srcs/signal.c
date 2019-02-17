/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:15:47 by rsathiad          #+#    #+#             */
/*   Updated: 2019/02/13 16:23:29 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	sig_handler_stop(void)
{
	disable_raw_mode(g_original);
	display_cursor();
	exit(0);
}

void	sig_handler_cont(void)
{
	g_original = enable_raw_mode();
	hide_cursor();
	screen_clear();
	print_to_screen(&g_state);
	ioctl(0, TIOCSTI, 27);
}

void	sig_handler_suspend(void)
{
	char	suspend[2];
	char	*str;

	tcgetattr(VSUSP, &g_original);
	suspend[0] = g_original.c_cc[VSUSP];
	suspend[1] = '\0';
	str = "process suspended ctrl+z\n";
	disable_raw_mode(g_original);
	display_cursor();
	write(1, str, ft_strlen(str));
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, suspend);
}

void	sig_handler_default(void)
{
	return ;
}

void	sig_handler_window(void)
{
	int				row;
	int				col;
	static int		check;

	row = 0;
	col = 0;
	check = 0;
	if (get_window_size(&row, &col) == -1)
		perror_exit("WINDOW RESIZEE FUCKED");
	if (col < g_display)
	{
		if (check != 1)
		{
			check = 1;
			screen_clear();
			write(2, "resize!", 7);
		}
	}
	else
	{
		check = 0;
		screen_clear();
		print_to_screen(&g_state);
	}
	return ;
}
