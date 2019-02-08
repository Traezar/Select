#include "../includes/ft_select.h"

void init_cursor(t_select **ptr_select)
{
    t_select *select;

    select = *ptr_select;
    select->cursor_x = 0;
    select->cursor_y = 0;
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
    t_options *list;

    list = (*select)->options;
    if (list->cursor)
    {
        list->cursor = 0;
        while(list->next != NULL)
            list = list->next;
        list->cursor = 1;
    }
    else 
    {
        while (list->next  && !((list->next)->cursor))
            list = list->next;
        if ((list->next)->cursor == 1)
        {
            list->cursor = 1;
            list->next->cursor = 0; 
        }
    }
    screen_clear();
    print_to_screen(*select);
}
void move_cursor_right(t_select **select)
{
    t_options *list;

    list = (*select)->options;
    while (list && !list->cursor)
        list=list->next;
    if(list->next)
    {
        list->cursor = 0;
        (list->next)->cursor =1;
    }
    else
    {
        list->cursor = 0;
        ((*select)->options)->cursor = 1;
    }
    screen_clear();
    print_to_screen(*select);
}
