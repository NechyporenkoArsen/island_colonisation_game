#pragma once
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameWin{
public:
	GameWin(sf::RenderWindow& window, int pixel);
	~GameWin();
	void render(),
		update();
	char clicked;
private:
	int pix;
	unsigned int grid_size;
	sf::RenderWindow& win;
	void gen_map_t_layer(),
		id2px();
	sf::Texture T_def,
		terrain_map_tex;
	sf::Image map_t_layer_image,
		I_def;
	std::unique_ptr<sf::Sprite> map_terrain_layer;
	std::array<std::array<int, 3>, 3> Mid2px;
};