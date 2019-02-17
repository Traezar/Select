/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:24:00 by rsathiad          #+#    #+#             */
/*   Updated: 2019/02/13 16:34:08 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int		termput_c(int c)
{
	return (write(2, &c, 1));
}

struct termios	enable_raw_mode(void)
{
	struct termios	raw;
	struct termios	original;

	if (tcgetattr(STDIN_FILENO, &raw) == -1)
		perror_exit("Enable Raw Mode tcgetattr failure");
	original = raw;
	raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		perror_exit("Enable Raw Mode tcsetattr failure");
	hide_cursor();
	return (original);
}

void			disable_raw_mode(struct termios original)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original) == -1)
		perror_exit("Disable Raw Mode tcsetattr failure");
	display_cursor();
}

void			display_cursor(void)
{
	tputs(tgetstr("ve", NULL), 1, termput_c);
}

void			hide_cursor(void)
{
	tputs(tgetstr("vi", NULL), 1, termput_c);
}
