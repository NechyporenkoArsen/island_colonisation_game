#include "LangMenu.h"
using namespace std;
using namespace sf;

LangMenu::LangMenu(Vector2f w, int pix){
	pixel = pix;
	loc loc(0);
	chosen = loc.l_num;
	loc_hov = {0, 0, 0};
	
	chosen_tex.loadFromFile("assets/textures/loc/chosen.png");
	UKR.loadFromFile("assets/textures/loc/UKR.png");
	ENG.loadFromFile("assets/textures/loc/ENG.png");
	PLN.loadFromFile("assets/textures/loc/PLN.png");
	
	chosen_spr = std::make_unique<Sprite>(chosen_tex);
	locs[0] = std::make_unique<Sprite>(ENG);
	locs[1] = std::make_unique<Sprite>(UKR);
	locs[2] = std::make_unique<Sprite>(PLN);
	
	for (int i = 0; i < 3; i++){
		locs[i]->setScale({ float(pix), float(pix) });
		locs[i]->setOrigin({ locs[i]->getLocalBounds().size.x / 2, locs[i]->getLocalBounds().size.y / 2 });
		locs[i]->setPosition({ float(w.x / 2 + (i - 1) * (locs[i]->getGlobalBounds().size.x * 1.4)), float(w.y / 2 - locs[i]->getGlobalBounds().size.y / 2) });
	}
	chosen_spr->setScale({ float(pix), float(pix) });
	chosen_spr->setOrigin({ chosen_spr->getLocalBounds().size.x / 2, chosen_spr->getLocalBounds().size.y / 2 });
	chosen_spr->setPosition( locs[chosen]->getPosition() );
}

LangMenu::~LangMenu(){}

void LangMenu::clicked_on(int i){
	chosen = i;
	chosen_spr->setPosition( locs[chosen]->getPosition() );
	i = 0;
	string input = "", line;
	ifstream r_l("localisations.txt");
	while (std::getline(r_l, line)) {
		if (line[0] != '>') {
			if (i == chosen) {
				input += ">";
			}
			input += line;
		}
		else {
			input += line.substr(1);
		}
		input += "\n";
		i++;
	}
	r_l.close();
	
	ofstream w_l("localisations.txt");
	w_l << input;
	w_l.close();
}

void LangMenu::update_lang(RenderWindow& win){
	for (int i = 0; i < 3; i++) {
		// BTT_HOVER
		// 0 - was unhovered; 1 - was hovered; 2 - got unhovered; 3 - got hovered

		if (loc_hov[i] == 3) {
			if (i == chosen) chosen_spr->setScale({ float(pixel * 1.2), float(pixel * 1.2) });
			locs[i]->setScale({ float(pixel * 1.2), float(pixel * 1.2) });
		}
		else if (loc_hov[i] == 2) {
			if (i == chosen) chosen_spr->setScale({ float(pixel), float(pixel) });
			locs[i]->setScale({ float(pixel), float(pixel) });
		}

		if (locs[i]->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(win))))
		{
			if (loc_hov[i] == 0 || loc_hov[i] == 2)
			{
				loc_hov[i] = 3;
			}
			else if (loc_hov[i] == 3)
			{
				loc_hov[i] = 1;
			}
		}
		else
		{
			if (loc_hov[i] == 2)
			{
				loc_hov[i] = 0;
			}
			else if (loc_hov[i] == 1 || loc_hov[i] == 3)
			{
				loc_hov[i] = 2;
				if (loc_cl[i] == 1) {
					loc_cl[i] = 3;
				}
			}
		}
	}
}

void LangMenu::render_lang(RenderWindow& win){
	for (int i = 0; i < 3; i++){
		win.draw(*locs[i]);
	}
	win.draw(*chosen_spr);
}