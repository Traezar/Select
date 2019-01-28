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
    ft_printf("Terminal type is :%s\nEntered Selection\n",select->termtype);
    enableRawMode(select->original);
    ft_printf("Raw Mode Enabled\n");
    select->options = copy_arguments_to_linked_list(av, ac);
    ft_printf("arguments copied\n");
    selected = display_list_and_wait_for_selection(select);
    return(selected);
}

char *display_list_and_wait_for_selection(t_select *select)
{
    char c;

    (void)select;
    c = 0;
    ft_printf("reading from stdin\n");
    while(1)
    {
        if(read(STDIN_FILENO, &c, 1) == -1)
            perror_exit("selection: Read returned: -1"); 
        if (iscntrl(c)) 
            ft_printf("%d\n", c);
        else
            ft_printf("%d ('%c')\n", c, c);
        if (c == 27)
            break;
    }
    return ("DONE!\n");
}