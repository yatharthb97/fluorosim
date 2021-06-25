//classes.hpp
#pragma once

#include <fstream>
#include<sstream>
#include<iomanip>
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include "macros.hpp"

#include "./submodules/filesystem.hpp"
//#include "./submodules/timer.hpp"

class SimClock
{
public:

  double MaxTime;
  double Brownian_dt;
  double Photophy_dt;

  ulint_t TotBrownSteps = 0;
  ulint_t TotPhotSteps = 0;


  //Constructor
  SimClock(double MaxTime, double Brownian_dt, double Photophy_dt) : MaxTime(MaxTime), Brownian_dt(Brownian_dt), Photophy_dt(Photophy_dt)
  {
    if(Brownian_dt >= Photophy_dt)
    {
      //photophyscics is contained within a brownian move
      
    }
  }

  ///Returns the number for each loop level
  //Loop_Partition_Fn(3,) //-> Number of Brownian moves within a photophy time



}; //End of class SimClock




Moves moves;
Moves::total_moves();
Moves::per_part();



class Detector
{ 

public:
  

  color_t Color;
  double Efficiency;
  ulint_t Photon_count = 0;

  /**
   * @brief The constructor
   * */
  Detector(color_t Color, double Efficiency): Color(Color), Efficiency(Efficiency)
  {}

  /**
   * @brief Store the detected ttl pulse
   * */
  void inline detect(const unsigned int ttl)
  {
    this->Photon_count += ttl;
  }

  /**
   * @brief Returns the detector count
   * */
  ulint_t inline count() const
  {
    return Photon_count;
  }

  /**
   * @brief Returns the approximate detector counts missed. Accuracy increases as Photon_count → ∞.
   * */
  ulint_t inline approx_missed() const
  {
    return Photon_count * (1.0 - Efficiency);
  }

  /**
   * @brief Models the detector loss due to finite efficiency
   * @returns boolean value of successful recording of photon
   * */
  bool inline detector_loss(const double &rnd) const
  {
    return (rnd <= efficiency);
  }

  /**
   * @brief couples the flourophore with the appropriate color and resets the emit_flag.
   * @returns boolean value of successful coupling
   * @question → should the filter be non determinsitic (stochastic) in order to allow cross talk ? 
   * */
  bool inline filter(Fluorophore &f) const
  {
    if(f.color == this->color)
    {
      f.emit_flag = false;
      return true;
    }

    else
      return false;
  }

  /**
   * @brief couples the flourophore with the appropriate color and resets the emit_flag and returns if the photon was successfully recorded.
   * @returns boolean value of successful recording of photon
   * */
  bool inline lossy_filter(Fluorophore &f, double &rnd)
  {
    if(f.color == this->color)
    {
      f.emit_flag = false;
      return (rnd <= efficiency);
    }

    else
      return false;
  }

};



class Laser
{
public:

  ulint_t CharDecayTime;  //Decay time for laser
  ulint_t PulseTimePeriod; //Pulsing Time Period of laser
  
  double frequency; //Frequency of light wave
  std::string color; //Color of laser
  std::string mode = "always-on"; //Mode of operation → String val
  bool pulsing = false; //Mode of operation is pulsing → bool val


  //Constructor
  Laser(ulint_t PulseTimePeriod, ulint_t CharDecayTime) : PulseTimePeriod(PulseTimePeriod), CharDecayTime(CharDecayTime)
  {
    this->mode = "pulsing";
    pulsing = false;
  }

  //Mode Constructor
  Laser(std::string mode)
  {
    if(mode == "always-on")
    {
      this->mode = mode;
      pulsing = false;
      this->CharDecayTime = std::numeric_limits<ulint_t>::max();
      this->PulseTimePeriod = std::numeric_limits<ulint_t>::max();
    }

    else if(mode =="pulsing") //Set Default Values
    { 
        pulsing = true;
        this->mode = mode;
        this->CharDecayTime = 5;
        this->PulseTimePeriod = 10;
    }

    else
    {
      std::cerr << "[ERROR] LASER → Invalid Mode of operation: " << mode << '\n';
      std::cerr << "[•••••> LASER → Mode of operation is set : " << mode << '\n';

      this->mode = "always-on";
      this->pulsing = false;
      this->CharDecayTime = std::numeric_limits<ulint_t>::max();
      this->PulseTimePeriod = std::numeric_limits<ulint_t>::max();
    }
  } //End of Mode based Constructor

  double prob(const ulint_t &simcounter) const
  {
      if(pulsing)
      {
        double elapsed_time = double(simcounter % PulseTimePeriod)*-1;
        return std::exp((elapsed_time)/double(CharDecayTime));
                     //! - This is a negative exponential
      }

      else //always-on
        return 1.0;

  } //End of prob


  std::string getPulseTimePeriod() const
  {
    if(!pulsing)
      return "∞";
    else
      return std::to_string(PulseTimePeriod);
  }


  std::string getCharDecayTime() const
  {
    if(!pulsing)
      return "∞";
    else
      return std::to_string(CharDecayTime);
  }

}; //End of class Laser


class Veff_Base()
{
  V bounds() const = 0; //returns the boundaries of the variable
  geo_t type() const = 0; //returns the "type" of the psf
  std::string type_str() const = 0; //Type of PSF in String
  double sf() const = 0; //measure of assymetry along z direction
  double vol() const = 0; //volume of rough bound enclosure
  double psf_prob(const &V) const = 0; //returns the intensity profile at the point
  bool invol(const &V) const = 0; //returns whether the particle is in the effective vol
};


class 3D_Gaussian : public Veff_Base
{
  public:

  V exponents;
  V centre;
  V boundaries;
  double norm = 1.0;

  double radius;
  double radius_sq;
  double sf;

  3D_Gaussian(double radius, double sf, V centre = V()) : radius(radius), sf(sf), centre(centre), radius_sq(radius*radius)
  {
    this->boundaries = V(centre + radius, centre + radius, centre + radius*sf);
    this->exponents =  V(-2.0/radius_sq, -2.0/radius_sq, -2.0/(radius_sq*sf));
  }


  V bounds() const override
  {
    return boundaries;
  }

  geo_t type() const override
  {
    return geo_t::Ellipsoid;
  }

  std::string type_str() const override
  {
    return "3D Gaussian - Ellipsoid";
  }
  double sf() const override
  {
    return this->sf;
  }

  double vol() const override
  {
    return CONST_PI_pow3by2 * this->radius * this->radius *  this->radius * this->sf;
  }

  double psf_prob(const &V) const override
  {
    V temp = V(pos - this->centre).square;
    temp = temp.comp_mul(this->exponents);
    
    double exponent = exps.accumulate();
    return this->norm * std::exp(exponent)
  }

  bool invol(const &V) const override
  {
    V temp = V(pos - this->centre);
    temp.comp_divide(this->boundaries);
    temp.comp_square(); //Square it

    return (temp.accumulate <= 1.0) || false;
  }

};


class USphere :  public Veff_Base
{
  public:

  V exponents;
  V centre;
  V boundaries;
  double norm = 1.0;

  double radius;
  double radius_sq;
  double sf;

  USphere(double radius, V centre = V()): radius(radius), radius_sq(radius_sq), centre(centre), boundaries(V(radius, radius, radius))
  {
    this->exponents = boundaries.square();
  }

  V bounds() const override
  {
    return boundaries;
  }

  geo_t type() const override
  {
    return geo_t::Sphere;
  }

  std::string type_str() const override
  {
    return "Uniform Sphere";
  }

  double sf() const override
  {
    return 1.0;
  }

  double vol() const override
  {
    return 4/3*CONST_PI * this->radius * this->radius * this->radius;
  }
  double psf_prob(const &V pos) const override
  {
    return 1.0 * invol(pos) + 0.0;
  }
  
  bool invol(const &V pos) const override
  {
    V temp = V(pos - this->centre).square();
    V temp.comp_divide(exponents);

    return (temp.accumulate() <= radius_sq) || false;
  }

};


//Wrapper for all the stringstream objects → Single Interface
class Datapipe
{
    
public:

    std::ostringstream stats;
    
    #if FCS_PART_TAGGING == 1
      std::ostringstream tag;
    #endif

    //distributions
    #if FCS_RND_SAMPLING == 1
      std::ostringstream u_dist;
      std::ostringstream gauss_dist;
    #endif

    //Reference of all streams
    std::vector <std::ostringstream *> pipelist;


    Datapipe()
    {
      //stats
      stats << std::setprecision(FCS_FLOAT_PRECISION);
      pipelist.emplace_back(&stats);

      //tag
      #if FCS_PART_TAGGING == 1
        tag << std::setprecision(FCS_FLOAT_PRECISION);
        pipelist.emplace_back(&tag);
      #endif

      //distributions
      #if FCS_RND_SAMPLING == 1
        pipelist.emplace_back(&u_dist);
        pipelist.emplace_back(&gauss_dist);
      #endif

    } // End of Datapipe()

    bool inline Flush(const std::string &parentpath)
    {

      bool errnox = false;
      if(!parentpath.empty())
      {
        errnox = WriteToFile(std::string(parentpath + AddExt("stats")), stats.str());


        #if FCS_PART_TAGGING == 1
        errnox = errnox && WriteToFile(std::string(parentpath + AddExt("tag")), tag.str());
        #endif


        #if FCS_RND_SAMPLING == 1
        errnox = errnox && 
                 WriteToFile(std::string(parentpath + AddExt("u_dist")), u_dist.str()) &&
                 WriteToFile(std::string(parentpath + AddExt("gauss_dist")), gauss_dist.str());
        #endif
                          
      }

      return errnox;

    } //End of Flush()

    //Clears all buffers
    void ClearAll()
    {
        for(auto stream: pipelist)
        {
          stream->str(std::string()); //Set equivalent to string of zero length
          stream->clear();  //Set error stateflags
          stream->seekp(0); // for outputs: seek put ptr to start
        }
    }

private:


  std::string AddExt(std::string str)
  {
    str.append(FCS_DATAFILE_EXT);
    return str;
  }
  
  bool inline WriteToFile(std::string path, const std::string &content)
  {
    std::ofstream file(path, std::ios::out);
    if(file.is_open())
    { 
      file << content;
      return true;
      //RAII close expected.
    }
    else
      return false;

    //RAII file close expected
  }

}; //End of class Datapipe

