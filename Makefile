# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 05:15:55 by ytouate           #+#    #+#              #
#    Updated: 2022/05/11 16:19:40 by ytouate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
NAME = exec
LIBFT = ./libft/libft.a
FILES = exec.c get_next_line.c get_next_line_utils.c
O_FILES = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(O_FILES)
	ar -rc  exec.a $(O_FILES)
	@$(CC) $(CFLAGS) $(LIBFT) exec.a  -o $(NAME) -lreadline
$(LIBFT) : 
	cd libft && make && make bonus && cd ..
clean:
	@rm -f $(O_FILES) exec.a
fclean: clean
	@rm -rf exec $(NAME)
re: fclean all