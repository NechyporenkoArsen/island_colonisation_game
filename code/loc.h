#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class loc
{
public:
	loc(char q);
	~loc();
	std::string lang;
	std::vector<std::string> get_l(char n);
private:
	std::vector<std::string> menu_loc;
};

