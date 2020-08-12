#ifndef __TANKLOADER__
#define __TANKLOADER__
#include <iostream>
#include <dirent.h>
#include <errno.h>
#include <dlfcn.h>
#include <sys/types.h>
#include "../base.h"
#include "../../api.h"
#include "constants.h"

// Class to manage loading and unloading shared objects and storing them in
// a vector.
class tankLoader
{
   // some typedefs for convenience
   typedef comp* tankCreate_t();
   typedef void tankDestroy_t(comp *);

   // A private structure used to hold information about each of the tank
   // shared objects that get loaded.
   struct tankHandle
   {
    comp *ptr;                    //A pointer to the tank object
    tankCreate_t* createFunc;     //A pointer to the tank object constructor
    tankDestroy_t* destroyFunc;   //A pointer to the tank object destructor
    void *library;                //A pointer to the library from which
   };                             //    this tank was loaded

protected:
    
   // Free the tank objects and close the shared library from whence it came
   void unloadTanks();
   // Load all the available tanks in the directory 'dir'
   void loadTanks(std::string dir);
   // Loop over all the tankHandles in _tanks and call their move methods
   ActionCommand doMoves(int player);
   // Give our tankAI a tank
   void setPlayerNumber(int tIndex, int pNum);
   void setPlayerAP(int tIndex);

   // Number of loaded tanks
  int getPlayerCount(){return _tanks.size();};
   //connect to the API
   void setTankLoad(api *ap);

   //Get tank names
   std::string getTankName(int index);

   //Storage array for our comp ai
   std::vector<tankHandle> _tanks;

private:
  api *ap;

friend class api;
};
#endif
