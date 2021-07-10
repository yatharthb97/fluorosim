#pragma once

#include <sstream>
#include <cmath>

#include "colors.hpp"
#include "types.hpp"

//Header File that describes Laser Objects.

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

}; // End of class Laser

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

		laserinfo << "• Unit Laser : " << color::color_str(this->Color);
		return laserinfo.str();
	}


}; // End of class UnitLaser

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

		laserinfo << "• Steady Laser : " << color::color_str(this->Color) 
		          << " | Intensity : " << this->Intensity;
		return laserinfo.str();
	}


}; // End of class SteadyLaser


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
