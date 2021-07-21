//classes.hpp
#pragma once

#include <cmath>
#include <vector>
#include <cassert> //For assert
#include <exception> //For std::terminate

#include "macros.hpp"

//#include "./submodules/timer.hpp"


//Temporal Process → this set is shared with the System group.
enum class Phenomena
{
  Brownian = 0,
  Photophysics
};



/**
 * @brief Timekeeping Object
 * */
template <unsigned int Max_Phenomena>
class Clock
{
public:

  double StepSize[Max_Phenomena] = {0.0};
  simcounter_t MaxSteps[Max_Phenomena] = {0};

  bool MaxTime_defined = false;


  //Constructor
  Clock(double MaxTime)
  {}

  /**
   * @brief Sets the Maximum time for the simulation.*/
  void set_max_time(simcounter_t MaxTime)
  {
    this->MaxTime = MaxTime;
    MaxTime_defined = true;
  }

  /**
   * @brief Sets the clock counter for the specified process. The size of the list needs to be defined at compile time. */
  void set_clock(const Phenomena process, const simcounter_t time_step)
  {
    assert(MaxTime_defined);

    if(time_step <= MaxTime)
    {
      unsigned int index = static_cast<unsigned int>(process);
      this->StepSize[index] = (time_step);
      this->MaxSteps[index] = simcounter_t(double(MaxTime)/double(time_step));
    }

    else
      {
        std::cerr << "• Invalid Input —→ Entered Step Size is greater than the MaxTime.\n";
        std::exit(EXIT_FAILURE);
      }
  }

  /**
   * @brief Returns the step size for a given process.*/
  double get_stepsize(Phenomena process)
  {
    return StepSize[static_cast<unsigned int>(process)];
  }


  /**
   * @brief Evaluates if B can be nested inside process A.
   * */
  bool has_nested_order(Phenomena A, Phenomena B)
  {
    return StepSize[static_cast<unsigned int>(A)] >= StepSize[static_cast<unsigned int>(B)];
  }


  /**
   * @brief Provides the exact relative frequency of process A wrt B.*/
  double rel_freq(Phenomena A, Phenomena B)
  {
    return StepSize[static_cast<unsigned int>(A)] / StepSize[static_cast<unsigned int>(B)];
  }


  /**
   * @brief Provides an approximate discrete relative frequency of process A wrt B with the value rounded off to the nearest integer.*/
  discrete_freq_t discrete_rel_freq(Phenomena A, Phenomena B)
  {
    return simcounter_t(std::round(StepSize[static_cast<unsigned int>(A)] / 
                                   StepSize[static_cast<unsigned int>(B)]));
  }


  /**
   * @brief Provides the maximum steps performed by a process.*/
  simcounter_t max_steps(Phenomena A)
  {
    return simcounter_t(double(MaxTime)/double(StepSize));
  }

}; //End of class SimClock