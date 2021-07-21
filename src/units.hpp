#pragma once

#include <cmath>
#include <sstream>
#include <iomanip>

#include "macros.hpp"


class Units
{
public:

/////////////////////////////////////////////////| Member List
  
  //Length Scale
  double Sigma = 1e-9;

  //Energy Scale
  double Epsilon = 1.0;

  //Viscosity Scale
  double Eta = CONST_WATER_VISCOSITY;

  //Needs to be calculated
  double Gamma_scale = Eta * Sigma;
  double Mass_scale = Gamma_scale * Gamma_scale * Sigma * Sigma / Epsilon;
  double Time_scale = Gamma_scale * Sigma * Sigma / Epsilon;
  double Force_scale = Epsilon / Sigma;

  double T_reduced = Epsilon / CONST_Kb;

/////////////////////////////////////////////////////////| Member List
  

  ////Inputs → Sigma, Epsilon, Viscosity (Eta)
  void set_scale_SEE(double Sigma, double Epsilon, double Viscosity)
  {
    
      this->Sigma = Sigma;
      this->Epsilon = Epsilon;
      this->Eta = Viscosity;  

      set_quantities(); //Recalculate all quantities
  }


  ////Inputs → Sigma, Epsilon, Viscosity (Eta)
  void set_scale_STE(double Sigma, double Temp, double Viscosity)
  {  
      this->Sigma = Sigma;
      this->Epsilon = Temp * CONST_Kb;
      this->Eta = Viscosity;

      set_quantities(); //Recalculate all quantities
  }

  /**
   * @brief Recalculates the other scales.*/
  void set_quantities()
  {
    this->Gamma_scale = Eta * Sigma;
    this->Mass_scale = Gamma_scale * Gamma_scale * Sigma * Sigma / Epsilon ;
    this->Time_scale = Gamma_scale * Sigma * Sigma /Epsilon;
    this->Force_scale = Epsilon / Sigma;

    //Reduced Temperature
    this->T_reduced = this->Epsilon / CONST_Kb;
  }

// stor_xxx() functions  

  //1
  double stor_volume() const
  {
    return Sigma * Sigma * Sigma;
  } 

  //2
  double stor_mass() const
  {
    return Mass_scale;
  }

  //3
  double stor_time() const
  {
    return Time_scale;
  }

  //4
  double stor_force() const
  {
    return Force_scale;
  }

  //5
  double stor_viscosity() const
  {
    return Eta;
  }

  //6
  double stor_D()  const
  {
    return Epsilon/Gamma_scale;
  }

  //7
  double stor_difftimescale() const
  {
    return Time_scale;
  }

//rtos_xxx() functions

  //1
  double rtos_volume() const
  {
    return 1/stor_volume();
  } 

  //2
  double rtos_mass() const
  {
    return 1/stor_mass();
  }

  //3
  double rtos_time() const
  {
    return 1/stor_time();
  }

  //4
  double rtos_force() const
  {
    return 1/stor_force();
  }

  //5
  double rtos_viscosity() const
  {
    return 1/stor_viscosity();
  }

  //6
  double rtos_D() const
  {
    return 1/stor_D();
  }

  //7
  double rtos_difftimescale() const
  {
    return 1/stor_difftimescale();
  }

  /////////////////////////////////////////////////////////| LANG UNITS


  std::string profile(double step_size, double total_steps) const
  {
    std::ostringstream buffer;
    buffer << std::setprecision(FCS_FLOAT_SHORT_PRECISION) << std::boolalpha << std::scientific;

    buffer << "————→   Units — Corresponding Real(SI) Unit per 1.0 Sim Unit  ←————\n\n";
    
    buffer << " • Sigma(m) : " << this->Sigma << " (Set)\n";
    buffer << " • Temp(K) : " << this->Epsilon/CONST_Kb << " (Set)\n";
    buffer << " • Thermal Energy - kBT(J) : " << this->Epsilon << " (Set)\n";
    buffer << " • Viscosity (Pa • s): " << this->Eta << " (Set)\n";

    buffer << " • Gamma : " << this->Gamma_scale << "\n\n";

    buffer << " • Time Scale(s) : " << this->Time_scale << '\n';
    buffer << " • One Time Step(s) - " << step_size << " : " << this->Time_scale * step_size << '\n';
    buffer << " • Total Simulation Time(s) - " << total_steps << " steps : "<< this->Time_scale * total_steps << "\n\n";

    buffer << " • Mass(kg) : " << this->Mass_scale << '\n';
    buffer << " • Force(N) : " << this->Force_scale << '\n';
    buffer << " • Diffusivity D : " << this->stor_D() << '\n';

   return buffer.str();
  }

}; //End of class Units

