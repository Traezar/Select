/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 21:34:59 by rsathiad          #+#    #+#             */
/*   Updated: 2019/02/17 12:33:07 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include "../libft/includes/libft.h"

# define ESC_KEYCODE 27
# define UP_KEYCODE 65
# define DOWN_KEYCODE 66
# define LEFT_KEYCODE 68
# define RIGHT_KEYCODE 67
# define SPACE_KEYCODE 0
# define DEL_KEYCODE 30

typedef struct			s_select
{
	struct s_options	*original_options;
	struct s_options	*options;
	int					screenrows;
	int					screencols;
	int					cursor_x;
	int					cursor_y;
	char				*termtype;
	char				**choice;
}						t_select;

typedef struct			s_dispatch
{
	int					key;
	void				(*f)(t_select **);
}						t_dispatch;

typedef struct			s_options
{
	char				*name;
	struct s_options	*next;
	bool				selected;
	bool				cursor;
	bool				deleted;
}						t_options;

struct termios			g_original;
t_select				g_state;
int						g_display;

/*
**main.c
*/
char					**display_list_and_wait_for_selection\
							(t_select **list_ptr);
char					**selection(t_select *select, char **av, int ac);
void					intitalise_select_display(t_select **ptr_select);
void					return_choice(t_select **select);

/*
**cursor.c
*/
void					init_cursor(t_select **ptr_select);
void					move_cursor_up(t_select **select);
void					move_cursor_down(t_select **select);
void					move_cursor_left(t_select **select);
void					move_cursor_right(t_select **select);

/*
**keyboard.c
*/
char					readinput(void);
void					process_input(t_select **select);
void					escape_program(t_select **select);
void					select_deselect(t_select **select);
void					delete_option(t_select **select);

/*
**window.c
*/
int						get_window_size(int *rows, int *cols);
void					print_to_screen(t_select *select);
int						check_print_type(t_options *list);
int						set_display_len(t_options *input);

/*
**list.c
*/
void					create_and_push_list_nodes(t_options **ret, char *name);
t_options				*copy_arguments_to_linked_list(char **av, int ac);
void					duplicate_node(t_options *node_ptr,
		t_options **ptr_to_head);
void					duplicate_list(t_options *original,
		t_options **ptr_to_head);
void					free_option_node(t_options *node);

/*
**terminal.c
*/
struct termios			enable_raw_mode(void);
void					disable_raw_mode(struct termios original);
void					display_cursor(void);
void					hide_cursor(void);

/*
**error.c
*/
int						select_usage(void);
int						perror_exit(char *str);
void					screen_clear(void);
void					sig_handler_cont(void);
void					sig_handler_stop(void);
void					sig_handler_suspend(void);
void					sig_handler_default(void);
void					sig_handler_window(void);

static t_dispatch		g_dispatch[] =
{
	{ESC_KEYCODE, escape_program},
	{LEFT_KEYCODE, move_cursor_left},
	{RIGHT_KEYCODE, move_cursor_right},
	{SPACE_KEYCODE, select_deselect},
	{DEL_KEYCODE, delete_option},
	{10, return_choice}
};

/*
**free.c
*/
void					free_select(t_select *select);
void					free_options(t_options *ref);
void					sig_handler_select(int signo);
#endif
