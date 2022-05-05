# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 05:15:55 by ytouate           #+#    #+#              #
#    Updated: 2022/05/05 05:32:17 by ytouate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = exec

FILES = exec.c
O_FILES = $(FILES:.c=.o)

all: $(NAME)
$(NAME): $(FILES)
	@$(CC) $(CFLAGS) exec.c -o $(NAME)

clean:
	@rm -f $(O_FILES)
fclean: clean
	@rm -rr $(NAME)
re: fclean all