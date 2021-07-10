#pragma once

#include <sstream>
#include "types.hpp"

//Header file for Camera Object

/**
 * @brief Simple object that represents the camera recording the Configuration space of the partiles in the box. It saves the number of snapshots to save. The minimum number of Snapshots possible is 1. It also generates the filenames used to save the frames — has methods and counting system.
 * */
class Camera
{
private:

  unsigned int Snapshots = 1;//! Number of Snapshots to record.
  counter_t Frame_Counter = 1; //! By convention, 0 is the inital position.
  
  constexpr static const char* Init_Name= "0"; //! Name given to the inital configuration frame.
  constexpr static const char* Suffix = ""; //! Filename Suffix.
  constexpr static const char* Prefix = ""; //! Filename Prefix.
  constexpr static const char* Ext = ".dat"; //! Filename Extension.

  /**
   * @brief Private method that generates the filename.
   * */
  std::string inline name_synthesis()
  {
    std::ostringstream stream;
    stream << this->Suffix << this->Frame_Counter << this->Prefix << this->Ext;
    
    this->Frame_Counter++;
    return stream.str();
  }


public:
  /**
   * @brief Default Constructor.
   * @param Number of snapshots to save.
   * */
  Camera(unsigned int Snapshots): Snapshots(Snapshots)
  {}

  /**
   * @brief Returns the number of snapshots to save.
   * */
  discrete_freq_t get_snaps() const
  {
    return (Snapshots == 0)*1 + 
           (Snapshots != 0)*Snapshots;
  }

  /**
   * @breif Generates the name of the inital snapshots —  special method for Configuration space at time t = 0.
   * */
  std::string get_init_snap_name() const
  {

    std::ostringstream stream;
    stream << this->Suffix << this->Init_Name << this->Prefix << this->Ext;
    return stream.str();
  }

  /**
   * @brief Returns a filename for the snapshot.
   * */
  std::string inline get_snap_name()
  {
    return this->name_synthesis();
  }

};