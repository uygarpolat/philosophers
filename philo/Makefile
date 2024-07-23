# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 17:57:36 by upolat            #+#    #+#              #
#    Updated: 2024/07/23 03:29:36 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# SRC_DIR = src/mandatory

SOURCES =		philo.c \
				create_mutexes.c \
				cleanup.c \
				eat_sleep_think.c \
				overseer.c \
				time.c \
				utils.c \
				initialize.c \
				threads.c \

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

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
