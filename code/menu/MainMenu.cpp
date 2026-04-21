#include "MainMenu.h"
using namespace std;
using namespace sf;

MainMenu::MainMenu(RenderWindow& window, Vector2f w, int pix, loc& lc) : lc(lc), win(window), win_size(w), pixel_size(pix) {
	clicked = 0;
	menu_page = 0;
	langMenu = std::make_unique<LangMenu>(win_size, pixel_size);
	dec_font.openFromFile("assets/fonts/RutheniaRadaFancy-Regular.ttf");
	btt_hov = {0, 0, 0};
	n_btt = 3;

	// Textures

	water.loadFromFile("assets/textures/water.jpg");
	btt.loadFromFile("assets/textures/menu_button.png");
	btt_prs.loadFromFile("assets/textures/menu_button_pressed.png");

	// Edit Textures

	water.setRepeated(true);

	// Load Sprites

	bg = std::make_unique<Sprite>(water);
	for (int i = 0; i < size(btt_menu); i++) {
		btt_menu[i] = std::make_unique<Sprite>(btt);
	}

	// Edit Sprites

	bg->setScale({ float(pixel_size), float(pixel_size) });
	bg->setTextureRect({ {0, 0}, {int(w.x), int(w.y)} });

	for (int i = 0; i < size(btt_menu); i++) {
		btt_menu[i]->setScale({ float(pixel_size), float(pixel_size) });
		btt_menu[i]->setOrigin({ btt_menu[i]->getLocalBounds().size.x / 2, btt_menu[i]->getLocalBounds().size.y / 2 });
		btt_menu[i]->setPosition({ w.x / 2, w.y / 2 + i * (btt_menu[i]->getGlobalBounds().size.y + 30)});
	}
	
	// Load Texts

	btt_txt[0] = std::make_unique<Text>(dec_font, String::fromUtf8(lc.menu_txt["btt_play"].begin(), lc.menu_txt["btt_play"].end()), 50);
	btt_txt[1] = std::make_unique<Text>(dec_font, String::fromUtf8(lc.menu_txt["btt_settings"].begin(), lc.menu_txt["btt_settings"].end()), 50);
	btt_txt[2] = std::make_unique<Text>(dec_font, String::fromUtf8(lc.menu_txt["btt_exit"].begin(), lc.menu_txt["btt_exit"].end()), 50);

	// Edit Texts

	for (int i = 0; i < n_btt; i++) {
		btt_txt[i]->setOrigin({ btt_txt[i]->getGlobalBounds().size.x / 2, btt_txt[i]->getGlobalBounds().size.y / 10 * 6 });
		btt_txt[i]->setPosition(btt_menu[i]->getPosition());
		btt_txt[i]->setFillColor(Color(0, 0, 0, 200));
	}
}

MainMenu::~MainMenu() {}

void MainMenu::change_page_to(char i) {
	///////////////////////////////////
	//
	// ===== menu_page =====
	// 
	// 0 main menu
	// 1 settings
	// 2 languages
	//
	///////////////////////////////////
	
	switch(i) {
		case 0: {
			menu_page = 0;
			n_btt = 3;
			btt_txt[0]->setString(String::fromUtf8(lc.menu_txt["btt_play"].begin(), lc.menu_txt["btt_play"].end()));
			btt_txt[1]->setString(String::fromUtf8(lc.menu_txt["btt_settings"].begin(), lc.menu_txt["btt_settings"].end()));
			btt_txt[2]->setString(String::fromUtf8(lc.menu_txt["btt_exit"].begin(), lc.menu_txt["btt_exit"].end()));			
			for (int i = 0; i < n_btt; i++) {
				btt_txt[i]->setOrigin({ btt_txt[i]->getGlobalBounds().size.x / 2, btt_txt[i]->getGlobalBounds().size.y / 10 * 6 });
			}
			break;
		}
		case 1: {
			menu_page = 1;
			n_btt = 2;
			btt_txt[0]->setString(String::fromUtf8(lc.menu_txt["btt_languages"].begin(), lc.menu_txt["btt_languages"].end()));		
			btt_txt[1]->setString(String::fromUtf8(lc.menu_txt["btt_return"].begin(), lc.menu_txt["btt_return"].end()));
			for (int i = 0; i < n_btt; i++) {
				btt_txt[i]->setOrigin({ btt_txt[i]->getGlobalBounds().size.x / 2, btt_txt[i]->getGlobalBounds().size.y / 10 * 6 });
			}
			if (btt_menu[0]->getPosition().y == btt_menu[1]->getPosition().y) {
				btt_hov[0] = 2;
				btt_hov[1] = 3;
				btt_menu[0]->setPosition({ win_size.x / 2, win_size.y / 2 });
				btt_txt[0]->setPosition(btt_menu[0]->getPosition());
			}
			break;
		}
		case 2: {
			btt_hov[0] = 2;
			menu_page = 2;	
			n_btt = 1;
			btt_txt[0]->setString(String::fromUtf8(lc.menu_txt["btt_return"].begin(), lc.menu_txt["btt_return"].end()));
			btt_txt[0]->setOrigin({ btt_txt[0]->getGlobalBounds().size.x / 2, btt_txt[0]->getGlobalBounds().size.y / 10 * 6 });
			btt_menu[0]->setPosition(btt_menu[1]->getPosition());
			btt_txt[0]->setPosition(btt_menu[0]->getPosition());
			break;
		}
	}
}

void MainMenu::clicked_on(int i) {
	switch (menu_page) {
		case 0: {
			switch (i) {
				case 0: { // go to play menu
					clicked = 1;
					break;
				}
				case 1: { // go to settings menu
					change_page_to(1);
					break;
				}
				case 2: { // exit game
					clicked = -1;
					break;
				}
			}
			break;
		}
		case 1: {
			switch(i) {
				case 0:{ // go to set localisation
					change_page_to(2);
					break;
				}
				case 1: { // return to main menu
					change_page_to(0);
					break;
				}
			}
			break;
		}
		case 2: {
			switch(i) {
				case 0: { // return to settings menu
					change_page_to(1);
				}
			}
		}
	}
}

void MainMenu::update() {
	for (int i = 0; i < n_btt; i++) {
		// BTT_HOVER
		// 0 - was unhovered; 1 - was hovered; 2 - got unhovered; 3 - got hovered

		if (btt_hov[i] == 3) {
			btt_menu[i]->setScale({ float(pixel_size * 1.1), float(pixel_size * 1.1) });
			btt_txt[i]->setCharacterSize(55);
			btt_txt[i]->setOrigin({ btt_txt[i]->getGlobalBounds().size.x / 2, btt_txt[i]->getGlobalBounds().size.y / 10 * 6 });
			btt_txt[i]->setPosition(btt_menu[i]->getPosition());
		}
		else if (btt_hov[i] == 2) {
			btt_menu[i]->setScale({ float(pixel_size), float(pixel_size) });
			btt_txt[i]->setCharacterSize(50);
			btt_txt[i]->setOrigin({ btt_txt[i]->getGlobalBounds().size.x / 2, btt_txt[i]->getGlobalBounds().size.y / 10 * 6 });
			btt_txt[i]->setPosition(btt_menu[i]->getPosition());
		}

		if (btt_menu[i]->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(win))))
		{
			if (btt_hov[i] == 0 || btt_hov[i] == 2)
			{
				btt_hov[i] = 3;
			}
			else if (btt_hov[i] == 3)
			{
				btt_hov[i] = 1;
			}
		}
		else
		{
			if (btt_hov[i] == 2)
			{
				btt_hov[i] = 0;
			}
			else if (btt_hov[i] == 1 || btt_hov[i] == 3)
			{
				btt_hov[i] = 2;
				if (btt_cl[i] == 1) {
					btt_cl[i] = 3;
				}
			}
		}
	}
			
	while (const std::optional<Event> event = win.pollEvent()) {

		// CLOSE WINDOW & RETURN

		if (event->is<Event::KeyPressed>()) {
			const auto* k_btt_pr = event->getIf<Event::KeyPressed>();
			if (k_btt_pr->code == Keyboard::Key::Escape) {
				if (menu_page == 0) {
					clicked = -1;
				}
				else if (menu_page == 1) {
					change_page_to(0);
				}
				else if (menu_page == 2) {
					change_page_to(1);
				}
			}
		}
		
		if (menu_page == 2){
			for (int i = 0; i < 3; i++) {
				// LOC_CLICK
				// 0 - is unpressed; 1 - is pressed; 2 - got pressed; 3 - got withdrawed; 4 - got clicked
				
				if (event->is<Event::MouseButtonPressed>()) {
					const auto* m_btt_pr = event->getIf<Event::MouseButtonPressed>();
					if (m_btt_pr->button == Mouse::Button::Left) {
						if (langMenu->loc_hov[i] == 1 || langMenu->loc_hov[i] == 3) {
							if (i == langMenu->chosen) langMenu->chosen_spr->setScale({ float(pixel_size * 0.9), float(pixel_size * 0.9) });
							langMenu->locs[i]->setScale({ float(pixel_size * 0.9), float(pixel_size * 0.9) });
							langMenu->loc_cl[i] = 2;
						}
						if (langMenu->loc_cl[i] == 2) {
							langMenu->loc_cl[i] = 1;
						}
					}
				}
				if (langMenu->loc_cl[i] == 3) {
					langMenu->loc_cl[i] = 0;
				}
				if (event->is<Event::MouseButtonReleased>()) {
					const auto* m_btt_rl = event->getIf<Event::MouseButtonReleased>();
					if (m_btt_rl->button == Mouse::Button::Left) {
						if (langMenu->loc_cl[i] == 1) {
							langMenu->loc_cl[i] = 4;
							if (i == langMenu->chosen) langMenu->chosen_spr->setScale({ float(pixel_size * 1.2), float(pixel_size * 1.2) });
							langMenu->locs[i]->setScale({ float(pixel_size * 1.2), float(pixel_size * 1.2) });
							langMenu->clicked_on(i);
							lc.find_loc();
							lc.set_maps();
							langMenu->chosen_spr->setScale({ float(pixel_size * 1.2), float(pixel_size * 1.2) });
							btt_txt[0]->setString(String::fromUtf8(lc.menu_txt["btt_return"].begin(), lc.menu_txt["btt_return"].end()));
							btt_txt[0]->setOrigin({ btt_txt[0]->getGlobalBounds().size.x / 2, btt_txt[0]->getGlobalBounds().size.y / 10 * 6 });
						}
						if (langMenu->loc_cl[i] == 4) {
							langMenu->loc_cl[i] = 0;
						}
					}
				}
			}
		}

		for (int i = 0; i < n_btt; i++) {
			// BTT_CLICK
			// 0 - is unpressed; 1 - is pressed; 2 - got pressed; 3 - got withdrawed; 4 - got clicked
			
			if (event->is<Event::MouseButtonPressed>()) {
				const auto* m_btt_pr = event->getIf<Event::MouseButtonPressed>();
				if (m_btt_pr->button == Mouse::Button::Left) {
					if (btt_hov[i] == 1 || btt_hov[i] == 3) {
						btt_cl[i] = 2;
					}
					if (btt_cl[i] == 2) {
						btt_cl[i] = 1;
						btt_menu[i]->setTexture(btt_prs);
						btt_txt[i]->setFillColor(Color(255, 225, 95, 200));
					}
				}
			}
			if (btt_cl[i] == 3) {
				btt_cl[i] = 0;
				btt_menu[i]->setTexture(btt);
				btt_txt[i]->setFillColor(Color(0, 0, 0, 200));
			}
			if (event->is<Event::MouseButtonReleased>()) {
				const auto* m_btt_rl = event->getIf<Event::MouseButtonReleased>();
				if (m_btt_rl->button == Mouse::Button::Left) {
					if (btt_cl[i] == 1) {
						btt_cl[i] = 4;
						clicked_on(i);
					}
					if (btt_cl[i] == 4) {
						btt_cl[i] = 0;
						btt_menu[i]->setTexture(btt);
						btt_txt[i]->setFillColor(Color(0, 0, 0, 200));
					}
				}
			}
		}
	}
	if (menu_page == 2) langMenu->update_lang(win);
}

void MainMenu::render() {
	win.clear();
	win.draw(*bg);
	for (short i = 0; i < n_btt; i++) {
		win.draw(*btt_menu[i]);
		win.draw(*btt_txt[i]);
	}
	if (menu_page == 2) langMenu->render_lang(win);
}