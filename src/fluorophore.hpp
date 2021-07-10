#pragma once

#include<vector>

#include "./submodules/vector.hpp"
#include "types.hpp"
#include "colors.hpp"
#include "particle.hpp"


/**
 * @brief Finite state representation of Fluorophore Photophysical States.
 * */
enum class fl_state_t
{
	Ground = 0,
	Excited = 1,
	Triplet = 2,
	Bleached = 3
};


/**
 * @brief Describes a basic Fluorophore model that has a color and a fl_state_t. Aditionally it contains Photo_cycles which represent the number of active fluorophores this entity represents. The Geometry is defined to <Point, Fluorophore>
 * 
 * */
class Fluorophore_Basic : public Geometry
{
public:

//Members
	color_t Color; //! Color of the Fluorophore
  fl_state_t Fl_state; //! Photophysics State → {enum class fl_state}
  unsigned int Photo_cycles = 1; //! Number of photo-cycles performed. This informally represents the number of distinct fluorophores this instance of ```Fluorophore_Basic``` represents.

  simcounter_t Last_emit = 0; //! Simulaton Counter of last emission → It is the temporal state-specifier and a memory variable of the fluorophore. It can answer questions like - When did this fl last emmit a photon? or For a given time t, has there been an emission which is simply the result of (t == Last_emit).


//Methods

  /**
   * @breif Default constructor.*/
  Fluorophore_Basic(): Color(color_t::colorless), Fl_state(fl_state_t::Ground), Geometry(geo_core_t::point, geo_t::fluorophore)
  {}

  Fluorophore_Basic(color_t Color): Color(Color), Fl_state(fl_state_t::Ground), Geometry(geo_core_t::point, geo_t::fluorophore)
  {}


	/**
	 * @brief Gets color of the Fluorophore.
	 * */
	color_t __attribute__((always_inline)) get_color() const
	{
		return this->Color;
	}

	/**
	 * @brief Returns the number of photo-cycles performed on the fluorophores for each photophysics move.
	 * */
	unsigned int __attribute__((always_inline)) get_photo_cycles() const
	{
		return this->Photo_cycles;
	}

	/**
	 * @brief Returns the Simulation time of last photon emission.
	 * */
	simcounter_t __attribute__((always_inline)) last_emit() const
	{
		return this->Last_emit;
	}

	/**
	 * @brief Returns the Quantum Yield, which represents Photons-Emitted/Photons-Absorbed  Interface.
	 * */
	double virtual inline get_qm_yield() const = 0;


	/**
	 * @brief Returns qm_yield * photon_output.
	 * */
	double __attribute__((always_inline)) get_intrinsic_brightness() const
	{
		return get_qm_yield() * get_photo_cycles();
	}

	bool __attribute__((always_inline)) relax_state()
	{
		this->Fl_state = fl_state_t::Ground;
	}
	
//Photo_Physics Interface/Space

	/**
	 * @brief Calls the fluorophore to absorb a photon. This function results in fl_state increment of the fluorophore. - Interfaced.
	 * @param Stochastic source which returns uniform random values [0,1] of type double.
	 * */
	void virtual try_absorb(double(*unirnd)()) = 0;

		/**
	 * @brief Calls the fluorophore to emit a photon. The resulting fl_state change belongs to the set → {no-state-change, relaxation-photo-emission, relaxation-NO-photon-emission} - Interfaced. Upon emission, it sets the <c>Emit_flag</c>.
	 * @param Stochastic source which returns uniform random values [0,1] of type double.
	 * */
	void virtual try_emit(double(*unirnd)()) = 0;

	bin_detect_t Emit_flag = false; //! Indicates that for the current time coordinate, a photon was emitted by the fluorophore. This flag is read by a detector object of appropriate color and is a "binary detectable" type.

}; // End of class Fluorophore_Basic


/**
 * @brief - Add-on adapter that can be used for bookeeping of absorbed and emitted counts. 
 * */
class Fluorophore_Metric
{

public:
		
	/**
	 * @brief Returns the Number of photons absorbed - Interface.
	 * */
	unsigned long int virtual inline get_absorbed_count() const = 0;

	/**
	 * @brief Returns the Number of photons emitted - Interface.
	 * */
	unsigned long int virtual inline get_emitted_count() const = 0;

	/**
	 * @brief Alias of Fluorophore_Metric::get_emitted_count().
	 * */
	unsigned long int inline get_cpp() const
	{
		return get_emitted_count();
	}

}; // End of class Fluorophore_Metric


/**
 * @brief Describes an entity that can diffuse. It contains a parameter called D which represent the diffusive coefficient.
 * */
class Diffusive
{
public:

	double Diffusivity; //! Diffusivity coefficient of the entity.

	/**
	 * @brief Constructor.*/
	Diffusive(double Diffusivity): Diffusivity(Diffusivity)
	{}

	/**
	 * @brief Accessor for Diffusivity member.
	 * */
	double inline get_D() const
	{
		return this->Diffusivity;
	}

	/**
	 * @brief Alias of get_D() member function.
	 * */
	double __attribute__((always_inline)) get_Diffusivity() const
	{
		return get_D();
	}
};


class Entity
{
	std::string name;
	std::string description;

	

	/**
	 * @ brief - Checks for aphysical states. Returns the vitality of the entity based on a set criteria.
	 * */
	bool inline virtual vitality() = 0;

	/**
	 * @ brief - Checks for aphysical states. Returns the vitality of the entity based on a set criteria and an input of one or more doubles and 3-Vectors (V).
	 * */
	bool inline virtual vitality(double *env1, V *env2) = 0;

};