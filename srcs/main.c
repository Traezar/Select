#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include "../includes/ft_select.h"

int main (int ac,char **av)
{
    t_select select;
    char *ret;

    ret = "NULL";
    if (ac <= 1)
     select_usage();
    else
    {
        select.termtype = getenv("TERM");
        if (tgetent(NULL, select.termtype))
            ret =selection(&select,av, ac);
        else
            perror_exit("Terminal not found!");
    }
    ft_printf("%s", ret);
    return (0);     
}

char *selection(t_select *select, char **av, int ac)
{
    char *selected;

    selected = NULL;
    enableRawMode(select->original);
    intitalise_select_display(&select);
    select->options = copy_arguments_to_linked_list(av, ac);
    selected = display_list_and_wait_for_selection(&select);
    return(selected);
}

char *display_list_and_wait_for_selection(t_select **select)
{
    char c;

    c = 0;
    print_to_screen(*select);
    ft_printf("reading from stdin\n");
    while(1)
    {
        process_input(select);
    }
    return ("DONE!\n");
}

void intitalise_select_display(t_select **ptr_select)
{
    int row;
    int col;

    row = (*ptr_select)->screenrows;
    col = (*ptr_select)->screenrows;
    init_cursor(ptr_select);
    if (get_window_size(&row, &col) == -1)
        perror_exit("failure to initialise select screen");

}