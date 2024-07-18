# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 17:57:36 by upolat            #+#    #+#              #
#    Updated: 2024/07/18 14:12:41 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src/mandatory

SOURCES =		$(SRC_DIR)/philo.c \
				$(SRC_DIR)/create_mutexes.c \
				$(SRC_DIR)/cleanup.c \
				$(SRC_DIR)/eat_sleep_think.c \
				$(SRC_DIR)/overseer.c \
				$(SRC_DIR)/time.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/initialize.c \
				$(SRC_DIR)/threads.c \

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
