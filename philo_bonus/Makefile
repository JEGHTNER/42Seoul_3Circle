# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 21:57:45 by jehelee           #+#    #+#              #
#    Updated: 2023/04/01 21:39:33 by jehelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

INC_DIR		= ./include/
SRCS_DIR	= ./src/

SRCS = free_error_utils_bonus.c ft_itoa.c ft_atoi.c init_functions_bonus.c monitoring_bonus.c main.c \
		time_utils_bonus.c thread_functions_bonus.c 


OBJ = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

CC = cc
CFLAGS = -Wextra -Werror -Wall

#rules

all : ${NAME}

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I $(INC_DIR) -g 

${NAME} : ${OBJ}
	$(CC) -o $(NAME) ${OBJ} -I $(INC_DIR) -g 

clean	:
	rm -rf $(OBJ)
	# rm -rf $(OBJS_BN)

fclean	: 
	rm -rf $(OBJ)
	rm -rf $(OBJS_BN)
	rm -rf	$(NAME)

re		: fclean all

.PHONY: all libs clean fclean re