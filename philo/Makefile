# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 13:55:29 by atorma            #+#    #+#              #
#    Updated: 2024/07/30 15:36:47 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS := -Wall -Wextra -Werror 
LDFLAGS := -lpthread
SOURCES = main.c init.c philo.c print.c ft_atoi.c
OBJECTS = $(SOURCES:.c=.o)

target debug: CC = cc
target debug: CFLAGS += -fsanitize=address,undefined -g 

target thread: CC = cc
target thread: CFLAGS += -fsanitize=thread -g

all: $(NAME)

export CC
export CFLAGS

$(NAME): $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS) $(LDFLAGS)

$(SOURCE_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: re
thread: re

.PHONY: debug all clean fclean re
