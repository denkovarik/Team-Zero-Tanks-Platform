#include "chaser.h"
#include "../libraries/src/alloc2d.h"
chaser::chaser() {
  map = alloc2D(11, 21);
}
chaser::~chaser() {}

std::string chaser::tankName()
{
  return "Chaser";
}

ActionCommand chaser::performAction()
{
  //Moves:
  //0 - nothing   1 - Up    2 - Right   3 - Down
  //4 - Left    5 - Reverse   6 - Fire Cannon

  int myMove, i;
  printf("Starting Chaser. Tank ID: %d\n",playerNumber);
  ap->apgetMap(playerNumber, map); 
  dir = ap->apgetDirection(playerNumber);
  speed = ap->apgetSpeed(playerNumber);  
  myX = ap->apgetTankX(playerNumber);
  myY = ap->apgetTankY(playerNumber);
  mapX = ap->apgetMapX(playerNumber);
  mapY = ap->apgetMapY(playerNumber);
  //printf("%d.\n",mapY);

  switch (dir)
  {
    case 0:
      for (i = 0; i < 4 && i + myY + 1 <= mapY; i++){
        if (!checkLocalMap(myX, myY + i + 1)){
          //printf("Map blocked, Changing Direction.\n");
          return changeDir(0);
        }
      }
      //if (i < 3)
      //    return changeDir(0);
      //printf("Staying on course. (up)\n");
      myMove = 1; 
      break;
    case 1:
      for (i = 0; i < 4 || i + myX + 1 <= mapX; i++){
        if (!checkLocalMap(myX + i + 1, myY)){
          //printf("Map blocked, Changing Direction.\n");
          return changeDir(1);
        }
      }
      myMove = 2;  
      //printf("Staying on course.(right)\n");
      break;
    case 2:
      for (i = 0; i < 4 || myY - i - 1 >= 1; i++){
        if (!checkLocalMap(myX, myY - i - 1)){
          //printf("Map blocked, Changing Direction.\n");
          return changeDir(2);
        }
      }
      //printf("Staying on course. (down)\n");
      myMove = 3;
      break;
    case 3:
      for (i = 0; i < 4 || myX - i - 1 >= 1; i++){
        if (!checkLocalMap(myX - i - 1, myY)){
          //printf("Map blocked, Changing Direction.\n");
          return changeDir(3);
        }
      }
      //printf("Staying on course. (down)\n");
      myMove = 4;
      break;
  }
  //if we get here panic again
  myMove = rand() % 4 + 1; //0-3 + 1 for movement only
  return (ActionCommand)myMove;
}

ActionCommand chaser::changeDir(int currDir)
{
  //commands 1-up, 2-right, 3-down, 4-left
  int myMove = 0;
  //printf("Changing directions.\n");
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
  //printf("Picked move: %d\n",myMove);
  return (ActionCommand) myMove;
}

bool chaser::checkLocalMap(int x, int y)
{
  if (map[y][x] == 'X' || map[y][x] == 'B' || map[y][x] == 'T') //if empty return true
    return true;
  return false; //if an object abort
}
