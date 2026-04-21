#include "GameWin.h"
using namespace std;
using namespace sf;

std::array<int, 3> id;
std::array<unsigned int, 3> px;

void GameWin::id2px() {
	px = {};
	for (char y = 0; y < 3; y++) {
		for (char x = 0; x < 3; x++) {
			px[y] += Mid2px[y][x] * id[x];
		}
	}
}

void GameWin::gen_map_t_layer() {
	I_def = T_def.copyToImage();
	for (char y = 0; y < grid_size; y++) {
		for (char x = 0; x < grid_size; x++) {
			id = {x, y, 1};
			id2px();
			map_t_layer_image.copy(I_def, {px[0], px[1]}, sf::IntRect({0, 0}, {32, 32}), true);
		}
	}
	terrain_map_tex.loadFromImage(map_t_layer_image);
	map_terrain_layer = std::make_unique<Sprite>(terrain_map_tex);
}