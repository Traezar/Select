#include "../includes/ft_select.h"
#include <ctype.h>



void escape_program(t_select **select)
{
     ft_printf("Escape_program\n");
    (void) select; 
    exit(0);
}

void select_deselect(t_select **select)
{
    (void) select;
    ft_printf("seleted option\n");
}

void delete_option(t_select **select)
{
    (void) select;
    ft_printf("deleted option\n");
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
     if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else 
      printf("%d ('%c')\r\n", c, c);
    if (c == 27)
    {
        if (read(STDIN_FILENO, &seq[0], 1) != 1) 
            return 27;
        if (read(STDIN_FILENO, &seq[1], 1) != 1) 
            return 27;
        if (seq[0] == '[')
        {
            if ((read(STDIN_FILENO, &seq[2], 1) == 1))
                return seq[2];
            else
                return seq[1];
        }
    }
    if (c == 127 || c == 126)
        return 30;
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
        {SPACE_KEYCODE, select_deselect},
        {DEL_KEYCODE, delete_option}
    };

    i = 0;
    c = readinput();
    ft_printf("this is the value of key entered: %d\n" ,c);
    if (c == 31 || c == 51)
    c = 30;
    while (i < 7)
    {
       // ft_printf("this is the value of dispatch.key: %d\n for value of i:%d\n\n",dispatch[i].key,i);
        if (dispatch[i].key == c)
        {
            dispatch[i].f(select);
            break;
        }
        i++;
    }
    if (i == 7)
    printf("input doesnt not  match anthing in the dispatch table\n");
}