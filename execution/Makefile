# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 05:15:55 by ytouate           #+#    #+#              #
#    Updated: 2022/05/19 11:35:58 by ytouate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = exec
LIBFT = ./libft/libft.a
FILES = exec.c
O_FILES = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(O_FILES)
	@ar -rc  exec.a $(O_FILES)
	@$(CC) $(CFLAGS) $(LIBFT) exec.a  -o $(NAME) -lreadline

$(LIBFT) : 
	@make -C ./libft && make bonus -C ./libft
clean:
	@rm -f $(O_FILES) exec.a
	@cd libft && make clean && cd ..
fclean: clean
	@rm -rf exec $(NAME)
	@cd libft && make fclean && cd ..
re: fclean all