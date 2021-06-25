#pragma once


#include "./submodules/vector.hpp"
#include<vector>
#include<array>


enum class fl_state_t
{
	Ground = 0,
	Excited,
	Triplet
};



enum class color_t
{
	default_color = 0,
	red,
	green,
	yellow
	
};

class Fluorophore
{
public:

	unsigned int partid;
	V pos; 		         	    //Position Vector
  V init_pos;          	  //Initial Position
	double D = 3.0;      	  //Diffusion Rate
	double qm_yield = 0.8; 	//Emmission base probablity
	bool InVol = false;     // Is the particle in the observation Volume ?
	
	unsigned long int last_flash = 0;  //Time of last flash
	//unsigned long int creation_t = 0;  //Time of Creation
	

	fl_state_t state;

	int FlashCount;  //Number of times the molecule is flashed



  //Default Constructor
  Fluorophore(unsigned int partid, V &pos): partid(partid), pos(pos), init_pos(pos)
  {}


/*  static unsigned int BleachedCount(const partlist_t &partlist)
  {
  	unsigned int count = 0;
  	for(auto &part : partlist)
  	{
  		count += part.bleached;
  	}

  	return count;
  } //End of BleachedCount()*/



  void __attribute__((always_inline)) Flash() //[[always_inline]]
  {
  	
  	//A
  	#if FCS_PER_PART_STATS == 1
  		this->FlashCount++;
  	#endif

  	//B
  	#if FCS_BLEACHING == 1
	  	this->internalflashCounter--;
	  	if(internalflashCounter == 0)
	  	{
	  		bleached =!bleached; //Toggle
	  		internalflashCounter = this->bleach_after;
	  	}
  	#endif
  } // End of Flash()



/*  //Outputs a string → Beautified and labelled
  void __attribute__((always_inline)) Profile()
  {

  }*/


  //Friend Declarations
  friend std::ostream& operator<< (std::ostream &stream, const Particle &part);


}; //End of class Particle



//! Stream operator overload that puts Particle info to the ostream.
std::ostream& operator<< (std::ostream &stream, const Particle &part)
{
   stream << part.partid << FCS_DSep << part.D << FCS_DSep 
          << part.qm_yield;

   #if FCS_PER_PART_STATS == 1
    stream << FCS_DSep << part.dist << FCS_DSep <<  part.dist_sq << '\n';
   #else
    stream << '\n';
  #endif

  return stream;

} //End of friend overload operator<<



class Fluorophore_Base
{

	int partid;
	V pos;
	V pos_init;
	fl_state_t state;
	color_t color = color_t::default_color;
	static Geometry geo(geo_core_t::point, geo_t::not_defind);
	
	Fluorophore_Base(): geo(Geometry(geo_core_t::point, geo_t::not_defind))
	{}

	int inline get_partid() const
	{
		return this->partid;
	}
	
	V inline get_pos() const
	{
		return this->pos;
	}

	int inline get_init_pos() const
	{
		return this->pos_init;
	}


	fl_state_t inline get_state() const
	{
		return this->state;
	}


	color_t inline get_color() const
	{
		return this->color;
	}

	double virtual get_qm_yield() = 0; //Interface functions
	double virtual get_excitation_p() = 0; //Interface functions
	double virtual get_brightness() = 0; //Interface functions
};


enum class geo_core_t
{
	not_defined = 0,
	point;
	circle,
	sphere,
	spherocylinder,
};



class Geometry
{
	geo_core_t core = geo_core_t::not_defined;
	geo_t geo = geo_t::not_defind;

	Geometry()
	{}
};