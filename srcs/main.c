#include <stdlib.h>
#include <termios.h>
#include "../includes/ft_select.h"

int main (int ac,char **av)
{
    char *buf;
    char *termtype;


    buf = malloc(2048);
    if (ac <= 1)
     select_usage();
    else
    {
        termtype = getenv("TERM");
        if (tgetent(buf, termtype))
        {
            (void)av;
            ft_printf("Terminal found: %s\n", termtype);
            //selection(termtype,av);
    
        }
        else
            perror_exit("Terminal not found!");
    }
    free(buf);
   return (0);     
}

/*void interrogate_terminal(char *termtype)
{
  am is "automatic wrap"
    cl is 
    co is 
    cm 
   
}

char *selection(char *termtype, char **av)
{
    t_select *ptr_to_list;
    char *selected;

    selected = NULL;
    ptr_to_list = copy_arguments_to_linked_list(av);
    selected = display_list_and_wait_for_selection(ptr_to_list);
    return (selected);
}

char *display_list_and_wait_for_selection(t_select *list_ptr)
{

    
}
*/