##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile
##

NAME	= ../myteams_server

CC	= gcc

RM	= rm -f

SRCS	= ./src/command/analyse_command.c \
	  ./src/command/exec_command/create/create.c \
	  ./src/command/exec_command/create/create_channel.c \
	  ./src/command/exec_command/create/create_team.c \
	  ./src/command/exec_command/create/create_thread.c \
	  ./src/command/exec_command/create/replay_thread.c \
	  ./src/command/exec_command/do_basics.c \
	  ./src/command/exec_command/redir_commands.c \
	  ./src/command/exec_command/info/info.c \
	  ./src/command/exec_command/info/info_channel.c \
	  ./src/command/exec_command/info/info_team.c \
	  ./src/command/exec_command/info/info_thread.c \
	  ./src/command/exec_command/list/list.c \
	  ./src/command/exec_command/list/list_channels.c \
	  ./src/command/exec_command/list/list_replies.c \
	  ./src/command/exec_command/list/list_teams.c \
	  ./src/command/exec_command/list/list_threads.c \
	  ./src/command/exec_command/no_argument/display_help.c \
	  ./src/command/exec_command/no_argument/display_users.c \
	  ./src/command/exec_command/no_argument/logout_client.c \
	  ./src/command/exec_command/one_argument/display_messages.c \
	  ./src/command/exec_command/one_argument/get_info_user.c \
	  ./src/command/exec_command/one_argument/subscribe_to_event.c \
	  ./src/command/exec_command/one_argument/unsubscribe_to_event.c \
	  ./src/command/exec_command/one_argument/unsubscribe_log.c \
	  ./src/command/exec_command/one_argument/unsubscribe.c \
	  ./src/command/exec_command/send_error_to_client.c \
	  ./src/command/exec_command/two_arguments/send_message_to_user.c \
	  ./src/command/exec_command/two_arguments/send_message_multi_user.c \
	  ./src/command/exec_command/use/set_team.c \
	  ./src/command/exec_command/use/set_team_channel.c \
	  ./src/command/exec_command/use/set_team_channel_thread.c \
	  ./src/command/exec_command/use/team_channel_thread_display.c \
	  ./src/command/exec_command/use/unset_use.c \
	  ./src/command/exec_command/use/use.c \
	  ./src/command/recup_command.c \
	  ./src/config/build_fd_sets.c \
	  ./src/config/exit.c \
	  ./src/config/init.c \
	  ./src/config/my_select.c \
	  ./src/connexion/check_user.c \
	  ./src/connexion/connexion.c \
	  ./src/connexion/set_user_pass.c \
	  ./src/main.c \
	  ./src/tools/clean_str.c \
	  ./src/tools/command_to_array.c \
	  ./src/tools/free_array.c \
	  ./src/tools/get_last_line.c \
	  ./src/tools/get_uuid_channel.c \
	  ./src/tools/get_uuid_thread.c \
	  ./src/tools/is_good_argument.c \
	  ./src/tools/recup_id.c \
	  ./src/tools/send_message.c \
	  ./src/tools/str_to_word_array.c \
	  ./src/tools/str_without_quotes.c \
	  ./src/tools/tools.c

SRC_NORMAL	= ./src/core/my_server.c

SRC_BONUS	= ../bonus/server/my_server.c

OBJS	= $(SRCS:.c=.o)

OBJ_NORMAL	= $(SRC_NORMAL:.c=.o)

OBJ_BONUS	= $(SRC_BONUS:.c=.o)

CFLAGS = -I ./include/
CFLAGS += -I ../libs/myteams/
CFLAGS += -Wall -Wextra

LDFLAGS = -L ../libs/myteams/ -lmyteams -luuid

all: $(NAME)

bonus: fclean $(NAME_BONUS)

$(NAME_BONUS): $(OBJS) $(OBJ_BONUS)
	 $(RM) $(NAME)
	 $(CC) $(OBJS) $(OBJ_BONUS) -o $(NAME) $(LDFLAGS)

$(NAME): $(OBJS) $(OBJ_NORMAL)
	$(RM) $(NAME)
	 $(CC) $(OBJS) $(OBJ_NORMAL) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(OBJ_NORMAL) $(OBJ_NORMAL)

fclean: clean
	$(RM) $(NAME)

re: fclean all


debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug bonus
