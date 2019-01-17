//
// EPITECH PROJECT, 2018
// zappy
// File description:
// spectator class for graphic
//

#include "Spectator.hpp"

static std::vector<std::string> str_to_wordtab(std::string str)
{
	std::vector<std::string> tab;
	int	size;

	size = str.find(" ");
	tab.push_back(str.substr(0, size));
	size += 1;
	tab.push_back(str.substr(size, str.find(" ", size) - size));
	size = str.find(" ", size) + 1;
	tab.push_back(str.substr(size, str.find(" ", size) - size));
	size = str.find(" ", size) + 1;
	tab.push_back(str.substr(size, str.find(" ", size) - size));
	size = str.find(" ", size) + 1;
	tab.push_back(str.substr(size, str.find("\n", size) - size));
	return tab;
}

Spectator::Spectator(int x, int y, std::string port)
{
	mapSize.x = x;
	mapSize.y = y;
	_port = port;
}

Spectator::~Spectator()
{}

const int	&Spectator::getFD() const
{
	return serverFD;
}

const size	&Spectator::getSize() const
{
	return mapSize;
}

int	Spectator::connection()
{
	char		answer[1024];
	struct sockaddr_in	serv_addr;
	int	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0) {
		std::cout << "Socket creation error." << std::endl;
		return -1;
	}
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(std::stoi(_port, NULL));
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		std::cout << "Invalid address / Address not supported." << std::endl;
		return -1;
	}
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "Connection failed." << std::endl;
		return -1;
	}
	serverFD = sock;
	std::cout << "Connection success." << std::endl;
	read(serverFD, answer, 1024);
	write(serverFD, "spectator\n", strlen("spectator\n"));
	return 0;
}

void	Spectator::parseMap()
{
	std::string	mapCom("Map " + std::to_string(1)  + "/" + std::to_string(1) + "\n");
	int	i = 0;
	int	y = 0;

	while (i < mapSize.x) {
		while (y < mapSize.y) {
			getMap(std::string("Map " + std::to_string(i) + "/" +
					   std::to_string(y) + "\n"), i, y);
			y++;
		}
		y = 0;
		i++;
	}
}

void	Spectator::getMap(const std::string &mapCom, int x, int y)
{
	char	buffer[4096] = {0};
	std::string	answer;
	unsigned int	size = 0;
	unsigned int	otherSize = 0;

	write(serverFD, mapCom.c_str(), mapCom.size());
	read(serverFD, buffer, 4096);
	while (size <= std::string(buffer).size() - 1) {
		answer = std::string(buffer).substr(size, std::string(buffer).find("\n", size) - size);
		size = std::string(buffer).find("\n", size) + 1;
		otherSize = answer.find(" ") + 1;
		if (std::stoi(answer.substr(otherSize, answer.find("\n", otherSize) - otherSize), NULL) > 0)
			drawObj(x, y, answer.substr(0, answer.find(" ")));
		answer.clear();
	}
}

void	Spectator::getPlayers()
{
	char	buffer[4096] = {0};
	std::string	answer;
	unsigned int	size = 0;
	std::vector<std::string> player;

	write(serverFD, "Players\n", 8);
	read(serverFD, buffer, 4096);
	if (std::string(buffer) != "No Players\n") {
		while (size <= std::string(buffer).size() - 1) {
			answer = std::string(buffer).substr(size, std::string(buffer).find("\n", size) - size);
			size = std::string(buffer).find("\n", size) + 1;
			player = str_to_wordtab(answer);
			drawPlayer(std::stoi(player[1]), std::stoi(player[2]), "Player" + player[0] + player[3], std::stoi(player[4]));
		}
	}
}
