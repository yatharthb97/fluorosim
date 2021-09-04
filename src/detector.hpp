#pragma once

#include "types.hpp"

//Header file for Detector class

template <class signal_t>
class Detector
{
public:
	signal_t Signal; //! The specific detection channel for the detector.
	double Efficiency = 1.0; //! The detection efficiency of the detector.
  	counter_t Detected_count = 0; //! The shots counted by the detector.


	//0
	/**
	 * @brief The constructor.
	 * */
	Detector(signal_t Signal, double Efficiency = 1.0): Signal(Signal), Efficiency(Efficiency)
	{}


	//1
	/**
	 * @brief Function that couples the detector to the detectable based on the channel_t.
	 * */
	bool inline filter(signal_t signal)
	{
		return (signal == this->Signal);
	}


	//2
	/**
	 * @brief Store the detected ttl pulse/shots.
	 * */
	void inline detect(const unsigned int emittance)
	{
	  this->Detected_count += emittance;
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
	  return counter_t(Detected_count * (1.0 - Efficiency));
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

/** @brief Describes a bookeeping object that tracks the various types of signals emitted within a system. */
template <class signal_t, unsigned int Max_signals>
class SignalSpace
{
public:
	unsigned int signals[Max_signals] = {0}; //! Stores the emit count (emittance) of the different signals in the signal space.
	
	/** @brief Increments the emitance of a particular signal type. */
	void emit(signal_t signal)
	{
		signals[static_cast<unsigned int>(signal)]++;
	}

	/** @brief Pops the passed signal type from the signal struct. */
	unsigned int detect(sig_t signal)
	{
		unsigned int tmp = signals[static_cast<unsigned int>(signal)];
		signals[static_cast<unsigned int>(signal)] = 0;
		return temp;
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
