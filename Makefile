# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 11:29:17 by ytouate           #+#    #+#              #
#    Updated: 2022/05/19 11:42:43 by ytouate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CMPL_EXEC = make -C ./execution
CMPL_PARSING = cd parsing && make && cd ..

all:
	$(CMPL_PARSING) $(CMPL_EXEC)
clean:
	cd execution && make clean && cd ..
	cd parsing && make clean && cd ..
fclean:
	cd execution && make fclean && cd ..
	cd parsing && make fclean && cd ..