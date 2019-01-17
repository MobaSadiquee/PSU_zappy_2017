##
## EPITECH PROJECT, 2018
## zappy
## File description:
## zappy client makefile
##

NAME	= ../zappy_server

CC	= gcc -g

RM	= rm -f

SRCS	= 	src/check_params.c \
		src/check_params_second.c \
		src/inventory.c \
		src/look.c \
		src/look_return.c \
		src/main.c  \
		src/map.c  \
		src/move_player.c  \
		src/player.c  \
		src/player_item.c  \
		src/player_list.c  \
		src/server.c  \
		src/stack.c \
		src/stack_utils.c \
		src/broadcast.c \
		src/broadcast_all.c \
		src/elevation.c \
		src/food.c \
		src/player_utils.c \
		src/tick.c \
		src/graphic_cmd.c \
		src/egg.c \
		src/ejection.c \
		src/ejection_dir.c \
		src/server_utils.c \
		src/broadcast_s.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -I./includes/ -W -Wall -Wextra -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
