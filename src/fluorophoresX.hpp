#pragma once
#include "fluorophore.hpp"

/*
*	@brief It is an instance of Fluorophore_Basic class. It is a simple colorless Fluorophore with a fixed quantum yield and no additional photo-physical behaviour. It has a quantum_yield of 1.0. And is delf diffusive (inherits Diffusive).
*/
class FluorophoreX05 : public Point_Particle, Fluorophore_Basic, Fluorophore_Metric, Diffusive
{
public:

//Members

	unsigned long int Emit_count = 0; //! Number of photons emitted which equalls the count of photons absorbed
	
//Constructors

	/**
	 * @brief Default Constructor - Sets the color to colorless explicitly
	 * */
	FluorophoreX05(const V Pos = V()) : Point_Particle(Pos), Fluorophore_Basic(color_t::colorless), Diffusive(1.0)
	{}

	/**
	 * @brief Contructor that sets the diffusivity and the QM yield of the Fluorophore.
	 * */
	FluorophoreX05(const V Pos = V(), const double Diffusivity) : Point_Particle(Pos), Fluorophore_Basic(color_t::colorless), Diffusive(Diffusivity)
	{}

//Fluorophore_Basic overrides
	/**
	 * @brief Returns a constant Quantum Yield ('''fixed_qm_yield'''), which represents Photons-Emitted/Photons-Absorbed.
	 * */
	double inline get_qm_yield() const override
	{
		return 1.0;
	}


	void inline try_absorb(double(*unirnd)()) override
	{
		this->Fl_state = fl_state_t::Excited;
	}

	void inline try_emit(double(*unirnd)()) override
	{
		if(this->Fl_state == fl_state_t::Excited)
		{
			relax_state();
			Emit_flag = true;
			this->Emit_count++;	
		}	
	}

//Fluorophore_Metric overrides
	/**
	 * @brief Returns the number of photons absorbed.
	 * */
	unsigned long int inline get_absorbed_count() const override
	{
		return this->Emit_count;
	}

	/**
	 * @brief Returns the number of photons emitted.
	 * */
	unsigned long int inline get_emitted_count() const override
	{
		return this->Emit_count;
	}


};


/*
*	@brief It is an instance of Fluorophore_Basic class. It is a simple colorless Fluorophore with a fixed quantum yield and no additional photo-physical behaviour. The only parameter it takes is diffusivity.
*/
class FluorophoreX06 : public Point_Particle, Fluorophore_Basic, Fluorophore_Metric, Diffusive
{
public:

//Members
	unsigned long int Fixed_qm_yield = 0; //! Fixed QM yield of the particle
	unsigned long int Absorb_count = 0; //! Number of photon absorbtions
	unsigned long int Emit_count = 0; //! Number of photon absorbtions

//Constructors

	/**
	 * @brief Default Constructor - Sets the color to colorless explicitly
	 * */
	FluorophoreX06(const V &Pos) : Point_Particle(Pos), Fluorophore_Basic(color_t::colorless), Diffusive(1.0), Fixed_qm_yield(1.0)
	{}

	/**
	 * @brief Contructor that sets the diffusivity and the QM yield of the Fluorophore.
	 * */
	FluorophoreX06(const V &Pos, const double Diffusivity, const double Fixed_qm_yield) : Point_Particle(Pos), Fluorophore_Basic(color_t::colorless), Diffusive(Diffusivity), Fixed_qm_yield(Fixed_qm_yield)
	{}

//Fluorophore_Basic overrides

	/**
	 * @brief Returns the Quantum Yield, which represents Photons-Emitted/Photons-Absorbed
	 * */
	double __attribute__((always_inline)) get_qm_yield() const override 
	{
		double yield = get_emitted_count()/get_absorbed_count();
		//assert(yield <= 1.0, "Invalid quantum_yield value!");
		return yield;
	}


	void inline try_absorb(double(*unirnd)()) override
	{
		this->Fl_state = fl_state_t::Excited;
	}

	void inline try_emit(double(*unirnd)()) override
	{
		if(this->Fl_state == fl_state_t::Excited)
		{
			relax_state();
			
			bool emit_photon = (unirnd() <= this->Fixed_qm_yield);
			this->Emit_flag = emit_photon;
			this->Emit_count += emit_photon;	
		}	
	}

//Fluorophore_Metric overrides

	/**
	 * @brief Returns the number of photons absorbed.
	 * */
	unsigned long int inline get_absorbed_count() const override
	{
		return this->Absorb_count;
	}

	/**
	 * @brief Returns the number of photons emitted.
	 * */
	unsigned long int inline get_emitted_count() const override
	{
		return this->Emit_count;
	}

// Extra function

	/**
	 * @brief Returns a constant Quantum Yield ('''fixed_qm_yield'''), which represents Photons-Emitted/Photons-Absorbed.
	 * */
	double inline get_fixed_qm_yield() const
	{
		return this->Fixed_qm_yield;
	}

};



