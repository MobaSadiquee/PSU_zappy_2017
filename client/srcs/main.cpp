//
// EPITECH PROJECT, 2018
// zappy
// File description:
// main function for AI clients
//

#include <csignal>
#include "Client.hpp"

void	signalHandler(__attribute__((unused))int signal)
{

}

int	main(int ac, char **av)
{
	Client	ai;
	std::map<Argument, std::string> args;

	std::signal(SIGPIPE, signalHandler);
	if (checkArgs(ac, av, args) == -1)
		return -1;
	ai.setArgs(args);
	std::cout << ai;
	if (ai.connection() == -1)
		return -1;
	ai.readServer();
	ai.mainLoop();
	return 0;
}
