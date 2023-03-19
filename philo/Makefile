# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 16:31:23 by jehelee           #+#    #+#              #
#    Updated: 2023/03/19 19:12:49 by jehelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# INC_DIR		= ./lib/include/
# LIB_DIR		= ./lib/
# BN_DIR		= ./bonus/
SRCS_DIR	= ./src/

SRCS = error_utils.c ft_atoi.c main.c

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