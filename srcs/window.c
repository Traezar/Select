#include "../includes/ft_select.h"


// whenever  get a signal named SIGWINCH, use ioctl with code TIOCGWINSZ gets the window size;
int get_window_size(int *rows, int *cols)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col <= 0)
		return (-1);
	else
	{
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return (0);
	}
}
int check_print_type(t_options *list)
{
	if (list->deleted)
		return 0;
	if (list->cursor == 1 && list->selected == 1)
	{
		ft_printf("\e[4:7m");
		ft_printf("%s", list->name);
		ft_printf("\e[0m");
	}
	else if (list->cursor ==1)
	{
		ft_printf("\e[4m");
		ft_printf("%s", list->name);
		ft_printf("\e[0m");

	}
	else if (list->selected == 1)
	{	ft_printf("\e[7m");
		ft_printf("%s", list->name);
		ft_printf("\e[0m");
	}
	else
		ft_printf("%s", list->name);

	return 1;
}

void print_to_screen (t_select *select)
{
	t_options *list;

	list = select->options;
	while (list != NULL)
	{
		if (check_print_type(list))
		{
			if (list->next != NULL)
				write (1,"\t",1);
			else
				write(1,"\n",1);
		}
		else if (list->next == NULL)
			write(1,"\n",1);
		list = list->next;
	}
	return ;
}