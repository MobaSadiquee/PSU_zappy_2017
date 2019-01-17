//
// EPITECH PROJECT, 2018
// Ia.cpp
// File description:
// Ia main class function
//

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "Ia.hpp"

Ia::Ia(int fd)
{
	this->_level = 1;
	this->_fd = fd;
	this->_dead = 0;

	this->_linemate = 0;
	this->_deraumere = 0;
	this->_sibur = 0;
	this->_mendiane = 0;
	this->_phiras = 0;
	this->_thystame = 0;
	this->_food = 0;

	this->_nbPlayer = 0;
	this->_eater = true;
	this->_help = false;
	this->_needHelp = false;
	this->_direction = 0;
}

Ia::~Ia()
{
}

int     Ia::getDead() const
{
	return (this->_dead);
}

std::vector<std::string>	Ia::getStack() const
{
	return _stack;
}

int      extractIntegerWords(std::string str)
{
	std::stringstream       ss;

	ss << str;
	std::string temp;
	int found;
	while (!ss.eof()) {
		ss >> temp;
		if (std::stringstream(temp) >> found)
			return found;
		temp = "";
	}
	return 0;
}

std::string	Ia::serverRead()
{
	char		buffer[4024] = {0};
	std::string	wrong = "ko\n";
	std::string	mess = "";

	read(_fd, buffer, 4024);
	this->_direction = 0;
	if ((strncmp("message", buffer, 7)) == 0) {
		this->_help = true;
		this->_eater = false;
		this->_direction = extractIntegerWords(std::string(buffer));
		std::cout << this->_direction << std::endl;
		read(_fd, buffer, 4024);
	}
	if (std::string(buffer) == "Elevation underway\n")
	{
		std::cout << "Server awnser : Elevation underway" << std::endl;
		while ((mess.substr(0, mess.find(":"))) != "Current level") {
			mess = this->serverRead();
			if (mess == "ko\n")
				break;
		}
		return (mess);
	}
	if (std::string(buffer) == "dead\n") {
		std::cout << "LOOSE" << std::endl;
		exit(0);
		return (NULL);
	}
	if (buffer == NULL)
		return (wrong);
	std::cout << "Server awnser : " << std::string(buffer) << std::endl;
	return (std::string(buffer));
}

void    Ia::forward()
{
	std::cout << "Forward" << std::endl;
	write(this->_fd, "Forward\n", strlen("Forward\n"));
	this->serverRead();
}

void    Ia::left()
{
	std::cout << "Left" << std::endl;
	write(this->_fd, "Left\n", strlen("Left\n"));
	this->serverRead();
}

void    Ia::right()
{
	std::cout << "Right" << std::endl;
	write(this->_fd, "Right\n", strlen("Right\n"));
	this->serverRead();
}

void	Ia::broadcastFunc(std::string str)
{
	std::string	mess = "Broadcast ";

	mess += str;
	mess += "\n";
	write(this->_fd, mess.c_str(), strlen(mess.c_str()));
	this->serverRead();
}

void	Ia::setIncantation()
{
	std::cout << "Incantation" << std::endl;
	write(this->_fd, "Incantation\n", strlen("Incantation\n"));
}

int	Ia::lookRessource(int i, int y) const
{
	return (this->_look[i][y]);
}

int	Ia::lookCase(int i) const
{
	int	found = 0;

	if (this->lookRessource(i, 0) != 0)
		found++;
	if (this->lookRessource(i, 1) != 0)
		found++;
	if (this->lookRessource(i, 2) != 0)
		found++;
	if (this->lookRessource(i, 3) != 0)
		found++;
	if (this->lookRessource(i, 4) != 0)
		found++;
	if (this->lookRessource(i, 5) != 0)
		found++;
	if (this->lookRessource(i, 6) != 0)
		found++;
	return (found);
}

void	Ia::lookHelp(int pos, std::string buffer)
{
	std::string		str;
	std::stringstream	str2;

	str2 << buffer;
	while (std::getline(str2, str, ' ') && pos <= 3)
	{
		if (str == "food")
			this->_look[pos][0]++;
		if (str == "linemate")
			this->_look[pos][1]++;
		if (str == "deraumere")
			this->_look[pos][2]++;
		if (str == "sibur")
			this->_look[pos][3]++;
		if (str == "mendiane")
			this->_look[pos][4]++;
		if (str == "phiras")
			this->_look[pos][5]++;
		if (str == "thystame")
			this->_look[pos][6]++;
		if (str == "player" && pos == 0)
			this->_nbPlayer++;
	}
}

int	Ia::look()
{
	std::string		str;
	std::stringstream	str2;
	std::string		buffer;
	int			pos = 0;
	int                     i = 0;
	
        this->_nbPlayer = 0;	
	std::cout << "Look" << std::endl;
	write(this->_fd, "Look\n", strlen("Look\n"));
	str = this->serverRead();
	if (str == "ko\n" || str == "ok\n")
		return -1;
	str2 << str;
	while (std::getline(str2, buffer, ','))
	{
		while (i <= 6)
		{
			this->_look[pos][i] = 0;
			i = i + 1;
		}
		lookHelp(pos, buffer);
		pos = pos + 1;
	}
	return 0;
}

int     Ia::inventoryFunc()
{
	int                     x = 0;
	int                     y = 0;
	std::string             str = "";
	std::stringstream       stream;
	std::string             buffer;
	int                     ressource[7];

	std::cout << "Inventory" << std::endl;
	write(this->_fd, "Inventory\n", strlen("Inventory\n"));
	str = this->serverRead();
	if (str == "ko\n" || str == "ok\n")
		return -1;
	str.erase(0, 2);
	str.erase(str.length() - 1, 1);
        if (str == "player")
		return -1;
	stream << str;
	while (std::getline(stream, buffer, ' '))
	{
		if ((x % 2) == 1)
		{
			ressource[y] = atoi(buffer.c_str());
			y++;
		}
		x++;
	}
	this->setInventory(ressource[0], ressource[1], ressource[2], ressource[3],
			   ressource[4], ressource[5], ressource[6]);
	return 0;
}
