

#include <iostream>
#include "detector.hpp"
#include "colors.hpp"


int main()
{
	using ColorDetector = Detector<color_t>;
	ColorDetector red_detect(color_t::red);
	std::cout << "Compiled!" << std::endl;
	return 0;
}