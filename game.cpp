#include "api.h"
#include <vector>
#include "util.h"

Game::Game(){}
Game::~Game(){}

void Game::executeTurn()
{
  if (!ap->acheckProjTurn()) //only increment on full game turn
    ap->aturnPassed(); 
  std::cout << "Game Turn [" << ap->agetTurn() << "] executed\n";
  gameOver = !ap->agameTurn();
  //ap->adisplayAscii();  //extra display during turn to test display
  // Here's where you handle things that should happen during a turn
  //   - Ask each of the tanks for their action
  //   - Update the game state
  //   - Issue a call to repaint the playfield, projectiles, tanks, etc.
  //std::cout << "Repainting game objects\n";
 
	printf( "Player Alive Cound %d\n", ap->agetPlayerAliveCount() );
 
  if (ap->acheckMaxTurn() || gameOver)//added check max turn for early testing exit
  {
      gameOver = true;
#ifdef DEBUG
      glutLeaveMainLoop();
#endif
  }
}
/*******************************************************************************
*   int initGameState(gameSetting *set, map *gameMap, gameFunctions *gameFunc, 
*                     api *bossMan, tankLodaer *tankLoader, std::string mapName, 
*                     int maxTurns, int idleTime, int UIMode, int argc, char *argv[]
*   Author(s): Jonathan McKee, Levi Butts
*   Parameters:
*     set - the pointer to the settings object
*     gameMap - the pointer to the map object
*     gameFunc - the pointer to the gameFunctions object
*     bossMan - the pointer to the API object
*     tankLoader - the pointer to the tankLoader object
*     mapName - the map name
*     maxTurns - the max number of turns
*     idleTime - the idle speed value
*     UIMode - the UIMode 0 - ASCII : 1 - OpenGL
*     argc - the number of arguments (for GlutInit)
*     argv - the command line options passed in (for GlutInit)
*   Return Value:
*     0 - Successful
*     2 - Could not spawn tanks
*     4 - UI set to -1 for testing
*     ? - the value return from areadMap() if unsuccessful
*
*   This function initializizes our game environment.  It sets the mapName,
*   max turns, idletime, UImode, adds our pointers to our settings, map,
*   gameFunctions to our API object.  It also reads the map file into the object
*   and then spawns the tanks.
*
********************************************************************************/

int Game::initGameState(gameSetting *set, map *gameMap, gameFunctions *gameFunc, api *bossMan, tankLoader *tankLoader, std::string mapName, int maxTurns, int idleTime, int UIMode, int argc, char *argv[])
{
  int temp;
  bossMan->setMap(gameMap);
  bossMan->setSetting(set);
  bossMan->setGame(this);
  bossMan->setGameFunc(gameFunc);
  bossMan->setTankLoad(tankLoader);
  bossMan->regAP();
  
  printf("Game::Starting game init.\n");
  printf("Game::Saving Settings.\n");
  printf("     Map Name: %s\n", mapName.c_str());
  ap->asetMapName(mapName);
  printf("     Max turns: %d\n", maxTurns);
  ap->asetMaxTurns(maxTurns);
  printf("     Idle Speed: %d\n", idleTime);
  ap->asetIdleTime(idleTime);
  if (UIMode == 0) 
      printf("     UI Mode: ASCII\n");
  else if (UIMode == 1)    
      printf("     UI Mode: OpenGL\n");
  else
      printf("Unknown\n");
  ap->asetUIMode(UIMode);
  printf("Game::Reading Map: %s\n",ap->agetMapName().c_str());
  temp = ap->areadMap();
  if (temp != 0)
    return temp;
  std::cout << "Game::Loading tanks\n";
  ap->aloadTanks();
  if(!ap->aspawnTanks())
  {
    std::cout << "Couldn't spawn tanks\n";
    return 2;
  }
  std::cout << ap->agetPlayerCount() << " number of tanks loaded.\n";
  std::cout << ap->agetPlayerAliveCount() << " number of tanks alive.\n";
  std::cout << "Game::Setting turn counter to 0.\n";
  ap->aresetTurn();
  if (UIMode == 0)
  {
    printf("Game::Starting ASCII game loop.\n");
    ap->asciiGameLoop();
    return 0;
  }else if( UIMode == 1)
  {
    printf("Game::Initializing OpenGL.\n");
    initOpenGL(argc, argv, 1200, 695, ap, idleTime);
    glutMainLoop();
    return 0;
  }else if( UIMode == -1)
  {
    printf("UI set to -1, Exiting.\n");
    return 4;
  }
  return 0; //For compiler warning
}

void Game::closeDown()
{
  std::cout << "Game::Closing game, cleaning up memory\n";
  std::cout << "Game::Writing results file\n";
}

  std::vector<tank> Game::getTankList()
  {
    return ap->agetTankList();
  }
  int Game::getFieldWidth()
  {
    return ap->agetFieldX();
  }
  int Game::getFieldHeight()
  {
    return ap->agetFieldY();
  }
  bool Game::setGame(api *ap){
      this->ap = ap;
      return ap->setGame(this);
  }
  void Game::drawGrid()
  {
    ap->adrawGrid();
  }
  void Game::drawTanks()
  {
    ap->adrawTanks();
  } 
  void Game::drawObjects()
  {
    ap->adrawObjects();
  } 
  void Game::drawProjectiles()
  {
    ap->adrawProjectiles();
  }
  void Game::headerText()
  {
    ap->aheaderText();
  }

  void Game::gameOverScreen()
  {
  	ap->agameOverScreen();
  }

void Game::setNewApi(api *ap){
  this->ap = ap;
}
