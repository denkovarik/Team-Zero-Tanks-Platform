#ifndef __GAME_H
#define __GAME_H
#include <iostream>
#include <vector>

//forward declarations for pointers
//need all because of initGameState function
class tank;
class api;
class gameSetting;
class map;
class gameFunctions;
class tankLoader;

class Game
{
public:
  Game();
  ~Game();
  int initGameState(gameSetting *set, map *gameMap, gameFunctions *gameFunc, api *bossMan, tankLoader * tankLoader, std::string mapName, int maxTurns, int idleTime, int UIModem, int argc, char *argv[]); //Setup the game environment
#ifndef CATCH   //dont protect functions for catch testing
protected:
#endif
  std::vector<tank> getTankList();  //get the tank vector
  int getFieldWidth();          //get Width of map
  int getFieldHeight();         //get Height of map
  bool setGame(api *ap);        //sets the API pointer back to this object
  void toggleProjTurn(){projOnlyTurn = !projOnlyTurn;}; //Toggle a projectile only turn for smoother traveling
  bool checkProjTurn(){return projOnlyTurn;};

  friend class DisplayEvent; //friend class and associated functions
  void drawGrid();              //draws Grid
  void drawTanks();             //draws tanks
  void drawObjects();	//draws objects
  void drawProjectiles();	//draws projectiles
  void headerText();            //draws header text
  void gameOverScreen();
  friend class TimerEvent;  //friend class and associated functions
  void executeTurn();           //perform turn
  void checkMaxTurn();          //see if the turn ended
  friend class CloseEvent;  //friend class and associated functions
  void closeDown();             //clean up on shutdown
  friend class InitEvent;   //friend class and associated functions
  void setNewApi(api *ap);      //this allows us to setup our link of objects

private:
  bool projOnlyTurn = false;
  bool gameOver = false;
  api *ap;
  friend class api;
};

#endif
