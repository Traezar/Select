# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsathiad <3kiraj@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/09 08:38:15 by rsathiad          #+#    #+#              #
#    Updated: 2019/01/27 14:55:07 by rsathiad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
OBJ = *.o

SRC = srcs/main.c srcs/error.c srcs/keyboard.c srcs/terminal.c srcs/list.c srcs/window.c
HDR = includes/select.h

all: LIBFT select 

select:
	@gcc -o $(NAME) $(CFLAGS) $(SRC) -I $(HDR) -L libft -lft -ltermcap -g
	@echo "\033[1;32m[Compiled]\033[0m: \033[1;33m./ft_select\033[0m"

LIBFT :
	@cd libft && make

clean:
	@rm -rf $(OBJ)
	@echo "\033[1;31m[Removed]\033[0m: select object files"

fclean: clean
	@clear
	@rm -rf ft_select
	@cd libft && make fclean

re: fclean all

CFLAGS = -Wall -Werror -Wextra

PHONY:
	clean fclean all re
