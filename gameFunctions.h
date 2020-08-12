#ifndef ASCIIGAMEFUNCTIONS_H
#define ASCIIGAMEFUNCTIONS_H
#include <vector>
#include <cctype>
#include <iostream>
#include <GL/freeglut.h>
#include <iomanip>

//Forward class Declarations
class map;
class tank;
class projectile;
class gameSetting;
class api;
class comp;
class tankObject;

class gameFunctions
{
#ifndef CATCH
protected:
#endif
  //Creates Tanks read from map and adds them to a container of tanks
  bool spawnTanks(map &gameMap, std::vector<tank> &tankList);

  //get the tanks next move
  int getTankMove(std::ifstream &fin);

  //takes turn for tank
  void takeTurn(int nextMove, tank &theTank, std::vector<projectile> &projectileList);

  //Fire projectile
  bool fire(tank theTank, std::vector<projectile> &projectileList);

  //Check if a projectile hit a tank or is off the map
  void checkProjectiles(std::vector<tank> &tankList, std::vector<projectile> &projectileList,
                        map &gameMap);

  //Display an ascii version of the game map for testing purposes
  bool displayAscii(map &gameMap, std::vector<tank> &tankList,
                    std::vector<projectile> &projectileList, std::vector<tankObject> &objectList);

  void drawGrid(int fieldx, int fieldy);

  void drawTanks(std::vector<tank> tankList, int fieldx, int fieldy);

  bool checkMove(int Xcord, int Ycord);

  void drawTank(int x, int y, int fieldx, int fieldy, int color[], int dir, int health);

  int aGameLoop(std::vector<tank> &tankList, std::vector<projectile> &projectileList, map &gameMap, gameSetting &settings);

  bool gameTurn( std::vector<tank> &tankList, std::vector<projectile> &projList);

  void headerText(std::vector<tank> tankList, int fieldx, int fieldy);

  void drawHeader(int fieldx, int fieldy, char *str, int r, int g, int b, int xPos, int yPos, bool title);

  void drawProjectiles(std::vector<projectile> projectileList, std::vector<tank> tankList, int fieldx, int fieldy);

  void drawProjectile(int x, int y, int fieldx, int fieldy, int color[]);

  void checkProjList(std::vector<projectile> &projList, std::vector<tank> &tankList);

  bool checkProjMove(projectile &proj);

  bool projHit(projectile &proj, std::vector<tank> &tankList, std::vector<tankObject> &objectList);

  void playerMove(int move, tank &tTank);
  
  bool pMoveValid(tank &tTank, int direction, int type = 0);

  bool createObject(int x, int y, int type, std::vector<tankObject> &objectList);

  void setGameFunc(api *ap);

  void gameOverScreen(std::vector<tank> tankList);

  void sortTanks(std::vector<tank> &tankList);

  void drawObjects(std::vector<tankObject> objectList, int fieldx, int fieldy);

  void drawTree(int x, int y, int fieldx, int fieldy, int color[], int sColor[]);

  void drawRock(int x, int y, int fieldx, int fieldy, int color[]);
  
  void drawBush(int x, int y, int fieldx, int fieldy, int color[]);

private:
  api *ap;

friend class api;
};
#endif
