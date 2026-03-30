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

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	srcs/minishell.c\
		srcs/parsing/tokeniser.c srcs/parsing/tokeniser-utils.c\
		srcs/parsing/cmd.c srcs/parsing/cmd-utils.c\
		srcs/parsing/expander.c srcs/parsing/expander-utils.c\
		srcs/parsing/expander-str.c\
		srcs/env/get-env.c srcs/env/set-env.c\
		srcs/signals/signals.c\
		builtins/builtins.c\
		builtins/echo.c builtins/cd.c builtins/pwd.c\
		builtins/export.c builtins/unset.c builtins/env.c\
		builtins/exit.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
VPATH = srcs:srcs/parsing:srcs/env:srcs/signals:builtins

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: %.c includes/minishell.h | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
