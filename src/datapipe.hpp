#pragma once

#include <sstream>
#include <vector>
#include<iomanip>

#include "macros.hpp"
#include "./submodules/filesystem.hpp"


/**
 * @brief Wrapper for all the stringstream objects → Single Interface
*/
class Datapipe
{
    
public:

    std::ostringstream stats;
    
    #if FCS_PART_TAGGING == 1
      std::ostringstream tag;
    #endif

    //distributions
    #if FCS_RND_SAMPLING == 1
      std::ostringstream u_dist;
      std::ostringstream gauss_dist;
    #endif

    //Reference of all streams
    std::vector <std::ostringstream *> pipelist;


    Datapipe()
    {
      //stats
      stats << std::setprecision(FCS_FLOAT_PRECISION);
      pipelist.emplace_back(&stats);

      //tag
      #if FCS_PART_TAGGING == 1
        tag << std::setprecision(FCS_FLOAT_PRECISION);
        pipelist.emplace_back(&tag);
      #endif

      //distributions
      #if FCS_RND_SAMPLING == 1
        pipelist.emplace_back(&u_dist);
        pipelist.emplace_back(&gauss_dist);
      #endif

    } // End of Datapipe()

    bool inline Flush(const std::string &parentpath)
    {

      bool errnox = false;
      if(!parentpath.empty())
      {
        errnox = WriteToFile(std::string(parentpath + AddExt("stats")), stats.str());


        #if FCS_PART_TAGGING == 1
        errnox = errnox && WriteToFile(std::string(parentpath + AddExt("tag")), tag.str());
        #endif


        #if FCS_RND_SAMPLING == 1
        errnox = errnox && 
                 WriteToFile(std::string(parentpath + AddExt("u_dist")), u_dist.str()) &&
                 WriteToFile(std::string(parentpath + AddExt("gauss_dist")), gauss_dist.str());
        #endif
                          
      }

      return errnox;

    } //End of Flush()

    //Clears all buffers
    void ClearAll()
    {
        for(auto stream: pipelist)
        {
          stream->str(std::string()); //Set equivalent to string of zero length
          stream->clear();  //Set error stateflags
          stream->seekp(0); // for outputs: seek put ptr to start
        }
    }

private:


  std::string AddExt(std::string str)
  {
    str.append(FCS_DATAFILE_EXT);
    return str;
  }
  
  bool inline WriteToFile(std::string path, const std::string &content)
  {
    std::ofstream file(path, std::ios::out);
    if(file.is_open())
    { 
      file << content;
      return true;
      //RAII close expected.
    }
    else
      return false;

    //RAII file close expected
  }

}; //End of class Datapipe