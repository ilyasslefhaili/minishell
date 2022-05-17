# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 05:15:55 by ytouate           #+#    #+#              #
#    Updated: 2022/05/16 14:57:35 by ytouate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror 
NAME = exec
LIBFT = ./libft/libft.a
FILES = exec.c
O_FILES = $(FILES:.c=.o)
# RL = /goinfre/.brew/Cellar/readline/8.1.2/lib/libreadline.a\
#  -I /goinfre/.brew/Cellar/readline/8.1.2/include
all: $(NAME)

$(NAME): $(LIBFT) $(O_FILES)
	@ar -rc  exec.a $(O_FILES)
	@$(CC) $(CFLAGS) $(LIBFT) exec.a  -o $(NAME) $(RL) -lreadline 

$(LIBFT) : 
	@cd libft && make && make bonus && cd ..
clean:
	@rm -f $(O_FILES) exec.a
	@cd libft && make clean && cd ..
fclean: clean
	@rm -rf exec $(NAME)
	@cd libft && make fclean && cd ..
re: fclean all