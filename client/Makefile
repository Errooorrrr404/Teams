##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile
##

NAME	= ../myteams_cli

CC	= gcc

RM	= rm -f

SRCS	= ./src/analyse_code/code.c \
	  ./src/analyse_code/display_users.c \
	  ./src/analyse_code/log_other_clients.c \
	  ./src/analyse_code/comand_accepted.c \
	  ./src/core/listen_server.c \
	  ./src/core/loop.c \
	  ./src/core/my_client.c \
	  ./src/main.c \
	  ./src/tools/clean_str.c \
	  ./src/tools/free_array.c \
	  ./src/tools/str_to_word_array.c \
	  ./src/tools/tools.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/
CFLAGS += -I ../libs/myteams/
CFLAGS += -Wall -Wextra

LDFLAGS = -L ../libs/myteams/ -lmyteams

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug