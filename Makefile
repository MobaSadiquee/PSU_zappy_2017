##
## EPITECH PROJECT, 2018
## zappy
## File description:
## main Makefile
##

all: server client graph

server:
	make -C ./server/

client:
	make -C ./client/

graph:
	make -C ./client/graph/

clean:
	make -C ./server/ clean
	make -C ./client/ clean
	make -C ./client/graph clean

fclean:
	make -C ./server/ fclean
	make -C ./client/ fclean
	make -C ./client/graph fclean

re: fclean all

.PHONY: all server client graph clean fclean re
