//indevelopment.hpp

#pragma once


template <unsigned int Length, unsigned int Theta>
Fl_Mesh()
{
	sps::partid_t parent_id;

	double vec2D;
	bitset2D occupancy[Length][Theta];


	CheckFlash(const Veff &psf, const Spherocylinder &sph)
	{
		Fl_mesh_core mesh = Fl::MeshGenerateSphMesh(sph);

		unsigned int counter = 0;
		for(unsigned int i = 0; i < size; i++)
		{
			counter += psf.bound(mesh.at(i).pos) * occupancy.at(i);
		}			//    (alias - invol)
	}
}


void pbc_with_relax(const Particle &part)
{
	V temp = part.pos;
	this->pbc(part.pos);
	if(temp.not_equal_to(part.pos, 1e-8)); //Tolerance of 10^-8
		part.relax_state();
}





void __attribute__((always_inline)) msd_calc(double &MSDi, unsigned int &InVolCount)
{
	for(auto &part : partlist) 
	{
	  
	  V msd_vec = part.pos - part.init_pos;
	  #if FCS_ENABLE_PBC == 1
	  	PBC(msd_vec); //TODO → Ask if this is strictly necessary
	  #endif 

	  MSDi += msd_vec.size_sq();
	  InVolCount =  veff.invol(part.pos);
	}
}

///// Freeze Photophysics time coordinate


//Loop → detection
for(auto &part : this->partlist)
{
	//Exposed Machinary Design Pattern
	//det_red.detect(det_red.lossy_filter(part, gauss_rnd));
	//det_green.detect(det_red.lossy_filter(part, gauss_rnd))

	#pragma unroll //unroll this loop in compilation
	for(auto &det : detectorlist) 
	{
		det.detect(det.lossy_filter(part, gaussrnd));
	}
}
///// Unfreeze Photophysics time coordinate



for(auto &part : this->partlist)
{
	InVolCount =  veff.invol(part.pos);
}



enum class geo_core_t
{
	not_defined = 0,
	point,
	circle,
	sphere,
	spherocylinder,
};

enum class geo_t
{
	not_defined = 0,
	fluorophore,
	spc_patched,
	sphere_patched,
	spherocylinder,
};

class Geometry
{
public:
	geo_core_t core = geo_core_t::not_defined;
	geo_t geo = geo_t::not_defined;

	Geometry(): core(geo_core_t::not_defined), geo(geo_t::not_defined)
	{}


	Geometry(geo_core_t core, geo_t geo): core(core), geo(geo)
	{}

};


if(PSF - Allows get_psf_prob() )
{
	fluorophoreX06.try_absorb(SimCounter, gaussrnd);
}

//Next cycle
fluorophoreX06.try_emit(SimCounter);

detect_cycle()
{

}



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










class Cubic_Prisim_Box
{
public:

//Members
	bool Symmetric = true;
	V bounds; //! (l, b, h) coordinates of the cubic prism box
	V min_bounds;
	V max_bounds;

	Cubic_Prisim_Box(V dims, ) :

	/**
	 * @brief Returns if the given coordinate is within the bounds of the box. - Interface.
	 * */
	bool invol(const V &pos) [alias inbox] = 0;


	/**
	 * @brief Returns a random coordinate within the box - Interface.
	 * @param Entropy Source - a function that returs uniformly distributed random numbers of type double.
	 * */
	V inline rnd_pos((double)(*drnd)) = 0;


	/**
	 * @brief Returns a pointer to the entropy source of the box. This pointer returns a pointer to a function that returns a random double belonging to [0,1] and is uniformly distributed in the domain - Interface.
	 */
	(double)(*drnd) entropy_source() = 0;

	/**
	 * @brief Evolves the box over time. It executes the simulation - Interface.
	 * @param Clock - A clock object that manages the timing and respective loop partioning.
	 * @param Camera - A camera object that takes snapshots at certain intervals and manages its respective loop partitioning.
	 * 
	 * @It outputs data to a set file in append mode.
	 * */
	void evolve(Clock &clock, Camera &camera) = 0;

	/**
	 * @returns a string representation for dashboard display - Interface.
	 * */
	std::string profile() = 0;

	/**
	 * @brief Outputs a file with the complete state of the box - Interface.
	 * @param filename The filename to save the state dump
	 * @param ext - Extension of the filename (defaults to json) and is used to deduce specific implementation.
	 * */
	void state_dump(std::string filename, std::string ext = "json") = 0;

	/**
	 * @brief Calls the analysis module after the system has evolved. Fails when the Simcounter is zero - Interface.
	 * */
	void post_analysis() = 0;

	/**
	 * @brief Adds identical fluorophores of a given configuration to the box with random positions.
	 * @param fls - Fluorophore Object
	 * @param N - number of clones to make
	 * */
	void add_particles(Fluorophore_Basic &fls, unsigned int N = 1) = 0;

	/**
	 * @brief Adds a new detector to the box
	 * @param The detector to copy and use with the box.
	 * */
	void add_detector(Detector &detector) = 0;

};


