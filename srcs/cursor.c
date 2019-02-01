#include "../includes/ft_select.h"

void init_cursor(t_select **ptr_select)
{
    t_select *select;

    select = *ptr_select;
    select->cursor_x = 0;
    select->cursor_y = 0;
}

void screen_clear()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H",3);
}

int get_cursor_pos(int *rows, int *cols){
    /*char buf[32];
    unsigned int i;

    i = 0;
    if (write(STDOUT_FILENO, "\x1b[6n", 4)!= 4)
        return -1;
    
    while(i <(sizeof(buf) -1))
    {
        if (read(STDIN_FILENO, &buf[i], 1) != 1)
            break;
        i++;
    }
    buf[i] = '\0';
    ft_printf("\r\n&buf[1]: '%s'\r\n", &buf[1]);
    readinput();
    return -1;
    */
    ft_printf("cursor is at (%d,%d)\n",rows, cols);
    return 0;
}

void move_cursor_up(t_select **select)
{
    ft_printf("moveup\n");
    (void)select;
}
void move_cursor_down(t_select **select)
{
    (void)select;
    ft_printf("movedown\n");
}
void move_cursor_left(t_select **select)
{
    ft_printf("moveleft\n");(void)select;
}
void move_cursor_right(t_select **select)
{
    ft_printf("moveright\n");(void)select;
}
