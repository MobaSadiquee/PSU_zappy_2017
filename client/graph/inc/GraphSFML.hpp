//
// EPITECH PROJECT, 2018
// zappy
// File description:
// class to use SFML
//

#ifndef GRAPHSFML_HPP_
# define GRAPHSFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>

struct size
{
	int x;
	int y;
};

class GraphSFML
{
public:
	GraphSFML();
	~GraphSFML();

	const sf::RenderWindow	&getWindow() const;
	void	setWindow();
	void	handleEvent();
	void	clear();
	void	draw(int x, int y);
	void	display();
	void	drawObj(int x, int y, std::string obj);
	void	drawPlayer(int x, int y, std::string player, int lvl);

private:
	void	keyboardEvent(sf::Event &event);
	void	mouseEvent(sf::Event &event);
	void	handleMousePos();
	int	drawFloor(std::string textName, int sizeX, int sizeY);
	int	setTextures();
	void	setObjPos();

	const std::string	assetsPath = "./assets/";
	sf::View		view;
	sf::RenderWindow	window;
	sf::Vector2f		viewPos;
	sf::Shader		shader;
	sf::Clock		clock;
	sf::Texture		textShader;
	sf::Sprite		spriteShader;
	sf::Music		music;
	std::map<std::string, sf::Texture>	textures;
	std::map<std::string, size>		objPos;
};

#endif /* GRAPHSFML_HPP_ */
