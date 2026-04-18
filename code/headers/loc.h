#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

class loc
{
public:
	loc(char q);
	~loc();
	map <string, string> menu_txt;
	void find_loc(),
		set_maps();
	char l_num;
private:
	string line;
	string lang;
};
