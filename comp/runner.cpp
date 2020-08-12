#include "runner.h"
#include "../libraries/src/alloc2d.h"
runner::runner() {
map = alloc2D(11, 21);
}
runner::~runner() {}

std::string runner::tankName()
{
  return "Runner";
}

ActionCommand runner::performAction()
{
  //Moves:
  //0 - nothing   1 - Up    2 - Right   3 - Down
  //4 - Left    5 - Reverse   6 - Fire Cannon
  printf("Runner starting turn. My id: %d\n", playerNumber);
  int myMove, i;
  ap->apgetMap(playerNumber, map); 
  dir = ap->apgetDirection(playerNumber);
  speed = ap->apgetSpeed(playerNumber);  
  myX = ap->apgetTankX(playerNumber);
  myY = ap->apgetTankY(playerNumber);
  mapX = ap->apgetMapX(playerNumber);
  mapY = ap->apgetMapY(playerNumber);

 // printf("Trying to pick a move.\n");
  switch (dir)
  {
    case 0:
      for (i = 0; i < 4 && i + myY + 1 <= mapY; i++)
        if (!checkLocalMap(myX, myY + i + 1))
          return changeDir(0);
      myMove = 1; 
      break;
    case 1:
      for (i = 0; i < 4 && i + myX + 1 <= mapX; i++)
        if (!checkLocalMap(myX + i + 1, myY))
          return changeDir(1);
      myMove = 2;  
      break;
    case 2:
      for (i = 0; i < 4 && myY - i - 1 >= 1; i++)
        if (!checkLocalMap(myX, myY - i - 1))
          return changeDir(2);
      myMove = 3;
      break;
    case 3:
      for (i = 0; i < 4 && myX - i - 1 >= 1; i++)
        if (!checkLocalMap(myX - i - 1, myY))
          return changeDir(3);
      myMove = 4;
      break;
  }
  //if we get here panic again
  myMove = rand() % 4 + 1; //0-3 + 1 for movement only
  return (ActionCommand)myMove;
}

ActionCommand runner::changeDir(int currDir)
{
  //commands 1-up, 2-right, 3-down, 4-left
  int myMove = 0;
  switch (currDir + 1) 
  {
    case 1:
      if ((myX+1 <= mapX) && (checkLocalMap(myX+1, myY))){
          myMove = 2;
        break;}
      if ((myX-1 >= 1) && (checkLocalMap(myX-1, myY))){
          myMove = 4;
        break;}
    case 2:
      if ((myY-1 >= 1) && (checkLocalMap(myX, myY - 1))){
          myMove = 3;
        break;}
      if ((myY+1 <= mapY) && (checkLocalMap(myX, myY + 1))){
          myMove = 1;
        break;}
    case 3:
      if ((myX-1 >= 1) && (checkLocalMap(myX-1, myY))){
          myMove = 4;
        break;}
      if ((myX+1 <= mapX) && (checkLocalMap(myX+1, myY))){
          myMove = 2;
        break;}
    case 4:
      if ((myY+1 <= mapY) && (checkLocalMap(myX, myY+1))){
          myMove = 1;
        break;}
      if ((myY-1 >= 1) && (checkLocalMap(myX, myY-1))){
          myMove = 3;
        break;}
  }
  if (myMove == 0) //If we can't find a dir panic
    myMove = rand() % 4 + 1; //0-3 + 1 for movement only
  return (ActionCommand) myMove;
}

bool runner::checkLocalMap(int x, int y)
{
  if (map[y][x] == 'X') //if empty return true
    return true;
  return false; //if an object abort
}
