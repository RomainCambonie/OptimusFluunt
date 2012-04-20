#include "utils.h"


int stringToInt(string str)
{
	std::istringstream iss(str);
	int nb;
	iss >> nb;
	return nb;
}

string intToString(int nb)
{
    std::ostringstream oss;
    oss << nb;
    return oss.str();
}
