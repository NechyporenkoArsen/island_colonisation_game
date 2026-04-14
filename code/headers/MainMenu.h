#pragma once
#include "loc.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <map>
using namespace std;
using namespace sf;

class MainMenu{
public:
	MainMenu(Vector2f w, int pix, loc& lc);
	~MainMenu();
	void render(RenderWindow& win),
		update(RenderWindow& win);
	char clicked;
	std::array<char, 3> btt_hov,
		btt_cl;
private:
	int pixel_size;
	Font dec_font;
	char menu_page;
	// Functions
	void clicked_on(int i);
	// Textures & Sprites
	Texture water,
		btt,
		btt_prs;
	std::unique_ptr<Sprite> bg,
		btt_menu[3];
	// Texts, Fonts & Localisation
	loc& lc;
	std::unique_ptr<Text> btt_txt[3];
};