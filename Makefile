# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucas <lucas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/19 17:09:08 by lucas             #+#    #+#              #
#    Updated: 2026/03/24 11:44:48 by lucas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =	srcs/minishell.c\
		srcs/parsing/tokeniser.c srcs/parsing/tokeniser-utils.c\
		srcs/parsing/cmd.c srcs/parsing/cmd-utils.c\
		srcs/parsing/expander.c srcs/parsing/expander-utils.c\
		srcs/parsing/expander-str.c\
		srcs/env/get-env.c srcs/env/set-env.c\
		srcs/signals/signals.c\
		libft.c\
		builtins/builtins.c\
		builtins/echo.c builtins/cd.c builtins/pwd.c\
		builtins/export.c builtins/unset.c builtins/env.c\
		builtins/exit.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o: %.c includes/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all fclean clean re
