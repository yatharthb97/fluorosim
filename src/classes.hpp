//classes.hpp
#pragma once

#include <cmath>
#include <vector>
#include <cassert> //For assert
#include <exception> //For std::terminate

#include "macros.hpp"

//#include "./submodules/timer.hpp"


//Temporal Process → this set is shared with the System group.
enum class Temporal_Process
{
  Brownian = 0,
  Photophysics
};













/**
 * @brief Timekeeping Object
 * */
template <unsigned int Phenomena>
class Clock
{
public:

  double StepSize[Phenomena] = {0.0};
  simcounter_t MaxSteps[Phenomena] = {0};

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
  void set_clock(const Temporal_Process process, const simcounter_t time_step)
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
  double get_stepsize(Temporal_Process process)
  {
    return StepSize[static_cast<unsigned int>(process)];
  }


  /**
   * @brief Evaluates if B can be nested inside process A.
   * */
  bool has_nested_order(Temporal_Process A, Temporal_Process B)
  {
    return StepSize[static_cast<unsigned int>(A)] >= StepSize[static_cast<unsigned int>(B)];
  }


  /**
   * @brief Provides the exact relative frequency of process A wrt B.*/
  double rel_freq(Temporal_Process A, Temporal_Process B)
  {
    return StepSize[static_cast<unsigned int>(A)] / StepSize[static_cast<unsigned int>(B)];
  }


  /**
   * @brief Provides an approximate discrete relative frequency of process A wrt B with the value rounded off to the nearest integer.*/
  discrete_freq_t discrete_rel_freq(Temporal_Process A, Temporal_Process B)
  {
    return simcounter_t(std::round(StepSize[static_cast<unsigned int>(A)] / 
                                   StepSize[static_cast<unsigned int>(B)]));
  }


  /**
   * @brief Provides the maximum steps performed by a process.*/
  simcounter_t max_steps(Temporal_Process A)
  {
    return simcounter_t(double(MaxTime)/double(StepSize));
  }

}; //End of class SimClock


void evolve(Clock &clock, Camera &camera)
{
    //Create Single Entropy Sources
    auto gaussrnd = std::bind(&MT_RND::engine.operator(), &rnd, gauss_dist);
    auto unirnd = std::bind(&MT_RND::engine.operator(), &rnd, uni_dist);

    const discrete_freq_t outerloop =  camera.get_snaps();
    const discrete_freq_t inner_brownainloop = clock.max_steps(Evol::Brownian)/outerloop;
    const discrete_freq_t inner_photoloop = clock.rel_freq(Evol::Photophysics, Evol::Brownian);
    
    //Print Information
    std::ostringstream info;
    info << "• Snapshots: " << outerloop << "  • Photosteps per Brownian steps: " << inner_photoloop << '\n';
    std::cout << info.str();

    //Start TimerHD - simulation
    time_simulation("Box::evolve → Simulation Block");

      //Outer Loop → For Snapshots
      for(simcounter_t k = 0; j < outerloop; j++) //Outer Loop
      {

          //Brownian Loop
          for(simcounter_t j = 0; j < inner_brownainloop; j++) //Inner Brownian Loop
          {
            //For One Time Step ↓        

            //Increment SimCounter
            clock.SimCounter++; //Increment Simulation SimCounter

            //6.3.1  //Move the particles
            dynamic_cycle(clock.SimCounter);

            for(simcounter_t i = 0; i < inner_photoloop; i++) //Inner Brownian Loop
            {
              //Loop → Photocycle
              photophysics_cycle(clock.SimCounter);

              //Loop → detection
              for(auto &part : this->partlist)
              {                
                #pragma unroll //unroll this loop in compilation
                for(auto &det : detectorlist) 
                {
                  det.detect(det.filter(part.get_color()), part.Emit_Flag);
                }

              } //End of detection loop

            } //End of photophysical loop

          //Data Acqusition ------------------------

            //Particle Tagging 
            #if FCS_PART_TAGGING == 1
              datapipe.tag << partlist[FCS_TAG_PARTID].position().info(FCS_DSep) << '\n';
            #endif //FCS_PART_TAGGING

            //Normalization
            MSD += (MSDi)/double(Part_no); //Total MSD count per particle

                              //Simulation Time
            datapipe.stats << double(clock.SimCounter)*Bdt << FCS_DSep << MSD/double(clock.SimCounter);
                              //Elapsed Time                 //Normed MSD
            for(auto &det : detectorlist)
            {
              datapipe.stats << FCS_DSep << det.get_count();
            } 
            datapipe.stats << '\n';
          //Data Acqusition ------------------------  

          } //End of Brownian Loop


          ////6.3.4 FrameExport - TODO → Introduce a camera based - get_snap_name() function
          WritePosFrame(partlist, j+1);

      } //End of Outer Snapshot Loop

    time_simulation.Stop(); //End TimerHD - simulation


} //End of evolve()



//Part::translate(V(x,y,z), (void)(*boundary_fn)(V &pos))


//Move All particles   D = 3, dim = 3 2*dim*D = 2*3*3
//<x^2> = 2*dim*D*dt = 4*D*t  ==> 18*t = MSD =<r^2>

//Defination of dynamic_cycle
void inline dynamic_cycle(simcounter_t Time, double(*gaussrnd)())
{
  for(auto &part : this->partlist)
  {
    double scalar = std::sqrt(2 * this->dim * part.get_D() * clock.stepsize(Temporal_Process::Brownian));
    V translation = V::GenerateMul(scalar, gaussrnd);
    part.translate(translation);
    
    #if FCS_ENABLE_PBC == 1
      pbc(part.Pos);
    #endif
  }
} //End of dynamic_cycle()

//Defination of photophysics_cycle
void inline photophysics_cycle(simcounter_t Time, double(*unirnd)())
{
  //Loop → absorbance
  for(auto &part : this->partlist)
  {
    //Absorbance depends on the external environment
    if(gaussrnd() <= laser.intensity(Time) * veff.intensity(part.position()))
    {
      part.try_absorb(unirnd);
    }
  }

  //Loop → emittance
  for(auto &part : this->partlist)
  {
    part.try_emit(unirnd);
  }
} //End of photophysics_cycle()