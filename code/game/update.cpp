#include "GameWin.h"
using namespace std;
using namespace sf;

void GameWin::update() {
	
	// MOVING CAMERA
	
	if (sf::Mouse::getPosition(win).x < 50 && camera.getCenter().x >= winSize.x - map_terrain_layer->getGlobalBounds().size.x / 2) {
		camera.setCenter({camera.getCenter().x - 1000 * deltaTime.asSeconds(), camera.getCenter().y});
	}
	else if (sf::Mouse::getPosition(win).x > winSize.x - 50 && camera.getCenter().x <= map_terrain_layer->getGlobalBounds().size.x / 2) {
		camera.setCenter({camera.getCenter().x + 1000 * deltaTime.asSeconds(), camera.getCenter().y});
	}
	if (sf::Mouse::getPosition(win).y < 50 && camera.getCenter().y >= winSize.y - map_terrain_layer->getGlobalBounds().size.y / 2) {
		camera.setCenter({camera.getCenter().x, camera.getCenter().y - 1000 * deltaTime.asSeconds()});
	}
	else if (sf::Mouse::getPosition(win).y > winSize.y - 50 && camera.getCenter().y <= map_terrain_layer->getGlobalBounds().size.y / 2) {
		camera.setCenter({camera.getCenter().x, camera.getCenter().y + 1000 * deltaTime.asSeconds()});
	}
	
	while (const std::optional<Event> event = win.pollEvent()) {

		// GO TO MAIN MENU

		if (event->is<Event::KeyPressed>()) {
			const auto* k_btt_pr = event->getIf<Event::KeyPressed>();
			if (k_btt_pr->code == Keyboard::Key::Escape) {
				clicked = -1;
			}
		}
	}
}