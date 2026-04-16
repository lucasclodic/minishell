# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/19 17:09:08 by lucas             #+#    #+#              #
#    Updated: 2026/04/15 16:51:35 by lclodic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/*.c) $(wildcard $(LIBFT_DIR)/*.h)

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	READLINE_PREFIX := $(shell brew --prefix readline 2>/dev/null)
	CFLAGS += -I$(READLINE_PREFIX)/include
	LDFLAGS := -L$(READLINE_PREFIX)/lib $(LDFLAGS)
endif

SRCS =	srcs/main.c srcs/main2.c\
		srcs/parsing/tokeniser.c srcs/parsing/tokeniser-utils.c\
		srcs/parsing/cmd.c srcs/parsing/cmd-utils.c\
		srcs/parsing/expander.c srcs/parsing/expander-utils.c\
		srcs/parsing/expander-str.c\
		srcs/env/get-env.c srcs/env/set-env.c\
		srcs/signals/signals.c\
		srcs/error.c\
		builtins/builtins.c\
		builtins/echo.c builtins/cd.c builtins/pwd.c\
		builtins/export.c builtins/export_utils.c builtins/unset.c builtins/env.c\
		builtins/exit.c\
		exec.c execute_cmd.c exec_utils.c exec_utils2.c redirs.c exec_utils3.c\
		exec_utils4.c redirs2.c exec2.c heredoc.c\
		gnl.c gnl_utils.c gnl_utils2.c\
		exec_helper_cleanup.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
VPATH = srcs:srcs/parsing:srcs/env:srcs/signals:builtins:srcs/exec:srcs/gnl:.

all: $(NAME)

$(LIBFT): $(LIBFT_SRCS)
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

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
