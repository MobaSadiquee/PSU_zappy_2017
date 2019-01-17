//
// EPITECH PROJECT, 2018
// zappy
// File description:
// spectator class for graphic
//

#ifndef SPECTATOR_HPP_
# define SPECTATOR_HPP_

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include "GraphSFML.hpp"

class Spectator : public GraphSFML
{
public:
	Spectator(int x, int y, std::string port);
	~Spectator();

	const int	&getFD() const;
	const size	&getSize() const;
	int	connection();
	void	parseMap();
	void	getPlayers();

private:
	void	getMap(const std::string &mapCom, int x, int y);

	size	mapSize;
	int	serverFD;
	std::string	_port;
};

#endif /* SPECTATOR_HPP_ */
