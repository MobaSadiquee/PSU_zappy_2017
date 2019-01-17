//
// EPITECH PROJECT, 2018
// think.cpp
// File description:
// think algo
//

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "Ia.hpp"

void    Ia::eaterMode()
{
	int     i = 0;
	int     choice;

	srand(time(NULL));
	choice = rand() % 2 + 1;
	if(_eater == true && choice == 1) {
		i = lookCase(1);
		if (i != 0) {
			this->forward();
			this->left();
			this->forward();
			return ;
		}
		i = lookCase(2);
		if (i != 0) {
			this->forward();
			return ;
		}
		i = lookCase(3);
		if (i != 0) {
			this->forward();
			this->right();
			this->forward();
			return ;
		}
		forward();
	}
	if(_eater == true && choice == 2) {
		i = lookCase(3);
		if (i != 0) {
			this->forward();
			this->right();
			this->forward();
			return ;
		}
		i = lookCase(2);
		if (i != 0) {
			this->forward();
			return ;
		}
		i = lookCase(1);
		if (i != 0) {
			this->forward();
			this->left();
			this->forward();
			return ;
		}
		forward();
	}
}

void    Ia::checkHelper()
{
	if (_direction == 0) {
		sleep(10);
		_eater = true;
		_help = false;
	}
	if (_direction == 1)
		forward();
	if (_direction == 2) {
		forward();
		left();
	}
	if (_direction == 3) {
		left();
		forward();
	}
	if (_direction == 4) {
		left();
		forward();
		left();
		forward();
	}
	if (_direction == 5) {
		left();
		left();
		forward();
		
	}
	if (_direction == 6) {
		right();
		forward();
		right();
	}
	if (_direction == 7) {
		right();
		forward();
	}
	if (_direction == 8) {
		forward();
		right();
	}
}

void		Ia::levelOne(std::string str)
{
	this->setLinemate();
	this->setIncantation();
	str = this->serverRead();
	if (str == "Current level: 2\n")
	{
		this->_level++;
		this->_eater = true;
		this->_needHelp = false;
		return ;
	}
	this->takeLinemate();
}

void		Ia::levelTwo(std::string str)
{
	if (_nbPlayer != 2)
	{
		this->_eater = false;
		this->_needHelp = true;
		this->look();
		if (this->lookCase(0) != 0)
			if (this->lookRessource(0, 0) != 0)
				this->takeFood();
		std::cout << "Broadcast" << std::endl;
		sleep(3);
		this->broadcastFunc("Help");
	}
	else
	{
		this->setLinemate();
		this->setDeraumere();
		this->setSibur();
		this->setIncantation();
		str = this->serverRead();
		if (str == "Current level: 3\n")
		{
			this->_level += 1;
			this->_eater = true;
			this->_needHelp = false;
			return ;
		}
		else if (str == "ko\n")
			this->_nbPlayer -= 1;
		this->takeLinemate();
		this->takeDeraumere();
		this->takeSibur();
		return ;
	}
}

void            Ia::levelThree(std::string str)
{
	if (_nbPlayer != 2) {
		_eater = false;
		this->_needHelp = true;
		look();
		if (lookCase(0) != 0) {
			if (lookRessource(0, 0) != 0)
				takeFood();
			std::cout << "Broadcast" << std::endl;
			sleep(3);
			broadcastFunc("Help");
		}
		else {
			setLinemate();
			setLinemate();
			setSibur();
			setPhiras();
			setPhiras();
			str = this->serverRead();
			if (str == "Current level: 4\n") {
				_level++;
				_eater = true;
				this->_needHelp = false;
				return ;
			}
			else if (str == "ko\n")
				this->_nbPlayer -= 1;
			takeLinemate();
			takeLinemate();
			takeSibur();
			takePhiras();
			takePhiras();
		}
	}
}
