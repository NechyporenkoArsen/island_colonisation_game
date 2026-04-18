#pragma once
#include "loc.h"
#include "LangMenu.h"
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
	MainMenu(RenderWindow& window, Vector2f w, int pix, loc& lc);
	~MainMenu();
	void render(),
		update();
	char clicked,
		menu_page;
private:
	std::array<char, 3> btt_hov,
		btt_cl;
	std::unique_ptr<LangMenu> langMenu;
	Vector2f win_size;
	RenderWindow& win;
	int pixel_size,
		n_btt;
	Font dec_font;
	// Functions
	void clicked_on(int i),
		change_page_to(char i);
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