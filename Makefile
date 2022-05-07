# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 05:15:55 by ytouate           #+#    #+#              #
#    Updated: 2022/05/07 11:40:39 by ytouate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = exec

FILES = exec.c libft_utils.c get_next_line.c get_next_line_utils.c

O_FILES = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(O_FILES)
	ar -rc  exec.a $(O_FILES)
	@$(CC) $(CFLAGS) exec.c exec.a -o $(NAME) -lreadline

clean:
	@rm -f $(O_FILES)
fclean: clean
	@rm -rf exec.a $(NAME) 
re: fclean all