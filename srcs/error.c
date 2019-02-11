#include <unistd.h>
#include <stdlib.h>
#include "../includes/ft_select.h"

int select_usage()
{
    ft_printf( "ft_select: usage\n\tThis program aim to demonstrate\
     the selection capabilities of terminals.\n\tusage: ./ft_select arg1 arg2 .....argN");
     return (0);
}

int perror_exit(char *str)
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H",3);
    ft_printf("ft_select: %s", str);
    exit(1);
}
void screen_clear()
{
    ft_printf("\x1b[2J\x1b[H");
}

