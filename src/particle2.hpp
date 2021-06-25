#pragma once


#include "./submodules/vector.hpp"
#include<vector>
#include<array>


enum class fl_state_t
{
	Ground = 0,
	Excited = 1,
	Triplet = 2,
	Bleached = 3
};

enum class color_t
{
	colorless = 0,
	red,
	green,
	yellow
};


class Fluorophore_Base : public Geometry, Point_Particle
{
public:

	fl_state_t state = flp_state::Ground;
	color_t color = color_t::colorless;

	Fluorophore_Base()
	{
		this->core = geo_core_t::point; //Explicitly declare the core geometry
		this->geo = geo_t::fluorophore;
	}

	int inline get_flpid();

	flp_state_t inline get_state() const
	{
		return this->state;
	}

	color_t inline get_color() const
	{
		return this->color;
	}

	void relax_state()
	{
		this->state = flp_state::Ground;
	}
	
	bool has_emit_state() const
	{
		return (this->state == flp_state::Ground);
	}

	double virtual get_excitaton_p() = 0;

	bool try_absorb(const Veff_Base &veff, gaussrnd)
	{
		double absorbance = has_absorb_state() * get_excitaton_p() * veff.psf_prob(this->pos);

		bool try_ab = (gaussrnd <= absorbance);
		this->Absorb_count += try_ab;
		return try_ab;

	}

	bool try_emit(gaussrnd)
	{
		double relaxivity = (try_relax() * photo_emission_p());

		bool try_emit = (gaussrnd <=relaxivity);
		if(try_emit) {relax_state()};
		
		this->Emit_count += try_emit;
		this->Emit_flag = try_emit;
		
		return try_emit;
	}

  relax_state() = 0;
	try_relax() = 0;
	has_absorb_state() = 0;
	get_excitaton_p() = 0;
	get_photon_emission_p() = 0;

	double virtual get_qm_yield() const = 0; //Interface functions
	double virtual get_excitation_p() const = 0; //Interface functions
	double virtual get_brightness() const = 0; //Interface functions
};


class Fluorophore : public Fluorophore_Base
{
	public:


		
		double brightness = 0.0;
		double Pexcitation;



		//Quantum yield: efficiency of the energy transferred from incident light to emitted fluorescence (= number of emitted photons per absorbed photons).
		ulint_t counterAbsorbed, counterEmitted = 0;
		double get_qm_yield() const override
		{
			return double(counterAbsorbed) / double(counterEmitted);
		}


		void p_absorbed(double rnd) override
		{
			if(this->state == fl_state_t::Ground)
			{
				this->pAbsorbed++;
				jump_state(rnd);
			}
			//this->state = this->state + satic_cast<unsigned int>(1)
		}

		//void jump_state(double rnd)

		void p_emitted() override
		{
			this->pEmitted++;
		}

		double get_brightness() const override
		{
			return this->brightness;
		}

};

//How the fn is called
void p_excite(do_stateswitch() * do_excitation(rnd1) * veff.psf_prob(part.pos));



bool do_excitation(double &rnd)
{
	return (rnd <= Pexcitation);
}


double 







class ext_fl
{
	double stoke_shift = 0.0;
};



try_exite();
try_emit();