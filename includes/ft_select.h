# ifndef FT_SELECT
#define FT_SELECT

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <signal.h>
#include "../libft/includes/libft.h"

typedef struct s_list 
{
    char *name;
    struct s_list *next;
} t_list;

int select_usage(void);
int perror_exit(char *str);
#endif