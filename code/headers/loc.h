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
private:
	string lang;
};
