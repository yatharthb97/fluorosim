#pragma once

#include "types.hpp"

//Header file for Detector class

template <class channel_t>
class Detector
{
public:
	channel_t Channel; //! The specific detection channel for the detector.
	double Efficiency = 1.0; //! The detection efficiency of the detector.
  counter_t Detected_count = 0; //! The shots counted by the detector.


	//0
	/**
	 * @brief The constructor.
	 * */
	Detector(channel_t Channel, double Efficiency = 1.0): Channel(Channel), Efficiency(Efficiency)
	{}


	//1
	/**
	 * @brief Function that couples the detector to the detectable based on the channel_t.
	 * */
	bool inline filter(channel_t channel)
	{
		return (channel == this->Channel);
	}


	//2
	/**
	 * @brief Store the detected ttl pulse/shots.
	 * */
	void inline detect(const unsigned int ttl, bin_detect_t &detectable)
	{
	  this->Detected_count += ttl;
	  detectable = (ttl > 0) || false; //Switch detectable as per the condition
	}

	//3
	/**
	 * @brief Returns the detector count.
	 * */
	counter_t inline get_count() const
	{
	  return this->Detected_count;
	}

	//4
	/**
	 * @brief Returns the approximate detector counts missed. Accuracy increases as Photon_count → ∞.
	 * */
	counter_t inline approx_missed() const
	{
	  return Detected_count * static_cast<counter_t>(1.0 - Efficiency);
	}

	//5
	/**
	 * @brief Resets the Photon counter value.
	 * */
	void inline reset()
	{
		this->Detected_count = 0;
	}

	//6
	/**
	 * @brief Models the detector loss due to finite efficiency.
	 * @param Entropy source that can be called to produce a unit uniformly distributed random number.
	 * @returns boolean value of successful recording of photon
	 * */
	bool inline detector_loss(double(*unirnd)()) const
	{
	  return (unirnd() <= this->Efficiency);
	}

};


//TODO - Cleanup
  /**
   * @brief couples the Channel and resets the emit_flag and returns if the photon was successfully recorded.
   * @returns boolean value of successful recording of photon
   * */
/*  bool inline lossy_filter(const detectable_t flag, double(*unirnd)())
  {
    if(f.color == this->color)
    {
      f.emit_flag = false;
      return (rnd <= efficiency);
    }

    else
      return false;
  }*/
