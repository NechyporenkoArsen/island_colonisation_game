#include "loc.h"
using namespace std;

loc::loc(char q){
	find_loc();
}

loc::~loc(){}

void loc::find_loc() {
	l_num = 0;
	ifstream r_l("localisations.txt");
	while (std::getline(r_l, line)) {
		if (line[0] == '>') {
			lang = line.substr(1);
			break;
		}
		l_num++;
	}
	r_l.close();
}

void loc::set_maps() {
	ifstream read("localization/" + lang + "/menu.txt");
	while (std::getline(read, line)) {
		if (line[0] == '&') {
			menu_txt[line.substr(1, line.find(':')-1)] = line.substr(line.find(":") + 1);
		}
	}
	read.close();
}