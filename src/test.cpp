

#include <iostream>
#include <random>
#include <functional>
/*#include "detector.hpp"
#include "colors.hpp"
#include "camera.hpp"
#include "datapipe.hpp"
#include "particle.hpp"
#include "fluorophore.hpp"
#include "fluorophoresX.hpp"
#include "./submodules/random.hpp"*/

#include "units.hpp"
#include "macros.hpp"


int main()
{
/*	using ColorDetector = Detector<color_t>;
	ColorDetector red_detect(color_t::red);

	Camera cam(14);
	std::cout << "Compiled!" << std::endl;

	//MT_RND rnd;
	std::mt19937 rnd;
	std::uniform_real_distribution<double> uni_dist(0.0, 1.0);
	std::normal_distribution<double> gauss_dist(0.0, 1.0);

	//This approach will not work. It is better to use a seperate function inside the box.
	auto gaussrnd = std::bind(std::mt19937::operator(), &rnd, &gauss_dist);
    auto unirnd = std::bind(std::mt19937::operator(), &rnd, &uni_dist);

    for (unsigned int i = 0; i < 1000 ; i++)
    {
    	std::cout << gaussrnd() << std::end;
    }

    for (unsigned int i = 0; i < 1000 ; i++)
    {
    	std::cout << unirnd() << std::end;
    }*/


    Units unit;
    unit.set_scale_STE(2*1e-9, 300, CONST_WATER_VISCOSITY);

    std::cout << unit.profile(1e-3, 1e8) << std::endl;
}


