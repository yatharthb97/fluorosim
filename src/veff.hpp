#pragma once
#include <assert.h>

#include "submodules/vector.hpp"
#include "particle.hpp"
#include "types.hpp"
#include "macros.hpp"
//Header file that defines Veff objects

/**
 * @brief Base Interface class for Effective Volume Objects (Veff). It represents a 3D volume formed by the Point Spread function of the laser beam. The object is formed independently of the laser object. The associated volume is constrained to be *Axis-Aligned* to the global bounding Box coordinates. to The class is completely interfaced and cannot be instanciated.
 * */
class Veff
{

  //1
  /**
   * @brief Returns a type "name" for the PSF profile of the Veff - Interface.
   * */
  std::string virtual inline get_veff_type() const = 0;

  //2
  /**
   * @brief Returns the "Structure Factor", which is a measure of assymetry of the PSF. By convention, it is assymetry along the z-axis.
   * */
  double virtual inline get_sf() const = 0;
  
  //3
  /**
   * @brief Returns the radial raduis of the PSF. By convention, it is the x-y radius or in 3D-Assymetric cases the x-radius only.
   * */
  double virtual inline get_rad_radius() const = 0;
  
  //4
  /**
   * @brief Returns the "Assymetric" z-radius. For shpheres this function has the exact same behaviour as ```Veff::radial_radius()```.
   * */
  double virtual inline get_z_radius() const = 0;
  
  
  //5
  /**
   * @brief Intensity function that returns a normalized intensity value based on the position of the passed Point_Particle.
   * */
  n_intensity_t virtual inline intensity(const Point_Particle&) const = 0;

  //6
  /**
   * Returns if a given Pont_Particle is in within or on the surface of the volume.
   * */
  bool virtual inline in_vol(const Point_Particle&) const = 0;
};


/**
 * @brief 3D_Gaussian effective volume
 * */
class Gaussian_3D : public Veff, Geometry
{

public:


  V Centre; //! Centre of the effective volume.
  V Radii; //! Vector Representation of all the 3 radii.
  //PSF Function
  V Exponents; //! The exponent factors in the 3D gaussian equation (PSF intensity function).
  double Norm = 1.0; //! The Normalization applied to the PSF intensity function.

  //Radii
  double Radius = 1.0; //! The radial radius of the Veff.
  double Sf = 1.0; //! The Structure factor of the Veff

  Gaussian_3D(double Radius, double Sf, V centre = V()) : Radius(Radius), Sf(Sf), Centre(Centre), Geometry(geo_core_t::ellipsoid, geo_t::PSF)
  {
    
    this->Radii = V(this->Radius, this->Radius, this->Radius * this->Sf);

    double Radius_sq = this->Radius * this->Radius;
    this->Exponents =  V(-2.0/Radius_sq, -2.0/Radius_sq, -2.0/(Radius_sq * this->Sf));
  }

//class Veff overrides

  //1
  /**
   * @brief A string descriptor for the PSF.
   * */
  std::string get_veff_type() const override
  {
    return "3D Gaussian PSF - Ellipsoid Veff";
  }

  //2
  /**
   * @brief Accessor of the Structure factor value.
   * */
  double get_sf() const override
  {
    return this->Sf;
  }

  //3
  /**
   * @brief Returns the radial raduis of the PSF. By convention, it is the x-y radius or in 3D-Assymetric cases the x-radius only.
   * */
  double inline get_rad_radius() const override
  {
  	return this->Radius;
  }

  //4
  /**
   * @brief Returns the "Assymetric" z-radius. For shpheres this function has the exact same behaviour as ```Veff::radial_radius()```.
   * */
  double inline get_z_radius() const override
  {
  	return this->Radii.Z();
  }


  //5
  /**
   * @brief Returns the intensity value based on the relative Position of the point_Particle relative to the PSF Centre. Process →  Calculate relative poistion w.r.t PSF centre. Then multiply the square of it by the precalculated Exponents. Then add (accumulate). At the end normalize. 
   * */
  n_intensity_t intensity(const Point_Particle &point) const override
  {
  	V exps = V(point.position() - this->Centre).square();
  	exps.comp_mul(this->Exponents);
  	
  	double exponent = exps.accumulate();
  	return this->Norm * std::exp(exponent);
  }

  //6
  /**
   * @brief Checks whether the particle is inside the veff.
   * */
  bool in_vol(const Point_Particle &point) const override
  {
    V temp = V(point.position() - this->Centre);
    temp.comp_divide(this->Radii);
    temp.comp_square();

    return (temp.accumulate() <= 1.0) || false;
  }


//class Geometry ovverrides
  
  //7
  /**
   * @brief Returns the calculated volume of the Veff. \f$ vol = \pi^{3/2} r^{3} \cdot sf  \f$.
   * */
  double get_vol() const override
  {
    return CONST_PI_pow3by2 * this->Radius * this->Radius *  this->Radius * this->Sf;
  }

  //8
  /**
   * @brief Implementation pending (TODO). Returns the Surface area of the Ellipsoid.
   * */
  double inline get_area() const override
  {
    assert(false);
    return 0; //dead code
  }

  //9
  /**
   * @brief Returns the relavent dimensions of the Veff.
   * */
  double inline get_dim() const override
  {
    return 3.0;
  }


};

/**
 * @brief Uniform spherical Veff. It describes a PSF intensity function which is 1.0 inside the volume of the sphere and 0.0 outside.
 * */
class USphere : public Veff, Geometry
{
 
public:

  V Centre; //! Centre of the effective volume.
  double Norm = 1.0; //! The Normalization applied to the PSF intensity function.

  double Radius; //! The radial radius of the Veff.
  double Radius_sq; //! The square of the radial raduis of the Veff.

  USphere(double Radius, V centre = V()) : Radius(Radius), Centre(Centre), Radius_sq(Radius * Radius), Geometry(geo_core_t::sphere, geo_t::PSF)
  {}

//class Veff overrides

  //1
  /**
   * @brief A string descriptor for the PSF.
   * */
  std::string inline get_veff_type() const override
  {
    return "Uniform Sphere - PSF & Veff";
  }

  //2
  /**
   * @brief Accessor of the Structure factor value.
   * */
  double inline get_sf() const override
  {
    return 1.0;
  }

  //3
  /**
   * @brief Returns the radial raduis of the PSF. By convention, it is the x-y radius or in 3D-Assymetric cases the x-radius only.
   * */
  double inline get_rad_radius() const override
  {
  	return this->Radius;
  }

  //4
  /**
   * @brief Returns the "Assymetric" z-radius. For shpheres this function has the exact same behaviour as ```Veff::radial_radius()```.
   * */
  double inline get_z_radius() const override
  {
  	return this->Radius;
  }


  //5
  /**
   * @brief Returns the intensity value based on the relative Position of the point_Particle relative to the PSF Centre. Process →  Calculate relative poistion w.r.t PSF centre. Then multiply the square of it by the precalculated Exponents. Then add (accumulate). At the end normalize. 
   * */
  n_intensity_t inline intensity(const Point_Particle &point) const override
  {
    return (this->Norm * in_vol(point) + 0.0);

  }

  //6
  /**
   * @brief Checks whether the particle is inside the veff.
   * */
  bool inline in_vol(const Point_Particle &point) const override
  {
    V temp = V(point.position() - this->Centre).square();
    return (temp.accumulate() <= this->Radius_sq) || false;
  }

// class Geometry overrides

  //7
  /**
   * @brief Returns the calculated volume of the Veff. \f$ vol = \frac{4}{3) \pi r^{3} \cdot sf  \f$.
   * */
  double inline get_vol() const override
  {
    return 4/3 * CONST_PI * this->Radius_sq * this->Radius;
  }

  //8
  /**
   * @brief Returns the Surface Area of the Sphere Veff. \f$ SA = 4\pi r^{2} \f$
   * */
  double inline get_area() const override
  {
    return 4 * CONST_PI * this->Radius_sq;
  }

  //9
  /**
   * @brief Returns relavent dimensions — 3 for the sphere.
   * */
  double inline get_dim() const override
  {
    return 3.0;
  }


};


class UCube : public Veff, Geometry
{
 
public:

  double Norm = 1.0; //! The Normalization applied to the PSF intensity function.

  double Half_edge = 0.5; //! The radial radius of the Veff.
  V Centre; //! Centre of the effective volume.
  V Bounds_min; //! Minimum of the bounding box coordinates (Origin for an assymetric box).
  V Bounds_max; //! Maximum of ht ebounding box cooedinate (The diagonal end of the Origin for an assymetric box)

  UCube(double Edge, V centre = V()) : Half_edge(Edge/2), Centre(Centre), Geometry(geo_core_t::cube, geo_t::PSF)
  {
  	V half_edge_scalar;
    half_edge_scalar.xyz(Half_edge); //V(Half_edge, Half_edge, Half_edge)

    this->Bounds_min = Centre - half_edge_scalar;
  	this->Bounds_max = Centre + half_edge_scalar;
  }

//class Veff overrides

  //1
  /**
   * @brief A string descriptor for the PSF.
   * */
  std::string inline get_veff_type() const override
  {
    return "Uniform Cube - PSF & Veff";
  }

  //2
  /**
   * @brief Accessor of the Structure factor value.
   * */
  double inline get_sf() const override
  {
    return 1.0;
  }

  //3
  /**
   * @brief Returns the radial raduis of the PSF. By convention, it is the x-y radius or in 3D-Assymetric cases the x-radius only.
   * */
  double inline get_rad_radius() const override
  {
  	return this->Half_edge;
  }

  //4
  /**
   * @brief Returns the "Assymetric" z-radius. For shpheres this function has the exact same behaviour as ```Veff::radial_radius()```.
   * */
  double inline get_z_radius() const override
  {
  	return this->Half_edge;
  }

  //5
  /**
   * @brief Returns the intensity value based on the relative Position of the point_Particle relative to the PSF Centre. Process →  Calculate relative poistion w.r.t PSF centre. Then multiply the square of it by the precalculated Exponents. Then add (accumulate). At the end normalize. 
   * */
  n_intensity_t inline intensity(const Point_Particle &point) const override
  {
    return (this->Norm * in_vol(point)) + 0.0;
  }

  //6
  /**
   * @brief Checks whether the particle is inside the veff.
   * */
  bool inline in_vol(const Point_Particle &point) const override
  {
    bool result = 

    point.position().X() >= Bounds_min.X() && 
    point.position().X() <= Bounds_max.X() &&

    point.position().Y() >= Bounds_min.Y() && 
    point.position().Y() <= Bounds_max.Y() &&

    point.position().Z() >= Bounds_min.Z() && 
    point.position().Z() <= Bounds_max.Z();

    return result;
  }


//class Geometry overrides

  //7
  /**
   * @brief Returns the calculated volume of the Veff. \f$ vol = a^{3}\f$, a is the edge of the cube.
   * */
  double inline get_vol() const override
  {
    double Edge = this->Half_edge * 2;
    return Edge * Edge * Edge;
  }


  //8
  /**
   * @brief Returns the Surface Area of the Sphere Veff. \f$ SA = 6 a^{2} \f$, where a is the edge of the cube.
   * */
  double inline get_area() const override
  {
    double Edge = this->Half_edge * 2;
    return 6 * Edge * Edge;
  }

  //9
  /**
   * @brief Returns relavent dimensions — 3 for the cube.
   * */
  double inline get_dim() const override
  {
    return 3.0;
  }


};