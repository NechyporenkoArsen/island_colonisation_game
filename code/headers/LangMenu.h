#pragma once
#include "loc.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <istream>
#include <fstream>
using namespace std;
using namespace sf;

class LangMenu{
public:
	LangMenu(Vector2f win, int pix);
	~LangMenu();
	void update_lang(RenderWindow& win),
		render_lang(RenderWindow& win),
		clicked_on(int i);
	std::array<char, 3> loc_hov,
		loc_cl;
	char chosen;
	std::unique_ptr<Sprite> locs[3],
		chosen_spr;
private:
	int pixel;
	Texture chosen_tex,
		UKR,
		ENG,
		PLN;
};