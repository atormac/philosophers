# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 13:55:29 by atorma            #+#    #+#              #
#    Updated: 2024/08/14 16:01:15 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS := -Wall -Wextra -Werror -pthread
LDFLAGS := -lpthread
INCLUDE_DIR = ./include
SOURCE_DIR = source
SOURCES = main.c init.c thread.c philo.c monitor.c print.c ft_atoi.c
OBJECTS = $(addprefix $(SOURCE_DIR)/,$(SOURCES:.c=.o))

target debug: CC = cc
target debug: CFLAGS += -fsanitize=address,undefined -g 

target thread: CC = clang-18
target thread: CFLAGS += -fsanitize=thread -g

target symbols: CC = cc
target symbols: CFLAGS += -gdwarf-4

all: $(NAME)

export CC
export CFLAGS

$(NAME): $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS) $(LDFLAGS)

$(SOURCE_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) $(LDFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: re
thread: re
symbols: re

.PHONY: debug thread symbols all clean fclean re
