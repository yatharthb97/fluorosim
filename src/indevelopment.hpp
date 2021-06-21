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


