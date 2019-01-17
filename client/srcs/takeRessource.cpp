//
// EPITECH PROJECT, 2018
// takeRessource
// File description:
// take ressource from the ma
//

#include <unistd.h>
#include <string.h>
#include "Ia.hpp"

void	Ia::takeFood()
{
	std::string   str;

	std::cout << "Take food" << std::endl;
	write(this->_fd, "Take food\n", strlen("Take food\n"));
	str = this->serverRead();
	this->_food += 1;
}

void	Ia::takeLinemate()
{
	std::string	str;

	std::cout << "Take linemate" << std::endl;
	write(this->_fd, "Take linemate\n", strlen("Take linemate\n"));
	str = this->serverRead();
	this->_linemate += 1;
}

void	Ia::takeDeraumere()
{
	std::string	str = "";

	std::cout << "Take deraumere" << std::endl;
	write(this->_fd, "Take deraumere\n", strlen("Take deraumere\n"));
	str = this->serverRead();
	this->_deraumere += 1;
}

void	Ia::takeSibur()
{
	std::string	str = "";
	
	std::cout << "Take sibur" << std::endl;
	write(this->_fd, "Take sibur\n", strlen("Take sibur\n"));
	str = this->serverRead();
	this->_sibur += 1;
}

void	Ia::takeMendiane()
{
	std::string	str = "";
	
	std::cout << "Take mendiane" << std::endl;
	write(this->_fd, "Take mendiane\n", strlen("Take mendiane\n"));
	str = this->serverRead();
	this->_mendiane += 1;
}

void	Ia::takePhiras()
{
	std::string	str = "";
	
	std::cout << "Take phiras" << std::endl;
	write(this->_fd, "Take phiras\n", strlen("Take phiras\n"));
	str = this->serverRead();
	this->_phiras += 1;
}

void	Ia::takeThystame()
{
	std::string	str = "";
	
	std::cout << "Take thystame" << std::endl;
	write(this->_fd, "Take thystame\n", strlen("Take thystame\n"));
	str = this->serverRead();
	this->_thystame += 1;
}

void	Ia::setLinemate()
{
	std::cout << "Set linemate" << std::endl;
	write(this->_fd, "Set linemate\n", strlen("Set linemate\n"));
	this->serverRead();
	this->_linemate -= 1;	
}

void	Ia::setDeraumere()
{
	std::cout << "Set deraumere" << std::endl;
	write(this->_fd, "Set deraumere\n", strlen("Set deraumere\n"));
	this->serverRead();
	this->_deraumere -= 1;
}

void	Ia::setSibur()
{
	std::cout << "Set sibur" << std::endl;
	write(this->_fd, "Set sibur\n", strlen("Set sibur\n"));
	this->serverRead();
	this->_sibur -= 1;
}

void	Ia::setMendiane()
{
	std::cout << "Set mendiane" << std::endl;
	write(this->_fd, "Set mendiane\n", strlen("Set mendiane\n"));
	this->serverRead();
	this->_mendiane -= 1;
}

void	Ia::setPhiras()
{
	std::cout << "Set phiras" << std::endl;
	write(this->_fd, "Set phiras\n", strlen("Set phiras\n"));
	this->serverRead();
	this->_phiras -= 1;
}

void	Ia::setThystame()
{
	std::cout << "Set thystame" << std::endl;
	write(this->_fd, "Set thystame\n", strlen("Set thystame\n"));
	this->serverRead();
	this->_thystame -= 1;
}

void    Ia::setInventory(int food, int linemate, int deraumere, int sibur,
			     int mendiane, int phiras, int thystame)
{
	this->_linemate = linemate;
	this->_deraumere = deraumere;
	this->_sibur = sibur;
	this->_mendiane = mendiane;
	this->_phiras = phiras;
	this->_thystame = thystame;
	this->_food = food;
	std::cout << "Linemate : " << linemate << std::endl;
	std::cout << "Deraumere: " << deraumere << std::endl;
	std::cout << "Sibur    : " << sibur << std::endl;
	std::cout << "Mendiane : " << mendiane << std::endl;
	std::cout << "Phiras   : " << phiras << std::endl;
	std::cout << "Thystame : " << thystame << std::endl;
	std::cout << "Food     : " << food << std::endl << std::endl;
}
