#include "api.h"
#include "libraries/src/alloc2d.h"
#include "comp/src/tankLoader.h"



/******************************************************************
*  api()
*  Author(s): Jonathan McKee
*  This allows the creation of an API object
*
*******************************************************************/
api::api() {}
/******************************************************************
*  ~api()
*  Author(s): Jonathan McKee
*  This function cleans up the API object
*
*******************************************************************/
api::~api()
{
}

/******************************************************************
*  setMap(map *gMap)
*  Author(s): Jonathan McKee
*  Parameters:
*   gMap - pointer to map object
*  Return Value:
*   true if the pointer was set
*  This function links the API to the specified map object
*
*******************************************************************/
bool api::setMap(map *gMap)
{
  gameMap = gMap;
  if(gameMap != nullptr)
    return true;
  return false;
}
/******************************************************************
*  setSetting(gameSetting *gameSetting)
*  Author(s): Jonathan McKee
*  Parameters:
*   gameSetting - pointer to gameSetting object
*  Return Value:
*   true if pointer was set
*  This function links the API to the specified gameSetting object
*
*******************************************************************/
bool api::setSetting(gameSetting *gameSetting)
{
  settings = gameSetting;
  if(settings != nullptr)
    return true;
  return false;
}
/******************************************************************
*  setGame(Game *gl)
*  Author(s): Jonathan McKee
*  Parameters:
*   gl - pointer to new Game object
*  Return Value:
*   true if pointer was set
*  This function links our API object to the specifid Game object
*
*******************************************************************/
bool api::setGame(Game *gl)
{
  glGame = gl;
  if(glGame != nullptr)
    return true;
  return false;
}
/******************************************************************
*  setGameFunc(gameFunctions *gameFunc)
*  Author(s): Jonathan McKee
*  Parameters:
*   gameFunc - the pointer to the new gameFunc link
*  Return Value:
*   true if pointer was set
*  This function links the API to our gameFunctions object
*
*******************************************************************/
bool api::setGameFunc(gameFunctions *gameFunc)
{
  this->gameFunc = gameFunc;
  if(gameFunc != nullptr)
    return true;
  return false;
}
/******************************************************************
*  setTankLoader(tankLoader *tankLoader)
*  Author(s): Jonathan McKee
*  Parameters:
*   tankLoader - the pointer to the new tankLoader link
*  Return Value:
*   true if pointer was set
*  This function links the API to our tankLoader object
*
*******************************************************************/
bool api::setTankLoad(tankLoader *tankLoad)
{
  this->tankLoad = tankLoad;
  if(tankLoad != nullptr)
    return true;
  return false;
}

//Tank Helpers
/******************************************************************
*  asetPos(int x, int y, tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   x - the new x value
*   y - the new y value
*   tTank - the tank to set position for
*  Return Value:
*   true if tank moved
*  Sets the position of a tank object
*
*******************************************************************/
bool api::asetPos(int x, int y, tank &tTank)
{
  return tTank.setPos(x,y);
}

/******************************************************************
*  asetColors(int r, int g, int b, tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   r - The red value
*   g - The green value
*   b - The blue value
*   tTank - The tank to change color of
*  Return Value:
*   true if the color was set
*  This function changes the color of the specified tank
*
*******************************************************************/
bool api::asetColors(int r, int g, int b, tank &tTank)
{
  return tTank.setColors(r,g,b);
}
/******************************************************************
*  agetPos(int &x, int&y, tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   x - the variable to store x value in
*   y - the variable to store y value in
*   tTank - the tank to get position of
*  Return Value:
*   returns true if values were returned
*  This function returns the position of the specified tank
*
*******************************************************************/
bool api::agetPos(int &x, int &y, tank &tTank)
{
  return tTank.getPos(x,y);
}
/******************************************************************
*  agetX(tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to get the X value from
*  Return Value:
*   returns the tanks x value
*  This function returns the x value of the specified tank
*
*******************************************************************/
int api::agetX(tank &tTank)
{
  return tTank.getX();
}        //Return the current x position of the tank
/******************************************************************
*  agetY(tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to get the Y value from
*  Return Value:
*   returns the y value
*  This function returns the Y value of the tank specified
*
*******************************************************************/
int api::agetY(tank &tTank)
{
  return tTank.getY();
}            //Return the current y positoin of the tank
/******************************************************************
*  amoveUp(tank &tTank, int y)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to move
*   y - number of spaces to move
*  Return Value:
*   true if the move was successful
*  This function attempts to move the tank upward
*
*******************************************************************/
bool api::amoveUp(tank &tTank, int y)
{
  return tTank.moveUp(y);
}      //Moves the tank up (default 1)
/******************************************************************
*  amoveRight(tank &tTank, int y)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to move
*   y - the number of spaces to move
*  Return Value:
*   true if the tank moves
*  This function attempts to move the tank right
*
*******************************************************************/
bool api::amoveRight(tank &tTank, int y)
{
  return tTank.moveRight(y);
}     //Moves the tank right (default 1)
/******************************************************************
*  amoveDown(tank &tTank, int y)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to move
*   y - the number of spaces to move
*  Return Value:
*   true of the tank moved
*  This function attempts to move the tank down
*
*******************************************************************/
bool api::amoveDown(tank &tTank, int y)
{
  return tTank.moveDown(y);
}      //Moves the tank down (default 1)
/******************************************************************
*  amoveLeft(tank &tTank, int y)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to move
*   y - number of spaces to move
*  Return Value:
*   true if the move was successful
*  This function attempts to move the tank left
*
*******************************************************************/
bool api::amoveLeft(tank &tTank, int y)
{
  return tTank.moveLeft(y);
}      //Moves the tank left (default 1)
/******************************************************************
*  agetSpeed(tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to get the speed from
*  Return Value:
*   returns the speed value
*  This function returns the speed of the specified tank
*
*******************************************************************/
int api::agetSpeed(tank &tTank)
{
  return tTank.getSpeed();
}        //Return the current speed of the tank
/******************************************************************
*  agetKill(tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to get the kills from
*  Return Value:
*   returns the number of kills
*  This functionsr returns the number of kills for the tank specified
*
*******************************************************************/
int api::agetKill(tank &tTank)
{
  return tTank.getKill();
}       //Returns the current number of kills
/******************************************************************
*  agetHealth(tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to check health of
*  Return Value:
*   the health of the tank
*  This function gets the health of the supplied tank
*
*******************************************************************/
int api::agetHealth(tank &tTank)
{
  return tTank.getHealth(); //Returns the current health
}
/******************************************************************
*  agetHit(tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to check health of
*  Return Value:
*   the hits of the tank
*  This function gets the hits of the supplied tank
*
*******************************************************************/
int api::agetHits(tank &tTank)
{
  return tTank.getHit(); //Returns the current health
}
/******************************************************************
*  agetMisses(tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to check health of
*  Return Value:
*   the tanks current misses
*  This function gets the misses for the specified tank
*
*******************************************************************/
int api::agetMiss(tank &tTank)
{
  return tTank.getMiss(); //Returns the current health
}
/******************************************************************
*  agetColors(int &r, int &g, int &b, tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   r - the variable to hold the red value
*   g - the variable to hold the green value
*   b - the variable to hold the blue value
*   tTank - the tank value to check
*  Return Value:
*   returns true when the colors are returned
*  This function gets the player color
*
*******************************************************************/
bool api::agetColors(int &r, int &g, int &b, tank &tTank)
{
  return tTank.getColors(r,g,b); //Returns the colors of the tank
}
/******************************************************************
*  atakeDamage(tank &tTank, int y)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank object to modify
*   y - the amount of damage to take
*  Return Value:
*   true if damage was successfully taken
*  This function causes the supplied tank to take damage
*
*******************************************************************/
bool api::atakeDamage(tank &tTank, int y)
{
  return tTank.takeDamage(y); //Gives the tank damage (negative health, default 1)
}
/******************************************************************
*  asetX(int x, tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*     x - the new X value
*     tTank - The tank to modify
*  Return Value:
*     true if the x value was set
*  This function sets the x value for the specified tank
*
*******************************************************************/
bool api::asetX(int x, tank &tTank)
{
  return tTank.setX(x); //Manually set the x position of the tank
}
/******************************************************************
*  asetY(int y, tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   y - the new y value
*   tTank - the tank to modify
*  Return Value:
*   true if new value set
*  This function sets the y value of the specified tank
*
*******************************************************************/
bool api::asetY(int y, tank &tTank)
{
  return tTank.setY(y);
}        //Manually set the y position of the tank
/******************************************************************
*  asetSpeed(int newSpeed, tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   newSpeed - The new speed value for the tank
*   tTank - the tank object to modify
*  Return Value:
*   returns true if the speed was set
*  This sets the speed value of the specified tank
*
*******************************************************************/
bool api::asetSpeed(int newSpeed, tank &tTank)
{
  return tTank.setSpeed(newSpeed); //Manually set the speed of the tank
}
/******************************************************************
*  aaddKill(tank &tTank, int kill)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to add a kill to
*   kill - the amount of kills to add
*  Return Value:
*   returns true if the kill was added
*  This function adds the specified number of kills to the tank
*
*******************************************************************/
bool api::aaddKill(tank &tTank, int kill)
{
  return tTank.addKill(kill); //Adds kills to the tank's stats (default 1)
}
/******************************************************************
*  aaddHit(tank &tTank, int hits)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to add a hits to
*   Hit - the amount of hits to add
*  Return Value:
*   returns true if the hit was added
*  This function adds the specified number of hits to the tank
*
*******************************************************************/
bool api::aaddHit(tank &tTank, int hit)
{
  return tTank.addHit(hit); //Adds hit to the tank's stats (default 1)
}
/******************************************************************
*  aaddMiss(tank &tTank, int miss)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to add a hits to
*   miss - the amount of miss to add
*  Return Value:
*   returns true if the mis was added
*  This function adds the specified number of miss to the tank
*
*******************************************************************/
bool api::aaddMiss(tank &tTank, int miss)
{
  return tTank.addMiss(miss); //Adds miss to the tank's stats (default 1)
}
/******************************************************************
*  asetKill(tank &tTank, int kill)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to set the kills of
*   kill - the new kill number
*  Return Value:
*   returns true if the new kill was set
*  This is function sets the kills of the supplied tank
*
*******************************************************************/
bool api::asetKill(tank &tTank, int kill)
{
  return tTank.setKill(kill); //Manually set the number of tank kills
}
/******************************************************************
*  asetMiss(tank &tTank, int miss)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to set the miss of
*   miss - the new miss number
*  Return Value:
*   returns true if the new miss was set
*  This is function sets the miss of the supplied tank
*
*******************************************************************/
//bool api::asetMiss(tank &tTank, int miss)
//{
//  return tTank.setMiss(miss); //Manually set the number of tank miss
//}
/******************************************************************
*  asetHit(tank &tTank, int hit)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to set the hits of
*   hit - the new hits number
*  Return Value:
*   returns true if the new hit was set
*  This is function sets the hits of the supplied tank
*
*******************************************************************/
bool api::asetHit(tank &tTank, int hit)
{
  return tTank.setHit(hit); //Manually set the number of tank kills
}
/******************************************************************
*  asetHealth(int hp, tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*   hp - the tanks new value
*   tTank - the tank to set the health of
*  Return Value:
*   returns true if the value is set succesfully
*  This function sets the health of the supplied tank
*
*******************************************************************/
bool api::asetHealth(int hp, tank &tTank)
{
  return tTank.setHealth(hp); //Manually set the health
}
/******************************************************************
*  agetDirection(tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*     tTank - the tank to get the direction of
*  Return Value:
*     returns the direction of the tank
*  This function gets the direction of the supplied tank
*
*******************************************************************/
int api::agetDirection(tank &tTank)
{
  return tTank.getDirection();
}
/******************************************************************
*  asetDirection(tank &tTank, int newDir)
*  Author(s): Jonathan McKee
*  Parameters:
*   tTank - the tank to change direction
*   newDir - the new direction of the tank
*  Return Value:
*  This function changes the direction a tank is facing
*
*******************************************************************/
bool api::asetDirection(tank &tTank,int newDir)
{
  return tTank.setDirection(newDir);
}
/******************************************************************
*  aFire(tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*     tTank - The tank object to create a projectile for
*  Return Value:
*     none
*  This function creates a projectile for the supplied tank
*
*******************************************************************/
void api::aFire(tank &tTank)
{
  gameFunc->fire(tTank, projectileList);
}
/******************************************************************
*  int agetPlayerId(tank &tTank)
*  Author(s): Jonathan McKee
*  Parameters:
*     tTank - The tank object to get the player id of
*  Return Value:
*     returns the tank's id number
*  This function returns the player ID from the supplied tank.
*
*******************************************************************/
int api::agetPlayerId(tank &tTank)
{
  return tTank.getPlayerId();
}
/******************************************************************
*  bool regAP()
*  Author(s): Jonathan McKee
*  Parameters:
*   none
*  Return Value:
*   true if we made it to the end of the registration process
*  This function travels the various objects and sets their ap
* pointer equal to this api object.
*
*******************************************************************/
bool api::regAP()
{
  glGame->setGame(this);
  settings->setSetting(this);
  gameMap->setMap(this);
  gameFunc->setGameFunc(this);
  tankLoad->setTankLoad(this);
  return true;
}
/******************************************************************
*  asetGameMode(string gameMode)
*  Author(s): Jonathan McKee
*  Parameters:
*   string gameMode
*  Return Value:
*   true - valid game mode
*   false - invalid game mode
*  This function sets the gameMode variable stored in the API object
*
*******************************************************************/
bool api::asetGameMode(std::string gameMode)
{
  transform(gameMode.begin(), gameMode.end(), gameMode.begin(), ::tolower);
  if(gameMode.compare("tanks") != 0 &&
     gameMode.compare("planes") != 0 &&
     gameMode.compare("boats") != 0)
  {
    return false;
  }
  this->gameMode = gameMode;
  return true;
}

/******************************************************************
*  afindTankNumber(int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   id - the player id to match to a tank
*  Return Value:
*   returns the tankList index for this players tank or -1 when not
*     found
*  This function searches the tankList for the specified player Id
*     and then returns the result.
*
*******************************************************************/
int api::afindTankNumber(int id)
{
  //printf("Finding the tank number. From %d tanks.\n", (int) tankList.size());
  for (unsigned i = 0; i <= tankList.size(); i++)
  {
    //printf("%d Loop.\n",i);
    if (agetPlayerId(tankList[i]) == id)
    {
      //printf("Found tank number: %d.\n",i);
      return (int) i;
    }
  }
  //not found
  return -1;
}

/******************************************************************************
*                                                                             *
*                 Start of API AI accessible functions                        *
*                                                                             *
*                                                                             *
******************************************************************************/



/******************************************************************
*  apgetMap(int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   id - the player id to match to a tank
*  Return Value:
*   returns a integer double array of the map created for the player
*  This function finds the selected player's tank, looks at its
*   location and then builds a map using the vision stat to limit
*   the range simulating fog of war
*
*******************************************************************/
void api::apgetMap(int id, int** &tempMap)
{
  //printf("Making custom map.\n");
  //printf("Finding tank (%d) position.\n", id);
  int tankNum = afindTankNumber(id);
  //printf("Making custom map.\n");
  int tankX = agetX(tankList[tankNum]);
  int tankY = agetY(tankList[tankNum]);
  int vision = 4;
  int i, j;
  //int** tempMap;
  tileObject tempObj;
  int tempObjInt;
  //create ranges
  int xH = tankX + vision, yH = tankY + vision, xL = tankX - vision, yL = tankY - vision;
  //check for off map
  (xH > FieldX) ? xH = FieldX : xH;
  (yH > FieldY) ? yH = FieldY : yH;
  (xL < 1) ? xL = 1 : xL;
  (yL < 1) ? yL = 1 : yL;
  //tempMap = alloc2D(FieldY + 1, FieldX + 1);
  for (i = 1; i <= FieldY; i++)
  {
    for (j = 1; j <= FieldX; j++)
    {
      if ((i >= yL ) && (i <= yH) && (j >= xL) && (j <= xH))
      { 
        tempObj = agetMapObject(j, i);
        switch(tempObj)
        {
              case tileObject::TREE:
                tempObjInt = 'T';
                break;
              case tileObject::ROCK:
                tempObjInt = 'R';
                break;
              case tileObject::PROJECTILE:
                tempObjInt = 'P';
                break;
              //case tileObject::WATER:
                //tempObjInt = 'W';
                //break;
              case tileObject::TANK:
                tempObjInt = 'E';
                break;
              default:
                tempObjInt = 'X';
                break;
        }
      }else{
          tempObjInt = 0;
      }
      tempMap[i][j] = tempObjInt;
    }
  }
}                       
  
/******************************************************************
*  apcheckMove(int x, int y, int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   x - proopsed x value
*   y - proposed y value
*   id - the player id to match to a tank
*  Return Value:
*     true if the move is valid
*     false if the move is invalid
*  This function checks if the players move is a valid move and
*     returns true or false to the player. Only checks the final
*     destination and not the path if speed > 1
*
*******************************************************************/
bool api::apcheckMove(int x, int y, int id)
{
  int tankNum = afindTankNumber(id);
  int tankX, tankY;
  int tankSpeed = agetSpeed(tankList[tankNum]);
  //Populate tankX and tank Y before getting Max's and Min's
  agetPos(tankX, tankY, tankList[tankNum]);
  int xH = tankX + tankSpeed, yH = tankY + tankSpeed, xL = tankX - tankSpeed, yL = tankY - tankSpeed;
  //check if move is out of range
  if ((x < xL) || (x > xH) || (y < yL) || (y > yH))
    return false;
  //check if space is empty or projectile  (We will let them run into a projectile if they want)
  if ((agetMapObject(x, y) == tileObject::EMPTY) || agetMapObject(x,y) == tileObject::PROJECTILE)
    return true;

  //Check spaces between x and y if needed

  //other wise not possible
  return false;
}      
/******************************************************************
*  apgetPos(int &x, int &y, int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   x - x value
*   y - y value
*   id - the player id to match to a tank
*  Return Value:
*     true if the position was returned
*  This function returns the players position
*
*******************************************************************/
bool api::apgetPos(int &x, int &y, int id)
{
  int tankNum = afindTankNumber(id);
  return agetPos(x, y, tankList[tankNum]);
}     
/******************************************************************
*  apgetTankX(int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   id - the player id to match to a tank
*  Return Value:
*     the players current x value
*  This function returns the players current x value
*
*******************************************************************/
int api::apgetTankX(int id)
{
  int tankNum = afindTankNumber(id);
  return agetX(tankList[tankNum]);
}     
/******************************************************************
*  apgetTankY(int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   id - the player id to match to a tank
*  Return Value:
*     the players current Y value
*  This function returns the players current Y value
*
*******************************************************************/
int api::apgetTankY(int id)
{
  int tankNum = afindTankNumber(id);
  return agetY(tankList[tankNum]);
}     
/******************************************************************
*  apgetHealth(int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   id - the player id to match to a tank
*  Return Value:
*     the players current health
*  This function returns the players current health
*
*******************************************************************/
int api::apgetHealth(int id)
{
  int tankNum = afindTankNumber(id);
  return agetHealth(tankList[tankNum]);
}     
/******************************************************************
*  apgetHit(int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   id - the player id to match to a tank
*  Return Value:
*     the players current hits
*  This function returns the players current hits
*
*******************************************************************/
int api::apgetHits(int id)
{
  int tankNum = afindTankNumber(id);
  return agetHits(tankList[tankNum]);
}     
/******************************************************************
*  apgetKill(int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   id - the player id to match to a tank
*  Return Value:
*     the players current kill count
*  This function returns the players current kill count
*
*******************************************************************/
int api::apgetKill(int id)
{
  int tankNum = afindTankNumber(id);
  return agetKill(tankList[tankNum]);
}     
/******************************************************************
*  apgetSpeed(int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   id - the player id to match to a tank
*  Return Value:
*     the players current speed
*  This function returns the players current speed value
*******************************************************************/
int api::apgetSpeed(int id)
{
  int tankNum = afindTankNumber(id);
  return agetSpeed(tankList[tankNum]);
}                  
/******************************************************************
*  apgetDirection(int id)
*  Author(s): Jonathan McKee
*  Parameters:
*   id - the player id to match to a tank
*  Return Value:
*     the players current direction
*  This function returns the players current direction
*
*******************************************************************/
int api::apgetDirection(int id)
{
  int tankNum = afindTankNumber(id);
  return agetDirection(tankList[tankNum]);
}     

/******************************************************************
*  aunloadTanks()
*  Author(s): Jonathan McKee
*  Parameters:
*  Return Value:
*  This function unloads our dynamically allocated tanks
*
*******************************************************************/
void api::aunloadTanks()
{
  tankLoad->unloadTanks();
}

/******************************************************************
*  aloadTanks()
*  Author(s): Jonathan McKee
*  Parameters:
*  Return Value:
*  This function dynamically allocates our tanks from so libraries
*
*******************************************************************/
void api::aloadTanks()
{
  tankLoad->loadTanks(tankDir);
}

/******************************************************************
*  adoMoves()
*  Author(s): Jonathan McKee
*  Parameters:
*  Return Value:
*  This function performs actions for out loaded tanks
*
*******************************************************************/
ActionCommand api::adoMoves(int player)
{
  //printf("Player id number: %d\n", player);
  return tankLoad->doMoves(player);
}
/******************************************************************
*  asetPlayerNumber()
*  Author(s): Jonathan McKee
*  Parameters:
*  Return Value:
*  This function gives our loaded tank a player number
*
*******************************************************************/
void api::asetPlayerNumber(int tIndex, int pNum)
{
  tankLoad->setPlayerNumber(tIndex, pNum);
}
/******************************************************************
*  asetPlayerAP()
*  Author(s): Jonathan McKee
*  Parameters:
*  Return Value:
*  This function gives our loaded tank a player AP
*
*******************************************************************/
void api::asetPlayerAP(int tIndex)
{
  tankLoad->setPlayerAP(tIndex);
}

/******************************************************************
*  agetTankName(int index)
*  Author(s): Dennis Kovarik
*  Parameters: 
*   int index - The index of the tank in the -tank vector
*  Return Value:
*  This function returns the name of the loaded tank
*
*******************************************************************/
std::string api::agetTankName(int index)
{
	return tankLoad->getTankName(index);
}
/******************************************************************
*  agetObjPos(int &x, int&y, tankObject &tObject)
*  Author(s): Jonathan McKee
*  Parameters:
*   x - the variable to store x value in
*   y - the variable to store y value in
*   tObject - the object to get position of
*  Return Value:
*   returns true if values were returned
*  This function returns the position of the specified tank
*
*******************************************************************/
bool api::agetObjPos(int &x, int &y, tankObject &tObject)
{
  return tObject.getObjPos(x,y);
}
/******************************************************************
*  asetObjPos(int x, int y, tankObj &tObject)
*  Author(s): Jonathan McKee
*  Parameters:
*   x - the new x value
*   y - the new y value
*   tObject - the object to set position for
*  Return Value:
*   true if object was set moved
*  Sets the position of a tankObject
*
*******************************************************************/
bool api::asetObjPos(int x, int y, tankObject &tObject)
{
  return tObject.setObjPos(x,y);
}
/******************************************************************
*  asetObjType(int type, tankObj &tObject)
*  Author(s): Jonathan McKee
*  Parameters:
*   type - the new object type
*   tObject - the object to type of
*  Return Value:
*   true if object was changed
*   false if inalvid type
*  Sets the type of a tankObject
*
*******************************************************************/
bool api::asetObjType(int type, tankObject &tObject)
{
  return tObject.setObjType(type);
}
/******************************************************************
*  agetObjType(tankObj &tObject)
*  Author(s): Jonathan McKee
*  Parameters:
*   tObject - the object to get type of
*  Return Value:
*   the object type of the tankObject
*  Gets the type of a tankObject
*
*******************************************************************/
int api::agetObjType(tankObject &tObject)
{
  return tObject.getObjType();
}

bool api::agetObjColors(int &r, int &g, int &b, tankObject &tObject)
{
  return tObject.getObjColors(r, g, b);
}

bool api::agetObjSecondaryColors(int &r, int &g, int &b, tankObject &tObject)
{
  return tObject.getObjSecondaryColors(r, g, b);
}
