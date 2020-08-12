//base class for API
#ifndef _RUNNER_H_
#define _RUNNER_H_
#include "base.h"
#include "src/constants.h"
#include "../api.h"

//Base computer player class
class runner : public comp
{
  public:
    //Gives the player their player number on creation
    runner();
    ~runner();
    std::string tankName();
    ActionCommand performAction();

  protected:
    int getPlayerId(){return playerNumber;};
    bool checkLocalMap(int x, int y);
    void setPlayerAP(api *ap){this->ap = ap;};
    ActionCommand changeDir(int currDir);
    void setPlayerNumber(int pNum){playerNumber = pNum;}

  private:
    //This number must be saved to use API functions.  An invalid player number will reject the call
    int playerNumber;
    api *ap;

    int** map;
    int dir;
    int speed;
    int myX;
    int myY;
    int mapX;
    int mapY;

  friend class api;

};
// Necessary functions for the dynamic tank loader

extern "C" comp* createTank()
{
  return new runner();
}

extern "C" void destroyTank(comp *p)
{
  delete p;
}

#endif
