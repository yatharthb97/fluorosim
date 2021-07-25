//macros.hpp
#pragma once
#include<cstdint>
//#include "modes.hpp"

//Type Declarations
using lint_t = long int; //lint_t -> long integer type
using ulint_t = unsigned long int; //ulint_t unsigned long integer type
using enum_int_t = std::uint_fast8_t; // Enum integer type



//Macro Declarations

//A. Data Seperator
#define FCS_DSep ','

//B. Float Precision for writing files
#define FCS_FLOAT_PRECISION	10
#define FCS_FLOAT_SHORT_PRECISION 5

//C. Extension for data files
#define FCS_DATAFILE_EXT ".dat"

//------------------------------------------------------------------------------------//

//1. Symmetric/Assymmetric Box → Enable Symmetric Box
#define FCS_SYMMETRIC_BOX 1

//2. Enable or disable PBC → 0 is disabled
#define FCS_ENABLE_PBC 1

//3. Use Gaussian Veff instead of Spherical Veff (Uniform Shphere Optimization)
#define FCS_VEFF_ELLIPSOID 1

//4. Enabling would restrict particle flashing to the first ellipsoid (Airy Disc). Enable for Optimization.
#define FCS_INVOL_CUTOFF 0

//5. Enables the offsetting of the PSF from the centre position
#define FCS_PSF_OFFSET 0

//----> These Macro Features don't affect results of simulations

//I. Take a sample of random number distributions and get a corresponding plot
#define FCS_RND_SAMPLING 0


//II. Enable Particle Tagging for a single particle defined by FCS_TAG_PARTID 
#define FCS_PART_TAGGING 0
#define FCS_TAG_PARTID 0

//III. Calculate Extra Statistics for all particles
#define FCS_PER_PART_STATS 1


//-----> Extra Features → Yet to be implemented





//Constants

//PI values //////////////////////////////////////
#define CONST_PI 3.14159265358979323846264338327950
#define CONST_PIby2 CONST_PI/2
#define CONST_PIby4 CONST_PI/4
#define CONST_PIby5 CONST_PI/5
#define CONST_PIby6 CONST_PI/6
#define CONST_PIby8 CONST_PI/8
#define CONST_PIby10 CONST_PI/10
#define CONST_PIby12 CONST_PI/12

//Pi to Power of 3/2
#define CONST_PI_pow3by2 5.56832799683170784528481798211883570

//Powers of 2 ///////////////////////////////////////////////
#define CONST_2pow1by6  1.1224620483093729814335330496791795
#define CONST_2pow1by12  1.05946309435929526456182529494634170
#define CONST_2pow1by3  1.259921049894873164767210607278228350

// Physical Constants ////////////////////////////////////////
#define CONST_Avogadro 6.02214076e+23
#define CONST_e 2.71828182845904523536028747
#define CONST_Kb 1.38064900e-23
#define CONST_WATER_VISCOSITY 0.000890 //milliPascal•sec → 0.890

//https://www.omnicalculator.com/physics/water-viscosity#:~:text=The%20dynamic%20viscosity%20of%20water%20at%20room%20temperature%20has%20a,water%20at%2020%C2%B0C.