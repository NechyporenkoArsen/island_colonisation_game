#include "GameWin.h"
using namespace std;
using namespace sf;

void GameWin::update() {
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