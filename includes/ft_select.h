# ifndef FT_SELECT
#define FT_SELECT

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <signal.h>
#include "../libft/includes/libft.h"
#define ESC_KEYCODE 27
#define UP_KEYCODE 65
#define DOWN_KEYCODE 66
#define LEFT_KEYCODE 68
#define RIGHT_KEYCODE 67
#define SPACE_KEYCODE 0

typedef struct s_select
{
    struct s_options *options;
    int screenrows;
    int screencols;
    int cursor_x;
    int cursor_y;
    char *termtype;
    struct termios original;
} t_select;

typedef struct s_dispatch 
{
    int key;
    void (*f)(t_select **);
} t_dispatch;
typedef struct s_options 
{
    char *name;
    struct s_options *next;
} t_options;



/*main.c*/
char *display_list_and_wait_for_selection(t_select **list_ptr);
char *selection(t_select *select, char **av, int ac);
void intitalise_select_display(t_select **ptr_select);

/*cursor.c*/
void init_cursor(t_select **ptr_select);
void screen_clear();
int get_cursor_pos(int *rows, int *cols);
void move_cursor_up(t_select **select);
void move_cursor_down(t_select **select);
void move_cursor_left(t_select **select);
void move_cursor_right(t_select **select);

/*keyboard.c*/
char readinput();
void process_input(t_select **select);
void escape_program(t_select **select);
void select_deselect(t_select **select);

/*window.c*/
int get_window_size(int *rows, int *cols);

/*list.c*/
void create_and_push_list_nodes(t_options **ret, char *name);
t_options *copy_arguments_to_linked_list(char **av, int ac);

/*terminal.c*/
void enableRawMode(struct termios original);
void disableRawMode(struct termios original);

/*error.c*/
int select_usage(void);
int perror_exit(char *str);



#endif