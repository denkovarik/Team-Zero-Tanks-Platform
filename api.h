/*********************************************************
* api.h
* Author(s): Jonathan McKee
* Last Date Modified: 10/7/2018
*
* This file acts as our API for the platform. It allows 
* our modules to interact securely while still providing 
* access for our AI functions.
**********************************************************/
//Header guards 
#ifndef __API_H
#define __API_H

//Include everythiny
#include <iostream>
#include "game.h"
#include "gameFunctions.h"
#include "classes/classTank.h"
#include "classes/classProjectile.h"
#include "classes/classGame.h"
#include "classes/classMap.h"
#include "classes/classObjects.h"
#include "comp/src/constants.h"
#include "comp/src/tankLoader.h"
#include "comp/base.h"

/*******************************************************************************
*  class api
*  Author(s): Jonathan McKee
*
*  This class acts as a gateway to all of our class modules.  It is a friend
*  class to all of our classes, and all classes (except the AI's) are friend
*  classes to the API.  This allows the API and other classes to access the
*  protected functions, while limiting AI access to the public functions
*                                                   
*******************************************************************************/
class api
{
//Public access functions that are accessible for the comptuer AI's
public:
  //These are fine as public because while a tank could make a new API object, it doesn't
  //help them access the current private game API
  api();  //constructor
  ~api(); //deconstructor

  void apgetMap(int id, int** &map);                       //Builds a map for the current player and returns it
  int apgetMapX(int id){return FieldX;};        //Returns the map width
  int apgetMapY(int id){return FieldY;};        //Returns the map height
  std::string apgetMapName(int id){return settings->getMapName();}; //Returns the current map name

  bool apcheckMove(int x, int y, int id);       //Checks for the player if their wanted move is valid

  bool apgetPos(int &x, int &y, int id);        //Returns the position of the current player
  int apgetTankX(int id);                       //Returns the current X position
  int apgetTankY(int id);                       //Returns the current Y position
  int apgetHealth(int id);                      //Returns the tanks current health
  int apgetKill(int id);                        //Returns the tanks current kill count
  int apgetSpeed(int id);                       //Returns the tanks current speed
  int apgetDirection(int id);                   //returns the tanks current direction
  int apgetHits(int id);                        //returns the tanks current hits

  int apgetTurn(){return agetTurn();};          //returns the current turn number
  int apgetMaxTurns(){return agetMaxTurns();};  //returns the max turn number

//Protected for limiting access to the main functions
//We use a define catch so that catch testing can gain full access to the functions
#ifndef CATCH
protected:
#endif
  //game Setup functions these functions are how we setup our pointers
  //between the various classes
  bool setMap(map *gMap);                     //sets our map pointer equal to the passed in pointer
  bool setSetting(gameSetting *gameSetting);  //sets our gameSetting pointer equal to the passed in pointer
  bool setGame(Game *gl);                     //sets our Game pointer equal to the passed in pointer
  bool setGameFunc(gameFunctions *gameFunc);  //sets our gameFunctions pointer equal to the passed in pointer
  bool setTankLoad(tankLoader *tankLoad); //sets our tankLoader pointer equal to the passed in tankLoader
  bool regAP();                               //Allows a Game object to register with the API object

  //GameFunctions Helpers - Forwards most requests to the gameFunctions class
  bool aspawnTanks(){return gameFunc->spawnTanks(*gameMap, tankList);}; //Spawn tanks
  void atakeTurnA(int nextMove, tank&theTank){gameFunc->takeTurn(nextMove, theTank, projectileList);}; //takeTurn
  void acreateObject(int x, int y, int type){gameFunc->createObject(x, y, type, objectList);}; //adds a object to list
  void aFire(tank &tTank); //function definition in .cpp file
  void acheckProjectiles(){gameFunc->checkProjectiles(tankList, projectileList, *gameMap);}; //checkProkectiles
  bool adisplayAscii(){return gameFunc->displayAscii(*gameMap, tankList, projectileList, objectList);}; //displayASCII map
  int asciiGameLoop(){return gameFunc->aGameLoop(tankList, projectileList, *gameMap, *settings);}; //ACCII gameLoop
  bool agameTurn(){return gameFunc->gameTurn(tankList, projectileList);}; //the order of turns

  //GameFunction Draw Functions - forwads open GL functions to gameFunctions object
  void adrawGrid(){printf("Drawing grid: %d, %d. ",FieldX, FieldY);gameFunc->drawGrid(FieldX, FieldY);}; //drawGrid
  void adrawTanks(){gameFunc->drawTanks(tankList, FieldX, FieldY);}; //draw Tanks
  void adrawProjectiles(){gameFunc->drawProjectiles(projectileList, tankList, FieldX, FieldY);};
  void adrawObjects(){gameFunc->drawObjects(objectList, FieldX, FieldY);};
  void adrawHeader(char* str, int r, int g, int b, int xoffset, int yoffset, bool title){gameFunc->drawHeader(FieldX, FieldY, str, r, g, b, xoffset, yoffset, title);}; // drawHeader at top of screen
  void aheaderText(){gameFunc->headerText(tankList, FieldX, FieldY);}; //make the header text
  void agameOverScreen(){gameFunc->gameOverScreen(tankList);};

  //Map Helpers - Stores most data in the API class, the rest are forwarded to gameMap object
  int agetFieldY(){return FieldY;}; //get height
  int agetFieldX(){return FieldX;}; //get width
  void asetFieldY(int fieldY){FieldY = fieldY;}; //set height
  void asetFieldX(int fieldX){FieldX = fieldX;}; //set width
  bool achangeMapObject(int x, int y, tileObject ob){return gameMap->changeMapObject(x,y, ob);}; //change a map object
  tileObject agetMapObject(int x, int y){return gameMap->getMapObject(x,y);}; //get a map object
  bool asetGameMode(std::string gameMode);  //Function definition in .cpp
  std::string agetGameMode(){return gameMode;}; //get game mode
  int areadMap(){return gameMap->readMap(settings->getMapName());}; //create the game map from file
  int areadMap(std::string mapName){return gameMap->readMap(mapName);}; // areadMap by value

  //GameSettings Helpers - forwards functions to the gameSettings class
  int agetMaxTurns(){return settings->getMaxTurns();}; //get max turns
  void asetMaxTurns(int maxturns){settings->setMaxTurns(maxturns);}; //set max turns
  bool acheckMaxTurn(){return settings->checkMaxTurns(settings->getTurn());}; //check if we hit max turns
  void asetIdleTime(int time){settings->setIdleTime(time);}; //set idle time
  int agetIdleTime(){return settings->getIdleTime();};//get idle time
  std::string agetMapName(){return settings->getMapName();}; // get map name
  void asetMapName(std::string newName){settings->setMapName(newName);}; //set map name
  void asetUIMode(int mode){settings->setUIMode(mode);}; //set UI mode
  int agetUIMode(){return settings->getUIMode();}; //get UI mode
  void aturnPassed(){settings->turnPassed();}; //increment turn counter
  int agetTurn(){return settings->getTurn();}; //return the current turn number
  void aresetTurn(){settings->resetTurn();}; //reset turns to 0
  int agetPlayerCount(){return playerCount;}; //returns the total number of tank players
  int agetPlayerAliveCount(){return playerAliveCount;}; //returns the total number of tanks alive
  void asetPlayerCount(int newPlayerCount){playerCount = newPlayerCount;}; //returns the total number of tank players
  void asetPlayerAliveCount(int newAlive){playerAliveCount = newAlive;}; //returns the total number of tanks alive

  //Projectile Helper - forwards functions to the projectile class
  void agetPosition(int &x, int &y, projectile &proj){proj.getPosition(x,y);}; //get projectile position
  void amoveProjectile(projectile &proj){proj.moveProjectile();}; //move projectile in the direction it is facing
  int agetOwner(projectile &proj){return proj.getOwner();}; //get the projectile owner
  void acheckProjList(){gameFunc->checkProjList(projectileList, tankList);}; //check the projectiles
  bool acheckProjMove(projectile &proj){return gameFunc->checkProjMove(proj);}; //check if the move hits
  bool aprojHit(projectile &proj){return gameFunc->projHit(proj, tankList, objectList);}; //perform the hit

  //Tank Helpers - forwards functions to the tank class
  //Most definitions are in the .cpp file
  //getters
  bool agetPos(int &x, int &y, tank &tTank); //return the current tank position
  int agetX(tank &tTank);        //Return the current x position of the tank
  int agetY(tank &tTank);            //Return the current y positoin of the tank
  int agetSpeed(tank &tTank);        //Return the current speed of the tank
  int agetKill(tank &tTank);       //Returns the current number of kills
  int agetHealth(tank &tTank);       //Returns the current health
  int agetMiss(tank &tTank);      //Returns the tank's number of misses
  int agetDirection(tank &tTank); //get player direction
  int agetPlayerId(tank &tTank);  //get player id number
  int agetHits(tank &tTank);       //get the current number of player hits
  bool agetColors(int &r, int &g, int &b, tank &tTank);  //Returns the colors of the tank
  //utilities
  bool atakeDamage(tank &tTank, int y = 1);    //Gives the tank damage (negative health, default 1)
  bool aaddKill(tank &tTank, int kill = 1);    //Adds kills to the tank's stats (default 1)
  bool aaddHit(tank &tTank, int hit = 1);     //Adds a hit to the tank's stats (default 1)
  bool aaddMiss(tank &tTank, int miss = 1);     //Adds a miss to the tank's stats (default 1)
  bool amoveUp(tank &tTank, int y = 1);      //Moves the tank up (default 1)
  bool amoveRight(tank &tTank, int y = 1);     //Moves the tank right (default 1)
  bool amoveDown(tank &tTank, int y = 1);      //Moves the tank down (default 1)
  bool amoveLeft(tank &tTank, int y = 1);      //Moves the tank left (default 1)
  bool aisAlive(tank &tTank){return agetHealth(tTank) > 0;};
  //setters
  bool asetPos(int x, int y, tank &tTank);     //Manually set the position of the tank
  bool asetX(int x, tank &tTank);        //Manually set the x position of the tank
  bool asetY(int y, tank &tTank);        //Manually set the y position of the tank
  bool asetSpeed(int newSpeed, tank &tTank);   //Manually set the speed of the tank
  bool asetKill(tank &tTank, int kill = 0);      //Manually set the number of tank kills
  bool asetHit(tank &tTank, int hit = 0);       //Manually set the number of tank hits
  bool asetMiss(tank &tTank, int miss = 0);       //Manually set the number of tank misses
  bool asetHealth(int hp, tank &tTank);      //Manually set the health
  bool asetColors(int r, int g, int b, tank &tTank); //set tank colors
  bool asetDirection(tank &tTank,int newDir); //set player direction
 
  //objects
  bool asetObjPos(int x, int y, tankObject &tObject);
  bool agetObjPos(int &x, int &y, tankObject &tObject);
  bool asetObjType(int type, tankObject &tObject);
  int agetObjType(tankObject &tObject);
  bool agetObjColors(int &r, int &g, int &b, tankObject &tObject);
  bool agetObjSecondaryColors(int &r, int &g, int &b, tankObject &tObject);

  //Misc functions 
  std::vector<tank> agetTankList(){return tankList;}; //returns the vector holding the tank list
  int afindTankNumber(int id); //finds the tank number from the player id number
  void atoggleProjTurn(){glGame->toggleProjTurn();};
  bool acheckProjTurn(){return glGame->checkProjTurn();};

  //TankLoader functions
  void aunloadTanks();
  void aloadTanks();
  ActionCommand adoMoves(int player);
  void asetPlayerNumber(int tIndex, int pNum);
  void asetPlayerAP(int tIndex);
  void agetCompArray();
  std::string agetTankName(int index); 	//Returns the name of the tank

  struct playerMap{
    int** map;
  };

private:
  //Object Lists
  std::vector<int> tankId;  //List of tanks
  std::vector<tank> tankList;  //List of objects
  std::vector<projectile> projectileList; //List of projectiles
  std::vector<tankObject> objectList; //List of various objects
#ifndef __TANKLOADER__
  std::vector<tankLoader::tankHandle> *compList; //List of comps
#endif
  std::vector<playerMap> playerMaps;
  //Map variables
  int FieldY = 0;  //Map height
  int FieldX = 0;  //Map weidth
  int** field;  //gamemap
  int playerCount = 0;
  int playerAliveCount=0;
  std::string mapName = "default.map";  //Map Name
  std::string gameMode = "tanks";  //map gamemode
  std::string tankDir = "comp/Tanks"; //Where to find our tanks

  //class references/objects
  map *gameMap;  //pointer to map object
  gameSetting *settings;  //pointer to gameSetting object
  Game *glGame;  //pointer to Game object
  gameFunctions *gameFunc; //pointer to gameFunctions object
  tankLoader *tankLoad; //pointer to gameLoader object
  
  //Friends
  friend class tank;  //Allows tank objects access to protected functions
  friend class map;   //Allows map objects access to protected functions
  friend class Game;  //Allows Game objects access to protected functions
  friend class gameSetting; //Allows gameSetting objects acces to protected functions
  friend class event; //Allows event objects access to protected functions
  friend class gameFunctions; //allows gameFunctions objects access to protected functions
  friend class tankLoader; //allows Tankloader access to protected functions
  friend class tankObjects; //allows tankObjects access to protected functions
   
};

#endif
