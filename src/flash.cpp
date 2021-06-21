

#include <iostream>
#include <chrono>





int main()
{
	std::string text;
	std::cin << text;

	std::cout << text << std::flush;
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	std::cout << "ESC[1A" << "----" << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	std::cout << "ESC[1A" << text << std::endl;

}
