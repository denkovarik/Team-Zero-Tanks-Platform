//base class for API
#ifndef _COMP_H_
#define _COMP_H_
#include "../api.h"
#include <cstdlib>
#include <string>

//Base computer player class
class comp
{
   public:
      //Gives the player their player number on creation
      virtual std::string tankName() = 0;
      virtual ActionCommand performAction() = 0;
      int getPlayerId(){return playerNumber;};

   protected:
      //This number must be saved to use API functions.  An invalid player number will reject the call
      virtual void setPlayerNumber(int pnum) = 0;
      virtual void setPlayerAP(api *ap) = 0;
      int playerNumber;

   friend class api;
   friend class tankLoader;
};
#endif
