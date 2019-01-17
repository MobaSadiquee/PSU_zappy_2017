//
// EPITECH PROJECT, 2018
// Ia.hpp
// File description:
// Ia header
//

#ifndef         _IA_HPP_
# define        _IA_HPP_

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

class   Ia
{
public:
	Ia(int);
	~Ia();

	std::string	serverRead();
	void		forward();
	void		left();
	void		right();
	int		lookCase(int) const;
	int		lookRessource(int, int) const;
	int		look();
	void            lookHelp(int, std::string);
	int		getDead() const;
	int		inventoryFunc();
	void		broadcastFunc(std::string);
	int		setLevel();
	void		setIncantation();
	void		checkHelper();
	void		eaterMode();
	std::vector<std::string>	getStack() const;

	void            levelUp();
	void            levelOne(std::string str);
	void		levelTwo(std::string str);
	void		levelThree(std::string str);
	
	void		takeFood();
	void		takeLinemate();
	void		takeDeraumere();
	void		takeSibur();
	void		takeMendiane();
	void		takePhiras();
	void		takeThystame();

	void		setLinemate();
	void		setDeraumere();
	void		setSibur();
	void		setMendiane();
	void		setPhiras();
	void		setThystame();
	void		setInventory(int, int, int, int, int, int, int);

	int             _nbPlayer;
	bool            _eater;
	bool		_help;
	bool		_needHelp;
	int		_direction;
private:

	int             _fd;
	int		_level;
	int		_dead;
	int		_look[4][7];
	std::vector<std::string>	_stack;

	int		_linemate;
	int		_deraumere;
	int		_sibur;
	int		_mendiane;
	int		_phiras;
	int		_thystame;
	int		_food;
};

#endif		/* !_IA_HPP_ */
