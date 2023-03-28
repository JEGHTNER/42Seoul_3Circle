# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 21:57:45 by jehelee           #+#    #+#              #
#    Updated: 2023/03/28 13:11:19 by jehelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INC_DIR		= ./include/
SRCS_DIR	= ./src/

SRCS = free_error_utils.c ft_atoi.c init_functions.c monitoring.c main.c \
		time_utils.c thread_functions.c 


OBJ = $(addprefix $(SRCS_DIR)/, $(SRCS:.c=.o))

CC = cc
CFLAGS = -Wextra -Werror -Wall

#rules

all : ${NAME}

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I $(INC_DIR)


${NAME} : ${OBJ}
	$(CC) -o $(NAME) ${OBJ} -I $(INC_DIR) 

clean	:
	rm -rf $(OBJ)
	# rm -rf $(OBJS_BN)

fclean	: 
	rm -rf $(OBJ)
	rm -rf $(OBJS_BN)
	rm -rf	$(NAME)

re		: fclean all

.PHONY: all libs clean fclean re