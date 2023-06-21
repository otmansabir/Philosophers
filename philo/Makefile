# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osabir <osabir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 14:51:58 by osabir            #+#    #+#              #
#    Updated: 2023/06/19 15:09:10 by osabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 

FLAGS = -Wall -Wextra -Werror # -fsanitize=thread

SRC = philo.c ft_atoi.c info_and_malloc.c philo_and_circle.c \
		routine_and_tool.c send_philo_and_wait.c

OBJ = $(SRC:.c=.o)

NAME = philo

HD = philo.h 

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HD)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re : fclean all