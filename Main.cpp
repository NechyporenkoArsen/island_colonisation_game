#include "MainMenu.h"
#include "GameWin.h"
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
	loc.set_maps();
	MainMenu MainMenu( window, {float(desktop.size.x), float(desktop.size.y) }, pixel_size, loc);
	GameWin GameWin(window, pixel_size);

    while (window.isOpen()) {
        window.clear();

        ///////////////////////////////////
        //
        // ===== open_win =====
        // 
        // -1 close
        //  0 MainMenu
		//  1 GameWin
        // 
        // ===== clicked =====
        // -1 set open_win to -1
        //  0 nothing
		//  1 set open_win to 1
        //
        ///////////////////////////////////

        switch (open_win) {
			case -1: {
				open_win = 0;
				window.close();
				break;
			}
			case 0: {
				MainMenu.update();
				MainMenu.render();
				switch(MainMenu.clicked){
					case -1: {
						open_win = -1;
						break;
					}
					case 1: {
						open_win = 1;
						MainMenu.clicked = 0;
						break;
					}
				}
				break;
			}
			case 1: {
				GameWin.update();
				GameWin.render();
				switch(GameWin.clicked){
					case -1: { // go to main menu
						open_win = 0;
						GameWin.clicked = 0;
					}
				}
				break;
			}
        }
        window.display();

    }
}