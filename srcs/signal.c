#include "../includes/ft_select.h"

void sig_handler_stop()
{  
    disableRawMode(g_original);
    display_cursor();
    exit(0);
}

void sig_handler_cont()
{
    g_original = enableRawMode();
    hide_cursor();
    screen_clear();
    print_to_screen(&g_state);
}

void sig_handler_suspend()
{
    char *str = "process suspended ctrl+z\n";
    disableRawMode(g_original);
    display_cursor();
    write(1, str, ft_strlen(str));
    signal(SIGTSTP,sig_handler_default);
}

void sig_handler_default()
{
    return;
}