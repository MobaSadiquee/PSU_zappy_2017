##
## EPITECH PROJECT, 2018
## zappy
## File description:
## zappy client makefile
##

NAME	= ../zappy_ai

CC	= g++

RM	= rm -f

SRCS	= srcs/main.cpp	\
	  srcs/Client.cpp \
	  srcs/Ia.cpp \
	  srcs/takeRessource.cpp \
	  srcs/mainLoop.cpp \
	  srcs/think.cpp

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS	+= -g -I./inc/ -W -Wall -Wextra -std=c++11

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CXXFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
