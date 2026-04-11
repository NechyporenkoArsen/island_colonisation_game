#include "loc.h"
using namespace std;

loc::loc(char q){
	ifstream r_l("game_set.txt"); // read language
	std::string line;
	while (std::getline(r_l, line)) {
		if (line.substr(0, line.find('=')) == "lang") {
			lang = line.substr(line.find("=") + 1);
			break;
		}
	}
	r_l.close();
}

loc::~loc(){}

std::vector<std::string> loc::get_l(char n){
	switch (n) {
	case 0: {
		if (size(menu_loc) == 0) {
			ifstream read("localization/" + lang + "/menu.txt");
			std::string line;
			while (std::getline(read, line)) {
				if (line[0] == '&') {
					menu_loc.push_back(line.substr(line.find(':') + 1));
					menu_loc[size(menu_loc) - 1] = menu_loc[size(menu_loc) - 1].substr(0, menu_loc[size(menu_loc) - 1].find('\n'));
				}
			}
			read.close();
		}
		return menu_loc;
		break;
	}
	default: {
		return { "" };
	}
	}
}