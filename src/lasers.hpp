#pragma once

#include <sstream>
#include <cmath>

#include "colors.hpp"
#include "types.hpp"

//Header File that describes Laser Objects.

//0
/**
 * @brief Base Laser Object Interface. It is completely interfaced and and cannot be instantiated.
 * */
class Laser
{
public:

//Members
	
	color_t Color = color_t::colorless; //! Color of the laser beam

	//0
	/**
	 * @brief Default color constructor.*/
	Laser(color_t Color = color_t::colorless) : Color(Color)
	{}


	//1
	/**
	 * @brief Time dependent intensity function that emulates the laser beam intensity profile - Interface.
	 * @return Normalized Intensity Value. Max → 1.0, Minimum → 0.0.
	 * @param The discrete time value (Simulation Counter).
	 * */
	n_intensity_t inline virtual intensity(simcounter_t time) = 0;

	//2
	/**
	 * @brief Returns a descriptive string for the object that serves as dashboard information - Interface.
	 * */
	std::string inline virtual profile() = 0;

	//3
	/**
	 * @brief Returns the color of the laser. */
	color_t inline get_color() const
	{
		return this->Color;
	}

}; // End of class Laser


//1
/**
 * @brief Constant and Steady Laser Source with unit Intensity.
 * */
class UnitLaser : public Laser
{
public:

	/**
	 * @brief Only Constructor.
	 * */
	UnitLaser(color_t Color = color_t::colorless): Laser(Color)
	{}

	/**
	 * @Brief Returns a constant unit intensity.
	 * */
	n_intensity_t inline intensity(simcounter_t time) const
	{
		return 1.0;
	}

	/**
	 * @brief Descriptor.
	 * */
	std::string inline profile() const
	{
		std::ostringstream laserinfo;

		laserinfo << "• Unit Laser (always-on) : " << color::color_str(this->Color) << 
				  << " | Normalised intensity : 1.0 ";
		return laserinfo.str();
	}


}; // End of class UnitLaser


//2
/**
 * @brief Emulates a laser beam with fixed normalized intensity <= 1.0.
 * */
class SteadyLaser : public Laser
{
public:

	n_intensity_t Intensity = 1.0; //! Constant Intensity of the laser

	/**
	 * @brief Only Constructor.
	 * */
	SteadyLaser(color_t Color, n_intensity_t Intensity): Laser(Color), Intensity(Intensity)
	{}

	/**
	 * @Brief Returns a constant set intensity.
	 * */
	n_intensity_t inline intensity(simcounter_t time) const
	{
		return this->Intensity;
	}

	/**
	 * @brief Descriptor.
	 * */
	std::string inline profile() const
	{
		std::ostringstream laserinfo;

		laserinfo << "• Steady Laser (always-on) : " << color::color_str(this->Color) 
		          << " | Normalised intensity : " << this->Intensity;
		return laserinfo.str();
	}


}; // End of class SteadyLaser

//3
/**
 * @brief Emulates a laser beam with an exponentially decaying but periodic intensity profile.
 * */
class SoftDecayLaser : public Laser
{
public:

	simcounter_t CharDecayTime = 1; //! Characteristic Decay time of the exponential decaying intensity function.
	simcounter_t PulseTimePeriod = 1; //! The time period of the excitation.

	/**
	 * @brief Only Constructor.
	 * */
	SoftDecayLaser(color_t Color, simcounter_t PulseTimePeriod, simcounter_t CharDecayTime): Laser(Color), PulseTimePeriod(PulseTimePeriod), CharDecayTime(CharDecayTime)
	{}

	/**
	 * @Brief Returns a periodic exponentially decaying normalized intensity profile.
	 * */
	n_intensity_t inline intensity(simcounter_t time) const
	{
		double elapsed_time = double(time % PulseTimePeriod)*-1;
        
        return std::exp((elapsed_time)/double(CharDecayTime));
                     //! - This is a negative exponential
	}

	/**
	 * @brief Descriptor.
	 * */
	std::string inline profile() const
	{
		std::ostringstream laserinfo;

		laserinfo << "• Soft Decay Laser : " << color::color_str(this->Color) << '\n'
		          << "• Pulsing Time Period : " << this->PulseTimePeriod
		          << " | Characteristic Decay Time : " << this->CharDecayTime;
		return laserinfo.str();
	}


}; // End of class SteadyLaser


//4
/**
 * @brief Emulates a laser beam which is on during even timesteps and off during odd timesteps.
 * */
class EvenLaser : public Laser
{
public:

	/**
	 * @brief Only Constructor.
	 * */
	EvenLaser(color_t Color): Laser(Color)
	{}

	/**
	 * @Brief Returns a periodic exponentially decaying normalized intensity profile.
	 * */
	n_intensity_t inline intensity(simcounter_t time) const
	{
        return (time & 1);
	}

	/**
	 * @brief Descriptor.
	 * */
	std::string inline profile() const
	{
		std::ostringstream laserinfo;

		laserinfo << "• Even Laser (pulsing): " << color::color_str(this->Color) << '\n'
		          << "• Normalised intensity : 1.0 during even clock time.\n"
		          << "• Normalised intensity : 0.0 during odd clock time.\n"
		          
		return laserinfo.str();
	}


}; // End of class EvenLaser


//5
/**
 * @brief Emulates a laser beam which is on during odd timesteps and off during even timesteps.
 * */
class OddLaser : public Laser
{
public:

	/**
	 * @brief Only Constructor.
	 * */
	OddLaser(color_t Color): Laser(Color)
	{}

	/**
	 * @Brief Returns a periodic exponentially decaying normalized intensity profile.
	 * */
	n_intensity_t inline intensity(simcounter_t time) const
	{
        return !(time & 1);
	}

	/**
	 * @brief Descriptor.
	 * */
	std::string inline profile() const
	{
		std::ostringstream laserinfo;

		laserinfo << "• Odd Laser (pulsing): " << color::color_str(this->Color) << '\n'
		          << "• Normalised intensity : 1.0 during odd clock time.\n"
		          << "• Normalised intensity : 0.0 during even clock time.\n"
		          
		return laserinfo.str();
	}


}; // End of class EvenLaser