#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "../../api.h"

//Base file to keep us from recompiling catch everytime we make
  api *bossMan;

int main(int argc, char* argv[])
{
  //start global setup stuff
  int UIMode = -1, maxTurns = 1, idleTime = 1000, result=0;
  std::string mapName = "default.map";
  gameSetting *settings = new gameSetting;
  map *gameMap = new map;
  Game *gameinit = new Game;
  gameFunctions *gameFunc = new gameFunctions;
  bossMan = new api;
  tankLoader *tankLoad = new tankLoader;
  gameinit->initGameState(settings, gameMap, gameFunc, bossMan, tankLoad, mapName, maxTurns, idleTime, UIMode, argc, argv);

  //start Catch
  result = Catch::Session().run(argc, argv);

  //cleanup
  delete gameMap;
  delete gameinit;
  delete gameFunc;
  delete bossMan;
  delete settings;
  delete tankLoad;

  return result;
}
