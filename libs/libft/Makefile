# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 13:45:19 by omadali           #+#    #+#              #
#    Updated: 2025/10/17 19:30:16 by omadali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

AR = ar rcs

FLAGS = -Wextra -Wall -Werror

SRCS =	ft_atoi.c \
		ft_lstadd_back.c \
		ft_lstclear.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_split_utils.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strrchr.c \
		ft_strtrim.c

OBJS=$(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(AR)  $(NAME) $(OBJS) 
	@echo "OLMAK" 
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "TEMİZ"

fclean: clean
	@rm -f $(NAME)
	@echo "TERTEMİZ"

re: fclean all

.PHONY: all clean fclean re
