//
// EPITECH PROJECT, 2018
// zappy
// File description:
// GraphSFML member functions
//

#include "GraphSFML.hpp"

GraphSFML::GraphSFML()
{}

GraphSFML::~GraphSFML()
{}

const sf::RenderWindow	&GraphSFML::getWindow() const
{
	return window;
}

void	GraphSFML::setWindow()
{
	if (!music.openFromFile(assetsPath + "incarnam.ogg"))
		return;
	if (setTextures() == -1)
		return;
	setObjPos();
	if (!shader.loadFromFile(assetsPath + "background.frag", sf::Shader::Fragment))
		return;
	shader.setUniform("resolution", sf::Glsl::Vec2(1920, 1080));
	textShader.create(1920, 1080);
	spriteShader.setTexture(textShader);
	window.create(sf::VideoMode(1920, 1080), "Zappy");
	view.setCenter(0, 0);
	view.setSize(1920, 1080);
	viewPos.x = 0.f;
	viewPos.y = 0.f;
	music.play();
}

void	GraphSFML::handleEvent()
{
	sf::Event	event;

	window.setView(view);
	while (window.pollEvent(event)) {
		keyboardEvent(event);
		mouseEvent(event);
	}
	handleMousePos();
	
}

void	GraphSFML::clear()
{
	window.clear();
}

void	GraphSFML::draw(int x, int y)
{
	shader.setUniform("time", clock.getElapsedTime().asSeconds());
	spriteShader.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
	window.draw(spriteShader, &shader);
	if (drawFloor("text_grass.png", x, y) == -1)
		return;
}

void	GraphSFML::display()
{
	window.display();
}

void	GraphSFML::drawObj(int x, int y, std::string obj)
{
	sf::Sprite	sprite;
	float		posX = static_cast<float>(x);
	float		posY = static_cast<float>(y);

	sprite.setTexture(textures[obj]);
	sprite.setPosition(75 + posX * 75 + posY * (-75) + objPos[obj].x, 43.5 + posX * 43.5 + posY * 43.5 + objPos[obj].y);
	sprite.setOrigin(250, 250);
	sprite.setScale(0.025, 0.025);
	window.draw(sprite);
}

void	GraphSFML::drawPlayer(int x, int y, std::string obj, int lvl)
{
	sf::Sprite	sprite;
	float		posX = static_cast<float>(x);
	float		posY = static_cast<float>(y);

	sprite.setTexture(textures[obj]);
	sprite.setPosition(75 + posX * 75 + posY * (-75), 43.5 + posX * 43.5 + posY * 43.5);
	sprite.setOrigin((static_cast<float>(textures[obj].getSize().x) / 2.0f),
			 (static_cast<float>(textures[obj].getSize().y)));
	sprite.setScale(0.3 + static_cast<float>(lvl) / 10 / 2, 0.3 + static_cast<float>(lvl) / 10 / 2);
	window.draw(sprite);
}

void	GraphSFML::keyboardEvent(sf::Event &event)
{
	if (event.type == sf::Event::Closed)
		window.close();
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			window.close();
		if (event.key.code == sf::Keyboard::Up)
			viewPos.y -= 50;
		else if (event.key.code == sf::Keyboard::Down)
			viewPos.y += 50;
		else if (event.key.code == sf::Keyboard::Right)
			viewPos.x += 50;
		else if (event.key.code == sf::Keyboard::Left)
			viewPos.x -= 50;
		view.setCenter(viewPos);
		if (event.key.code == sf::Keyboard::PageUp) {
			view.zoom(0.9f);
		}
		if (event.key.code == sf::Keyboard::PageDown) {
			view.zoom(1.1f);
			spriteShader.setScale(800, 800);
		}
	}
}

void	GraphSFML::mouseEvent(sf::Event &event)
{
	if (event.type == sf::Event::MouseWheelScrolled) {
		if (event.mouseWheelScroll.delta < 0)
			view.zoom(1.1f);
		if (event.mouseWheelScroll.delta > 0)
			view.zoom(0.9f);
	}
	//if (event.type == sf::Event::MouseLeft) {
	//	sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(window).x, 0));
	//}
}

void	GraphSFML::handleMousePos()
{
	sf::Vector2i	pixelPos;

	pixelPos = sf::Mouse::getPosition(window);
	if (pixelPos.x <= 0) {
		viewPos.x -= 25;
		view.setCenter(viewPos);
	}
	if (pixelPos.y <= 10) {
		viewPos.y -= 25;
		view.setCenter(viewPos);
	}
	if (pixelPos.x >= 1900) {
		viewPos.x += 25;
		view.setCenter(viewPos);
	}
	if (pixelPos.y >= 1000) {
		viewPos.y += 25;
		view.setCenter(viewPos);
	}
}

int	GraphSFML::drawFloor(std::string textName, int sizeX, int sizeY)
{
	sf::Texture texture;
	sf::Sprite sprite;
	int i = 0;
	int y = 0;

 	if (!texture.loadFromFile(assetsPath + textName))
		return -1;
	sprite.setTexture(texture);
	sprite.setScale(0.1802f, 0.1802f);
	while (i < sizeX) {
		while (y < sizeY) {
			sprite.setPosition(y * 75 + i * (-75), y * 43.5 + i * 43.5);
			window.draw(sprite);
			y++;
		}
		i++;
		y = 0;
	}
	return 0;
}

int	GraphSFML::setTextures()
{
	sf::Texture	textLinemate;
	sf::Texture	textDeraumere;
	sf::Texture	textSibur;
	sf::Texture	textMendiane;
	sf::Texture	textPhiras;
	sf::Texture	textThystame;
	sf::Texture	textFood;

	if (!textLinemate.loadFromFile(assetsPath + "linemate.png"))
		return -1;
	if (!textDeraumere.loadFromFile(assetsPath + "deraumere.png"))
		return -1;
	if (!textSibur.loadFromFile(assetsPath + "sibur.png"))
		return -1;
	if (!textMendiane.loadFromFile(assetsPath + "mendiane.png"))
		return -1;
	if (!textPhiras.loadFromFile(assetsPath + "phiras.png"))
		return -1;
	if (!textThystame.loadFromFile(assetsPath + "thystame.png"))
		return -1;
	if (!textFood.loadFromFile(assetsPath + "food.png"))
		return -1;
	textures["Linemate"] = textLinemate;
	textures["Deraumere"] = textDeraumere;
	textures["Sibur"] = textSibur;
	textures["Mendiane"] = textMendiane;
	textures["Phiras"] = textPhiras;
	textures["Thystame"] = textThystame;
	textures["Food"] = textFood;
	textures["Player00"].loadFromFile(assetsPath + "player00.png");
	textures["Player01"].loadFromFile(assetsPath + "player01.png");
	textures["Player02"].loadFromFile(assetsPath + "player02.png");
	textures["Player03"].loadFromFile(assetsPath + "player03.png");
	textures["Player10"].loadFromFile(assetsPath + "player10.png");
	textures["Player11"].loadFromFile(assetsPath + "player11.png");
	textures["Player12"].loadFromFile(assetsPath + "player12.png");
	textures["Player13"].loadFromFile(assetsPath + "player13.png");
	textures["Player20"].loadFromFile(assetsPath + "player20.png");
	textures["Player21"].loadFromFile(assetsPath + "player21.png");
	textures["Player22"].loadFromFile(assetsPath + "player22.png");
	textures["Player23"].loadFromFile(assetsPath + "player23.png");
	textures["Player30"].loadFromFile(assetsPath + "player30.png");
	textures["Player31"].loadFromFile(assetsPath + "player31.png");
	textures["Player32"].loadFromFile(assetsPath + "player32.png");
	textures["Player33"].loadFromFile(assetsPath + "player33.png");
	textures["Player40"].loadFromFile(assetsPath + "player40.png");
	textures["Player41"].loadFromFile(assetsPath + "player41.png");
	textures["Player42"].loadFromFile(assetsPath + "player42.png");
	textures["Player43"].loadFromFile(assetsPath + "player43.png");
	return 0;
}

void	GraphSFML::setObjPos()
{
	objPos["Linemate"].x = -20;
	objPos["Linemate"].y = 0;
	objPos["Deraumere"].x = -40;
	objPos["Deraumere"].y = 0;
	objPos["Sibur"].x = 20;
	objPos["Sibur"].y = 0;
	objPos["Mendiane"].x = 40;
	objPos["Mendiane"].y = 0;
	objPos["Phiras"].x = 0;
	objPos["Phiras"].y = 20;
	objPos["Thystame"].x = 0;
	objPos["Thystame"].y = -20;
	objPos["Food"].x = 0;
	objPos["Food"].y = 0;
}
