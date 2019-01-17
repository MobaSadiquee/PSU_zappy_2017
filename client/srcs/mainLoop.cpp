//
// EPITECH PROJECT, 2018
// loop.cpp
// File description:
// main loop for the ai
//

#include "Ia.hpp"
#include "Client.hpp"

void            Ia::levelUp()
{
	std::string     mess = "";

	std::cout << "Mon level actuel -> " << this->_level << std::endl;
	if (this->_linemate >= 1 && _level == 1)
		levelOne(mess);
	if (this->_linemate >= 1 && this->_deraumere >= 1
	    && this->_sibur >= 1 && this->_level == 2)
		levelTwo(mess);
	if (_linemate >= 2 && _sibur >= 1 && _phiras >= 2 && _level == 3)
		levelThree(mess);
}

void	Client::eat() const
{
	if (this->_ia->lookRessource(0, 0) != 0)
		this->_ia->takeFood();
	if (this->_ia->lookRessource(0, 1) != 0)
		this->_ia->takeLinemate();
	if (this->_ia->lookRessource(0, 2) != 0)
		this->_ia->takeDeraumere();
	if (this->_ia->lookRessource(0, 3) != 0)
		this->_ia->takeSibur();
	if (this->_ia->lookRessource(0, 4) != 0)
		this->_ia->takeMendiane();
	if (this->_ia->lookRessource(0, 5) != 0)
		this->_ia->takePhiras();
	if (this->_ia->lookRessource(0, 6) != 0)
		this->_ia->takeThystame();
}

int	Client::mainLoop()
{
	this->_ia->_help = false;
	this->_ia->_eater = true;
	this->readServer();
	this->readServer();
	while (this->_ia->getDead() == 0) {
		if (this->_ia->_eater == true) {
			this->_ia->look();
			while (this->_ia->lookCase(0) != 0 && this->_ia->_eater == true) {
				this->eat();
				this->_ia->look();
			}
			if (this->_ia->_eater == false)
				continue ;
			this->_ia->inventoryFunc();
			this->_ia->levelUp();
			this->_ia->eaterMode();
		}
		if (this->_ia->_help == true) {
			this->_ia->checkHelper();
		}
		if (this->_ia->_needHelp == true)
			this->_ia->levelUp();
	}
	return 0;
}
