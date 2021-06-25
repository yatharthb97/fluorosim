

#include <iostream>
#include "particle2.hpp"


int main()
{
	Fluorophore2 fl2;
	std::cout << static_cast<unsigned int>(fl2.fl.core) << std::endl;
	return 0;
}