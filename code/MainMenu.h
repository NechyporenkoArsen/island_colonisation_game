#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
using namespace sf;

class MainMenu
{
public:
	MainMenu(Vector2f w, int pix);
	~MainMenu();
	void render(RenderWindow& win),
		update(RenderWindow& win);
	char clicked;
	std::array<char, 4> btt_hov,
		btt_cl;
private:
	int pixel_size,
		max_btt,
		min_btt;
	Font dec_font;
	char menu_page;
	// Functions
	void clicked_on(int i);
	// Textures & Sprites
	Texture water,
		btt,
		btt_prs;
	std::unique_ptr<Sprite> bg,
		btt_return,
		btt_menu[4];
	// Localisation & TEXT
	std::vector<std::string> lc;
	std::unique_ptr<Text> btt_main_txt[4];
};

