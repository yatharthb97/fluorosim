#pragma once


#include "./submodules/vector.hpp"
#include<vector>
#include<array>


//Header file that defines priliminary Euclid framework.


/**
 * @brief Defines a finite set of specific geometry for entities in Euclidean space.
 * */
enum class geo_t
{
	not_defined = 0,
	fluorophore,
	PSF
};

/**
 * @brief Defines a finite set of Core Geometries.
 * */
enum class geo_core_t
{
	not_defined = 0,
	point,
	circle,
	sphere,
	spherocylinder,
	ellipsoid,
	cube
};

/**
 * @brief A wrapper class that defines the Euclidean geometry of a given entity. It also contains specific interfaced methods that relate to the geometry of the entity.
 * */
class Geometry
{
public:

	geo_core_t Core; //! The Core Geometry of the object
	geo_t Geo; //! The context specific geometry that defines specific visual features. The specific visual features are irrelavent to shape based / excluded volume interactions.

	/**
	 * @brief The default constructor constructs an undefined geometry. */
	Geometry(): Core(geo_core_t::not_defined), Geo(geo_t::not_defined)
	{}

	/**
	 * @brief The constructor takes in two geometric state-specifiers to construct.*/
	Geometry(geo_core_t Core, geo_t Geo): Core(Core), Geo(Geo)
	{}

	/**
	 * @brief Accessor for the geometry of the particle.*/
	geo_t inline get_geo() const
	{
		return this->Geo;
	}
 
 	/**
 	 * @brief Accessor for the Core geometry of the particle.*/
	geo_core_t inline get_core_geo() const
	{
		return this->Core;
	}

	/**
	 * @brief Returns the volume of the given geometry - Interface.
	 * */
	double inline virtual get_vol() const = 0;

	/**
	 * @brief Returns the Surface area of the given geometry - Interface.*/
	double inline virtual get_area() const = 0;

	/**
	 * @brief Returns the relavent dimensions for the given geometry - Interface.
	 * */
	double inline virtual get_dim() const = 0;

}; //End of class Geometry


 
class Point_Particle //Change to Cartesian_Point
{
public:

//Members
	V Pos; //! Position of the particle

//Methods

	/**
	 * @brief Constructor
	 * */
	Point_Particle(const V &Pos): Pos(Pos)
	{}


	/**
	 * @brief  Translates the point particle with the given displacement.
	 * */
	void virtual translate(const V &displacement)
	{
		this->Pos += displacement;
	}


	/**
	 * @brief  Translates the point particle with the given displacement and then applies the boundary (condition) function.
	 * @param boundary_fn is a void return dunction that takes a position reference as arguement and applies the boundary_fn to the position.
	 * */
	void virtual translate(const V &displacement, void(*boundary_fn)(V &pos))
	{
		this->Pos += displacement;
		boundary_fn(this->Pos);
	}

	/**
	 * @brief Get the position of the particle (Special alias of Point_Particle::get_pos())
	 * */
	V __attribute__((always_inline)) position() const
	{
		return get_pos();
	}

	/**
	 * @brief Get the position of the point particle - Interface.
	 * */
	V virtual inline get_pos() const
	{
		return this->Pos;
	}

	/**
	 * @brief Sets the position of the Point_Particle.
	 * */
	void virtual inline set_pos(const V &new_pos)
	{
		this->Pos = new_pos;
	}

};








