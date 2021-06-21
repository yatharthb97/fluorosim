//Header file for Timing Framework → <timer.hpp>
//><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
//><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><

  /*$$$$$            /$$                                      /$$$$$$  /$$              
 /$$__  $$          | $$                                     /$$__  $$|__/              
| $$  \__/  /$$$$$$ | $$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$ | $$  \__/ /$$ /$$$$$$/$$$$ 
|  $$$$$$  /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$|  $$$$$$ | $$| $$_  $$_  $$
 \____  $$| $$  \ $$| $$  \ $$| $$$$$$$$| $$  \__/| $$  \ $$ \____  $$| $$| $$ \ $$ \ $$
 /$$  \ $$| $$  | $$| $$  | $$| $$_____/| $$      | $$  | $$ /$$  \ $$| $$| $$ | $$ | $$
|  $$$$$$/| $$$$$$$/| $$  | $$|  $$$$$$$| $$      |  $$$$$$/|  $$$$$$/| $$| $$ | $$ | $$
 \______/ | $$____/ |__/  |__/ \_______/|__/       \______/  \______/ |__/|__/ |__/ |__/
          | $$                                                                          
          | $$                                                                          
          |_*/
//><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
//><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><

//><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
//  Developed by: Yatharth Bhasin		|| Licence: *******************
//  Discipline of Physics				|| Compile : Ok -> 14/01/2021 12:30 PM
//  IIT Indore							|| Tested : NOK
//  (yatharth1997@gmail.com)			|| Documentation : NOK
//  (github: yatharthb97)				||		
//><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><



#pragma once
#include <chrono>
#include <ctime>


//TimeStamp - Create TimeStamps
std::time_t inline TimeStamp()
{
	auto stamp = std::chrono::system_clock::now();
	std::time_t stamp_time = std::chrono::system_clock::to_time_t(stamp);
	return(std::time_t (stamp_time));
}
//End of TimeStamp


class TimerHD
{

public:

	std::chrono::time_point<std::chrono::high_resolution_clock> stamp_time;
	std::string key;

	//Constructor
	TimerHD(std::string key = ""): key(key)
	{
		std::cout << "\x1B[33m Started Timing: " << key << "\x1B[37m \n";
		stamp_time = std::chrono::high_resolution_clock::now();
	}


	void Stop()
	{
		using namespace std;
		using namespace std::chrono;
		time_point<std::chrono::high_resolution_clock> stop = high_resolution_clock::now();
		auto _duration = std::chrono::duration_cast<microseconds>(stop - stamp_time);
		std::cout << "\x1B[33m Ended Timing : " << key << " -> "
			        << "Duration Elapsed:  ";

		long long duration = _duration.count();
      

		if (duration <= 99) std::cout << duration << " µs";
		else if (duration > 99 && duration <= 9999) std::cout << (double)duration*0.001 << " ms";
		else if (duration > 9999 & duration <= 9999999) std::cout << (double)duration*0.000001 << " s";
		else if (duration > 9999999 & duration <= 99999999 ) std::cout << (double)duration*1.6666666666666666666666666666667e-8 << " min";
		else  std::cout << (double)duration*2.7777777777777777777778e-10 << " hours";
		
		std::cout << "\x1B[37m" << std::endl;
	}


}; //End of class Timer