##
## EPITECH PROJECT, 2018
## zappy
## File description:
## zappy spectator makefile
##

NAME	= ../../zappy_spec

CC	= g++

RM	= rm -f

SRCS	= srcs/main.cpp	\
	  srcs/Spectator.cpp	\
	  srcs/GraphSFML.cpp

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS	+= -g -I./inc/ -W -Wall -Wextra -std=c++11 -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CXXFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
