# ifndef FT_SELECT
#define FT_SELECT

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <signal.h>
#include "../libft/includes/libft.h"

typedef struct s_options 
{
    char *name;
    struct s_options *next;
} t_options;

typedef struct s_select
{
    struct s_options *next;
    int screenrows;
    int screencols;
    struct termios original;
} t_select;

int select_usage(void);
int perror_exit(char *str);
void enableRawMode(struct termios *original);
void disableRawMode(struct termios *original);
void create_and_push_list_nodes(t_options **ret, char *name);
t_options *copy_arguments_to_linked_list(char **av);
#endif