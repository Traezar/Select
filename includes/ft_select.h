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
#define BOLD \e[1m
#define UNDER_ \e[4m
#define REV_ \e[7m
#define UNDER_REV \e[4;7m
#define ESC_KEYCODE 27
#define UP_KEYCODE 65
#define DOWN_KEYCODE 66
#define LEFT_KEYCODE 68
#define RIGHT_KEYCODE 67
#define SPACE_KEYCODE 0
#define DEL_KEYCODE 30

typedef struct s_select
{
    struct s_options *original_options;
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
    bool selected;
    bool cursor;
    bool deleted; 
} t_options;



/*main.c*/
char *display_list_and_wait_for_selection(t_select **list_ptr);
char *selection(t_select *select, char **av, int ac);
void intitalise_select_display(t_select **ptr_select);

/*cursor.c*/
void init_cursor(t_select **ptr_select);
void move_cursor_up(t_select **select);
void move_cursor_down(t_select **select);
void move_cursor_left(t_select **select);
void move_cursor_right(t_select **select);

/*keyboard.c*/
char readinput();
void process_input(t_select **select);
void escape_program(t_select **select);
void select_deselect(t_select **select);
void delete_option(t_select **select);

/*window.c*/
int get_window_size(int *rows, int *cols);
void print_to_screen(t_select *select);
int check_print_type(t_options *list);

/*list.c*/
void create_and_push_list_nodes(t_options **ret, char *name);
t_options *copy_arguments_to_linked_list(char **av, int ac);
void duplicate_node(t_options *node_ptr, t_options **ptr_to_head);
void duplicate_list(t_options *original, t_options **ptr_to_head);
void free_option_node(t_options *node);

/*terminal.c*/
struct termios enableRawMode(void);
void disableRawMode(struct termios original);

/*error.c*/
int select_usage(void);
int perror_exit(char *str);
void screen_clear();



#endif