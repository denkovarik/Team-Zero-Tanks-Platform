/*********************************************************************
*
*  Program Usage: ./battletanks [-map \"default.map\"] [-maxturn 200] [-ui (ascii|opengl)] [-idle 1000]
*
**********************************************************************/
#include "api.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
  int counter = 1, UIMode = 1, maxTurns = 1000, idleTime = 200;
  std::string mapName = "default.map";
  gameSetting *settings = new gameSetting;
  map *gameMap = new map;
  api *bossMan = new api;
  Game *gameinit = new Game;
  gameFunctions *gameFunc = new gameFunctions;
  tankLoader *tankLoad = new tankLoader;
  const char *mapname = "-map";
  const char *maxt = "-maxturn";
  const char *ui = "-ui";
  const char *idle = "-idle";
  srand(time(NULL));


  while(counter < argc)
  {
    if(strcmp(argv[counter], mapname) == 0 && counter+1 < argc)
    {
      mapName = argv[counter+1];
      counter+=2;
      continue;
    }
    if(strcmp(argv[counter], maxt) == 0 && counter + 1 < argc)
    {
      maxTurns = std::stoi(argv[counter+1]);
      counter+=2;
      continue;
    }
    if(strcmp(argv[counter], ui) == 0 && counter + 1 < argc)
    {
      counter+=2;
      if(strcmp(argv[counter-1], "ascii") == 0)
      {
        UIMode = 0;
      }
      if(strcmp(argv[counter-1], "opengl") == 0)
      {
        UIMode = 1;
      }
      continue;
    }
    if(strcmp(argv[counter], idle) == 0 && counter + 1 < argc)
    {
      idleTime = std::stoi(argv[counter+1]);
      counter+=2;
      continue;
    }
    printf("Invalid arguments.\n");
    printf("Program Usage: ./battletanks [-map \"default.map\"] [-maxturn 200]");
    printf(" [-ui (ascii|opengl)] [-idle 1000]\n");
    return (1);
  }


  
  printf("Welcome to BattleTanks\n");

  return gameinit->initGameState(settings, gameMap, gameFunc, bossMan, tankLoad, mapName, maxTurns, idleTime, UIMode, argc, argv);
}
