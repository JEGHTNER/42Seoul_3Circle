# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 21:57:45 by jehelee           #+#    #+#              #
#    Updated: 2023/03/26 15:51:43 by jehelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# INC_DIR		= ./lib/include/
# LIB_DIR		= ./lib/
# BN_DIR		= ./bonus/
SRCS_DIR	= ./src/

SRCS = free_error_utils.c ft_atoi.c init_functions.c monitoring.c main.c \
		time_utils.c thread_functions.c 

SRCS_BN = 

OBJ = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wextra -Werror -Wall

#rules
	
all : ${NAME}

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^ -g 


${NAME} : ${OBJ}
	$(CC) -o $(NAME) ${OBJ}

clean	:
	rm -rf $(OBJ)
	# rm -rf $(OBJS_BN)

fclean	: 
	rm -rf $(OBJ)
	rm -rf $(OBJS_BN)
	rm -rf	$(NAME)

re		: fclean all

# bonus: 
# 	make WITH_BONUS=1 all

.PHONY: all libs clean fclean re bonus