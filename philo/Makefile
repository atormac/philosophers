# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 13:55:29 by atorma            #+#    #+#              #
#    Updated: 2024/07/29 16:16:49 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS := -Wall -Wextra -Werror 
LDFLAGS := -lpthread
SOURCES = main.c ft_atoi.c philo.c
OBJECTS = $(SOURCES:.c=.o)

target debug: CC = clang
target debug: CFLAGS += -fsanitize=address,undefined -g 

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

.PHONY: debug all clean fclean re
