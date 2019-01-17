//
// EPITECH PROJECT, 2018
// zappy
// File description:
// main class for graphics
//

#include "Spectator.hpp"

int	main(int ac, char **av)
{
	Spectator	client(ac == 4 ? std::stoi(std::string(av[1]), NULL) : -1,
			       ac == 4 ? std::stoi(std::string(av[2]), NULL) : -1,
			       ac == 4 ? std::string(av[3]) : "");

	if (client.getSize().x == -1 || client.getSize().y == -1)
		return -1;
	if (client.connection() == -1)
		return -1;
	client.setWindow();
	while (client.getWindow().isOpen()) {
		client.handleEvent();
		client.clear();
		client.draw(client.getSize().x, client.getSize().y);
		client.parseMap();
		client.getPlayers();
		client.display();
	}
	close(client.getFD());
	return 0;
}
