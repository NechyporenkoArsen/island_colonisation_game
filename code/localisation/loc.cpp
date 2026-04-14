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
	
	// create maps
	
	ifstream read("localization/" + lang + "/menu.txt");
	while (std::getline(read, line)) {
		if (line[0] == '&') {
			menu_txt[line.substr(1, line.find(':')-1)] = line.substr(line.find(":") + 1);
		}
	}
	read.close();
}

loc::~loc(){
	cout << "close localisation" << endl;
}