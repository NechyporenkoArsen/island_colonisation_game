#pragma once
extern "C" {
    #include <sqlite3.h>
}
#include <iostream>
#include <array>
#include <vector>
#include <bit>
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class GameWin{
public:
	GameWin(sf::RenderWindow& window, int pixel, sf::Vector2f window_size, sf::View camera);
	~GameWin();
	void render(),
		update(),
		enter_game();
	char clicked;
private:
	sf::View camera;
    sqlite3* mapDB = nullptr;
	sf::Clock deltaTimeClock;
	sf::Time deltaTime;
	sf::Vector2f winSize;
	int pix;
	static constexpr unsigned int grid_size = 100;
	std::array<std::array<int, int(grid_size) + 1>, int(grid_size) + 1> grid_peaks;
	sf::RenderWindow& win;
	void gen_map(),
		gen_map_t(),
		gen_map_t_layer(),
		soft(int x, int y);
	std::string get_tilt(int y, int x);
	sf::Vector2u id2px(sf::Vector2u id);
	sf::Texture terrain_map_tex;
	std::array<sf::Texture, 19> T_def;
	sf::Image map_t_layer_image;
	std::map<std::string, sf::Image> I_def;
	std::unique_ptr<sf::Sprite> map_terrain_layer,
		hovered_tile;
	std::array<std::array<float, 3>, 3> Mid2px;
};