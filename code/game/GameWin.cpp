#include "GameWin.h"
using namespace std;
using namespace sf;

GameWin::GameWin(RenderWindow& w, int p) : win(w), pix(p) {
	grid_size = 10;
	Mid2px = {{
		std::array<int,3>{-16, 16, 16 * (int(grid_size) - 1)},
		std::array<int,3>{8, 8, 0},
		std::array<int,3>{0, 0, 1}
	}};
	T_def.loadFromFile("assets/textures/tiles/def.png");
	map_t_layer_image.resize({32 * grid_size, 16 * (grid_size + 1)});
	gen_map_t_layer();
	map_terrain_layer->setScale({float(pix), float(pix)});
}

GameWin::~GameWin() {}

void GameWin::render() {
	win.clear();
	win.draw(*map_terrain_layer);
}