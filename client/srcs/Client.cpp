//
// EPITECH PROJECT, 2018
// zappy
// File description:
// CLient member functions
//

#include "Client.hpp"

static int	checkArg(char *arg, Argument type,
			 std::map<Argument, std::string> &args)
{
	std::size_t	found;

	if (arg == NULL)
		return -1;
	if (type == PORT) {
		found = std::string(arg).find_first_not_of("0123456789");
		if (found != std::string::npos) {
			std::cout << "Error: Port can only contain digits."
				  << std::endl;
			return -1;
		}
	}
	args[type] = std::string(arg);
	return 0;
}

static int	checkLetter(char *arg)
{
	if (arg[1] == 'p')
		return 0;
	else if (arg[1] == 'n')
		return 1;
	else if (arg[1] == 'h')
		return 2;
	else
		return -1;
	return 0;
}

static void	displayHelp()
{
	std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
	std::cout << "\tport\tis the port number" << std::endl;
	std::cout << "\tname\tisthe name of the team" << std::endl;
	std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
}

int	checkArgs(int ac, char **av,
		  std::map<Argument, std::string> &args)
{
	int	returnLetter = -1;

	if (ac != 7 || (ac == 2 && std::string(av[1]) == "-help")) {
		displayHelp();
		return -1;
	}
	for (unsigned int i = 0; av[i] != NULL; i++) {
		if (av[i][0] == '-') {
			returnLetter = checkLetter(av[i]);
			if (returnLetter == -1)
				return -1;
			else
				if (checkArg(av[i + 1], (Argument)returnLetter, args) == -1)
					return -1;
		}
	}
	return 0;
}

Client::Client()
{
	_port = "8080";
	_name = "Team";
	_machine = "localhost";
	_fd = -1;
	_ia = NULL;
	FD_ZERO(&rd);
}

Client::~Client()
{
	delete _ia;
}

std::string	Client::getPort() const
{
	return _port;
}

std::string	Client::getName() const
{
	return _name;
}

std::string	Client::getMachine() const
{
	return _machine;
}

int	Client::getFd() const
{
	return _fd;
}

Ia	*Client::getIa() const
{
	return _ia;
}

void	Client::setArgs(std::map<Argument, std::string> &args)
{
	if (args.find(PORT) != args.end() && args.find(NAME) != args.end()
	    && args.find(MACHINE) != args.end()) {
		_port = args[PORT];
		_name = args[NAME];
		_machine = args[MACHINE];
	}
}

int	Client::connection()
{
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
	_fd = sock;
	_ia = new Ia(_fd);
	FD_SET(_fd, &rd);
	std::cout << "Connection success." << std::endl;
	return 0;
}

std::string	Client::readServer()
{
	std::string	answer;
	struct timeval	tv;

	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (select(FD_SETSIZE, &rd, NULL, NULL, &tv) > 0) {
		if (FD_ISSET(_fd, &rd)) {
			answer = _ia->serverRead();
			if (answer == "WELCOME\n")
				write(_fd, (_name + "\n").c_str(), _name.size() + 1);
		}
	}
	return answer;
}

std::ostream&	operator<<(__attribute__((unused))std::ostream &stream,
			   const Client& client)
{
	std::cout << "Port: " << client.getPort() << std::endl;
	std::cout << "Team name: " << client.getName() << std::endl;
	std::cout << "Machine name: " << client.getMachine() << std::endl;
	std::cout << "Server fd: " << client.getFd() << std::endl;
	return stream;
}
