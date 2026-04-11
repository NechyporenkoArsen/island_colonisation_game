#include "MainMenu.h"
#include "loc.h"
using namespace std;
using namespace sf;

MainMenu::MainMenu(Vector2f w, int pix){
	menu_page = 0;
	max_btt = 3;
	min_btt = 0;
	pixel_size = pix;
	loc loc(0);
	lc = loc.get_l(0);
	dec_font.openFromFile("assets/fonts/RutheniaRadaFancy-Regular.ttf");

	// Textures

	water.loadFromFile("assets/textures/water.jpg");
	btt.loadFromFile("assets/textures/menu_button.png");
	btt_prs.loadFromFile("assets/textures/menu_button_pressed.png");

	// Edit Textures

	water.setRepeated(true);

	// Load Sprites

	bg = make_unique<Sprite>(water);
	btt_return = make_unique<Sprite>(btt);
	for (int i = 0; i < size(btt_menu); i++) {
		btt_menu[i] = make_unique<Sprite>(btt);
	}

	// Edit Sprites

	bg->setScale({ float(pixel_size), float(pixel_size) });
	bg->setTextureRect({ {0, 0}, {int(w.x), int(w.y)} });

	btt_return->setOrigin({btt_return->getLocalBounds().size.x / 2, btt_return->getLocalBounds().size.y / 2});
	btt_return->setPosition({w.x / 2, w.y / 2});
	btt_return->setScale({float(pixel_size), float(pixel_size)});

	for (int i = 0; i < size(btt_menu); i++) {
		btt_menu[i]->setScale({ float(pixel_size), float(pixel_size) });
		btt_menu[i]->setOrigin({ btt_return->getLocalBounds().size.x / 2, btt_return->getLocalBounds().size.y / 2 });
		btt_menu[i]->setPosition({ w.x / 2, w.y / 2 + i * (btt_return->getGlobalBounds().size.y + 30)});
	}

	// TEXT

	for (int i = 0; i < size(btt_main_txt); i++) {
		btt_main_txt[i] = std::make_unique<Text>(dec_font, String::fromUtf8(lc[i].begin(), lc[i].end()), 50);
		btt_main_txt[i]->setOrigin({ btt_main_txt[i]->getGlobalBounds().size.x / 2, btt_main_txt[i]->getGlobalBounds().size.y / 10 * 6 });
		btt_main_txt[i]->setPosition(btt_menu[i]->getPosition());
		btt_main_txt[i]->setFillColor(Color(0, 0, 0, 200));
	}
}

MainMenu::~MainMenu(){
	///////////////////////////////////
	//
	// ===== menu_page =====
	// 
	// 0 MainMenu
	// 1 Settings
	//
	///////////////////////////////////
}

void MainMenu::clicked_on(int i) {
	switch (i) {
	case 1: {
		menu_page = 1;
		min_btt = 3;
		max_btt = 4;
		break;
	}
	case 2: {
		clicked = -1;
		break;
	}
	}
}

void MainMenu::update(RenderWindow& win) {
	while (const std::optional<Event> event = win.pollEvent()) {

		// CLOSE WINDOW

		if (event->is<Event::KeyPressed>()) {
			const auto* k_btt_pr = event->getIf<Event::KeyPressed>();
			if (k_btt_pr->code == Keyboard::Key::Escape) {
				clicked = -1;
			}
		}

		for (int i = min_btt; i < max_btt; i++) {

			// BTT_HOVER
			// 0 - was unhovered; 1 - was hovered; 2 - got unhovered; 3 - got hovered

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

			if (btt_hov[i] == 3) {
				btt_menu[i]->setScale({ float(pixel_size * 1.1), float(pixel_size * 1.1) });
				btt_main_txt[i]->setCharacterSize(55);
				btt_main_txt[i]->setOrigin({ btt_main_txt[i]->getGlobalBounds().size.x / 2, btt_main_txt[i]->getGlobalBounds().size.y / 10 * 6 });
				btt_main_txt[i]->setPosition(btt_menu[i]->getPosition());
			}
			else if (btt_hov[i] == 2) {
				btt_menu[i]->setScale({ float(pixel_size), float(pixel_size) });
				btt_main_txt[i]->setCharacterSize(50);
				btt_main_txt[i]->setOrigin({ btt_main_txt[i]->getGlobalBounds().size.x / 2, btt_main_txt[i]->getGlobalBounds().size.y / 10 * 6 });
				btt_main_txt[i]->setPosition(btt_menu[i]->getPosition());
			}

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
						btt_main_txt[i]->setFillColor(Color(255, 225, 95, 200));
					}
				}
			}
			if (btt_cl[i] == 3) {
				btt_cl[i] = 0;
				btt_menu[i]->setTexture(btt);
				btt_main_txt[i]->setFillColor(Color(0, 0, 0, 200));
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
						btt_main_txt[i]->setFillColor(Color(0, 0, 0, 200));
					}
				}
			}
		}
	}
}

void MainMenu::render(RenderWindow& win) {
	win.draw(*bg);
	for (int i = min_btt; i < max_btt; i++) {
		win.draw(*btt_menu[i]);
	}
	for (int i = min_btt; i < max_btt; i++) {
		win.draw(*btt_main_txt[i]);
	}
}