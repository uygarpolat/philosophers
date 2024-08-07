# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 17:57:36 by upolat            #+#    #+#              #
#    Updated: 2024/08/07 13:29:03 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SOURCES =		philo_bonus.c \
				create_semaphores_bonus.c \
				eat_sleep_think_bonus.c \
				overseer_bonus.c \
				time_bonus.c \
				utils_bonus.c \
				initialize_bonus.c \
				processes_bonus.c \
				post_process_bonus.c \

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
