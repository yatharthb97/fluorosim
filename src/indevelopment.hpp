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


//Part::translate(V(x,y,z), (void)(*boundary_fn)(V &pos))


//Move All particles   D = 3, dim = 3 2*dim*D = 2*3*3
//<x^2> = 2*dim*D*dt = 4*D*t  ==> 18*t = MSD =<r^2>
void __attribute__((always_inline)) dynamic_sweep()
{
	for(auto &part : this->partlist)   //sqrt(4*i.D*dt)*gauss_dist(mt);
	{
	  double scalar = std::sqrt(2 * this->dim * part.D * clock.Brownian_dt);
	  part.pos += V::Generate(scalar, gaussrnd, 
	                          [](double x, double y) -> double {return x * y;})
	  
	  #if FCS_ENABLE_PBC == 1
	  	PBC(part.pos);
	  #endif
	}
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
//Loop → absorbance
for(auto &part : this->partlist)   //sqrt(4*i.D*dt)*gauss_dist(mt);
{
	part.try_absorb();
} //End of minor loop

//Loop → emittance
for(auto &part : this->partlist)   //sqrt(4*i.D*dt)*gauss_dist(mt);
{
	part.try_emit();
} //End of minor loop

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