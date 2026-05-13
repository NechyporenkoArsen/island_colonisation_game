#include "GameWin.h"
using namespace std;
using namespace sf;

GameWin::GameWin(RenderWindow& w, int p, Vector2f s, View c) : win(w), pix(p), winSize(s), camera(c) {}

GameWin::~GameWin() {}

void GameWin::enter_game() {
	srand(time(NULL));
	Mid2px[0] = {-16, 16, float(16 * (float(grid_size) - float(1)))};
	Mid2px[1] = {8, 8, 0};
	Mid2px[2] = {0, 0, 1};
	
	//
	for (int i = 0; i < 19; i++) T_def[i].loadFromFile("assets/textures/tiles/def-112.png");
	T_def[0].loadFromFile("assets/textures/tiles/def-000.png");
	T_def[1].loadFromFile("assets/textures/tiles/def-001.png");
	T_def[2].loadFromFile("assets/textures/tiles/def-002.png");
	T_def[3].loadFromFile("assets/textures/tiles/def-011.png");
	T_def[4].loadFromFile("assets/textures/tiles/def-012.png");
	T_def[5].loadFromFile("assets/textures/tiles/def-022.png");
	T_def[6].loadFromFile("assets/textures/tiles/def-101.png");
	T_def[7].loadFromFile("assets/textures/tiles/def-102.png");
	T_def[8].loadFromFile("assets/textures/tiles/def-111.png");
	T_def[9].loadFromFile("assets/textures/tiles/def-112.png");
	T_def[10].loadFromFile("assets/textures/tiles/def-113.png");
	T_def[11].loadFromFile("assets/textures/tiles/def-122.png");
	T_def[12].loadFromFile("assets/textures/tiles/def-123.png");
	T_def[13].loadFromFile("assets/textures/tiles/def-202.png");
	T_def[14].loadFromFile("assets/textures/tiles/def-212.png");
	T_def[15].loadFromFile("assets/textures/tiles/def-213.png");
	T_def[16].loadFromFile("assets/textures/tiles/def-222.png");
	T_def[17].loadFromFile("assets/textures/tiles/def-223.png");
	T_def[18].loadFromFile("assets/textures/tiles/def-224.png");
	//
	I_def["000"] = T_def[0].copyToImage();
	I_def["001"] = T_def[1].copyToImage();
	I_def["002"] = T_def[2].copyToImage();
	I_def["011"] = T_def[3].copyToImage();
	I_def["012"] = T_def[4].copyToImage();
	I_def["022"] = T_def[5].copyToImage();
	I_def["101"] = T_def[6].copyToImage();
	I_def["102"] = T_def[7].copyToImage();
	I_def["111"] = T_def[8].copyToImage();
	I_def["112"] = T_def[9].copyToImage();
	I_def["113"] = T_def[10].copyToImage();
	I_def["122"] = T_def[11].copyToImage();
	I_def["123"] = T_def[12].copyToImage();
	I_def["202"] = T_def[13].copyToImage();
	I_def["212"] = T_def[14].copyToImage();
	I_def["213"] = T_def[15].copyToImage();
	I_def["222"] = T_def[16].copyToImage();
	I_def["223"] = T_def[17].copyToImage();
	I_def["224"] = T_def[18].copyToImage();
	//
	
	gen_map();
	map_terrain_layer->setScale({float(pix), float(pix)});
	map_terrain_layer->setOrigin({map_terrain_layer->getLocalBounds().size.x / 2, map_terrain_layer->getLocalBounds().size.y / 2});
	map_terrain_layer->setPosition({winSize.x / 2, winSize.y / 2});
}

void GameWin::render() {
	win.setView(camera);
	deltaTime = deltaTimeClock.restart();
	win.draw(*map_terrain_layer);
}