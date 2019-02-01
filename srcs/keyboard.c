#include "../includes/ft_select.h"



void escape_program(t_select **select)
{
     ft_printf("Escape_program\n");
    (void) select; 
    exit(0);
}

void select_deselect(t_select **select)
{
    (void) select;
    ft_printf("seleted option");
}


char readinput(){
    int readnum;
    char c;
    char seq[3];

    while ((readnum = read(STDIN_FILENO, &c , 1)) != 1)
    {
        if (readnum == -1)
            perror_exit("readinput fail");
    }

    if (c == 27)
    {
        if (read(STDIN_FILENO, &seq[0], 1) != 1) 
            return 27;
        if (read(STDIN_FILENO, &seq[1], 1) != 1) 
            return 27;
        if (seq[0] == '[')
            return seq[1];
    }
    return (c & 0x1f);
}

void process_input(t_select **select)
{
    char c;
    int i;
    static  t_dispatch dispatch[]=
    {
        {ESC_KEYCODE, escape_program},
        {UP_KEYCODE, move_cursor_up},
        {DOWN_KEYCODE, move_cursor_down},
        {LEFT_KEYCODE, move_cursor_left},
        {RIGHT_KEYCODE, move_cursor_right},
        {SPACE_KEYCODE, select_deselect}
    };

    i = 0;
    c = readinput();
     ft_printf("this is the value of key entered: %d\n" ,c);
    while (i < 6)
    {
        ft_printf("this is the value of dispatch.key: %d\n for value of i:%d\n\n",dispatch[i].key,i);
        if (dispatch[i].key == c)
            dispatch[i].f(select);
        i++;
    }
    if (i == 6)
    printf("input doesnt not  match anthing in the dispatch table\n");
}