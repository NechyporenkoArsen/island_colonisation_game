#include "MainMenu.h"
#include "loc.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
using namespace std;
using namespace sf;

char open_win = 0;
int pixel_size = 0;

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "World Evolution", Style::Titlebar, State::Windowed);
    VideoMode desktop = VideoMode::getDesktopMode();
    pixel_size = desktop.size.y / 320;
	loc loc(0);
	MainMenu MainMenu({ float(desktop.size.x), float(desktop.size.y) }, pixel_size, loc);

    while (window.isOpen()) {
        window.clear();

        ///////////////////////////////////
        //
        // ===== open_win =====
        // 
        // -1 close
        //  0 MainMenu
        // 
        // ===== clicked =====
        // -1 set open_win to -1
        //  0 nothing
        //
        ///////////////////////////////////

        switch (open_win) {
		case 0: {
			MainMenu.update(window);
			MainMenu.render(window);
			switch(MainMenu.clicked){
				case -1: {
					open_win = -1;
					break;
				}
			}
			break;
		}
        case -1: {
			open_win = 0;
            window.close();
            break;
        }
        }
        window.display();

    }
}