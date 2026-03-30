# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnicolas <mnicolas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 15:13:47 by lclodic           #+#    #+#              #
#    Updated: 2026/03/30 13:44:42 by mnicolas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =			ft_atoi.c ft_isascii.c ft_memset.c ft_bzero.c ft_isdigit.c \
				ft_strlen.c ft_isalnum.c ft_isprint.c ft_isalpha.c ft_memcpy.c \
				ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
				ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
				ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
				ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJS = 			$(SRCS:.c=.o)

BONUS =			ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
				ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS_BONUS =	$(BONUS:.c=.o)

CC =			cc
RM =			rm -f
CFLAGS =		-Wall -Wextra -Werror
AR =			ar rcs

NAME =			libft.a

all :			$(NAME)

$(NAME) :		$(OBJS)
	@$(AR) $(NAME) $(OBJS)

%.o: %.c		libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean :		clean
	@$(RM) $(NAME)

re : 			fclean $(NAME)

bonus:			$(OBJS) $(OBJS_BONUS)
	@$(AR) $(NAME) $(OBJS) $(OBJS_BONUS)

.PHONY:			all clean fclean re bonus
