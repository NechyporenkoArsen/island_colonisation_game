#include "code/MainMenu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

char open_win = 1;
int pixel_size = 0;

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "World Evolution", Style::Titlebar, State::Windowed);
    VideoMode desktop = VideoMode::getDesktopMode();
    MainMenu MainMenu();
    pixel_size = desktop.size.y / 160;

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
        // 0 nothing
        //
        ///////////////////////////////////

        switch (open_win) {
        case 0: {
            /*MainMenu.render(window);
            switch (MainMenu.clicked) {
            case -1: {
                open_win = -1;
                break;
            }
            }*/
            break;
        }
        case -1: {
            window.close();
            break;
        }
        }
        window.display();

    }
}