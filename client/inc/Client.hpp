
//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Client header class
//

#ifndef CLIENT_HPP_
# define CLIENT_HPP_

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "Ia.hpp"

enum Argument
{
	PORT,
	NAME,
	MACHINE
};

int	checkArgs(int ac, char **av,
		  std::map<Argument, std::string> &args);

class Client
{
public:
	Client();
	~Client();

	std::string	getPort() const;
	std::string	getName() const;
	std::string	getMachine() const;
	int		getFd() const;
	Ia		*getIa() const;
	
	void	setArgs(std::map<Argument, std::string> &args);
	int	connection();
	std::string	readServer();
	int	mainLoop();
	int	inventory();
	void	getBroadcast(std::string);
	void	eat() const;

private:
	std::string	_port;
	std::string	_name;
	std::string	_machine;
	int		_fd;
	Ia		*_ia;
	fd_set		rd;
};

std::ostream&	operator<<(std::ostream &stream, const Client& client);

#endif /* CIENT_HPP_ */
