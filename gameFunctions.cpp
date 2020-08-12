#include "api.h"
//#include "gameFunctions.h"
//#include "classes/classTank.h"
//#include "classes/classGame.h"
//#include "classes/classMap.h"
//#include "classes/classProjectile.h"
//#include "classes/classGame.h"
#include <unistd.h>
#include <math.h>
#include <GL/freeglut.h>
/*
   spawnTanks()
Authors: Adesh Kumar, Jonathan McKee, Dennis Kovarik
Parameters
map &gameMap            - An instance of the map class
vector<tank> &tanklist  - vector of instances of the tank class
Return Value
Returns an true if the function was able to read the map object gameMap
and populate the tankList vector with instances of the tank class.

This function accepts, as parameters, a map object, called gameMap, and a
vector of tanks, called tankList. The input map file should have already be
read in and stored in gameMap as a 2d array. This function parses the array
looking for tanks on the map. When it finds a tank, it creates a new
instance of the take, initialize it, and add it to tankList. The function
will return true if successful and false otherwise.
 */

bool gameFunctions::spawnTanks(map &gameMap, std::vector<tank> &tankList)
{
        tank *lookingForTank;      //If we find a tank
        //Run through the map to find a tank object

        int count = 1;
        for(int i = 1; i <= ap->agetFieldY(); i++)
        {
                for(int j = 1; j <= ap->agetFieldX(); j++)
                {
                        //If we find a tank in there
                        if(ap->agetMapObject(j, i) == tileObject::TANK)
                        {
                                if (count > ap->agetPlayerCount())
                                {
                                        ap->achangeMapObject(j, i, tileObject::EMPTY);
                                }else{
                                        lookingForTank = new tank;
                                        ap->asetPos(j, i, *lookingForTank);
                                        //lookingForTank->setPos(j,i);
                                        //Make a new tank, set it up, and put it in the std::vector
                                        ap->asetPlayerAliveCount(ap->agetPlayerAliveCount() + 1);
                                        switch(count)
                                        {
                                                case 1:
                                                        //lookingForTank->setColors(255, 0, 0);
                                                        //lookingForTank->setDirection(count - 1);
                                                        ap->asetColors(255, 0, 0, *lookingForTank);
                                                        ap->asetDirection(*lookingForTank,1);
                                                        ap->asetPlayerNumber(count - 1,ap->agetPlayerId( *lookingForTank ));
                                                        ap->asetPlayerAP(count-1);
                                                        break;
                                                case 2:
                                                        //lookingForTank->setColors(255, 0, 255);
                                                        //lookingForTank->setDirection(count - 1);
                                                        ap->asetColors(255, 0, 255, *lookingForTank);
                                                        ap->asetDirection(*lookingForTank,3);
                                                        ap->asetPlayerNumber(count - 1,ap->agetPlayerId( *lookingForTank ));
                                                        ap->asetPlayerAP(count-1);
                                                        break;
                                                case 3:
                                                        //lookingForTank->setColors(0, 0, 255);
                                                        //lookingForTank->setDirection(count - 1);
                                                        ap->asetColors(0, 0, 255, *lookingForTank);
                                                        ap->asetDirection(*lookingForTank,1);
                                                        ap->asetPlayerNumber(count - 1,ap->agetPlayerId( *lookingForTank ));
                                                        ap->asetPlayerAP(count-1);
                                                        break;
                                                case 4:
                                                        //lookingForTank->setColors(229, 244, 66);
                                                        //lookingForTank->setDirection(count - 1);
                                                        ap->asetColors(229, 244, 66, *lookingForTank);
                                                        ap->asetDirection(*lookingForTank,3);
                                                        ap->asetPlayerNumber(count - 1,ap->agetPlayerId( *lookingForTank ));
                                                        ap->asetPlayerAP(count-1);
                                                        break;
                                        }
                                        tankList.push_back(*lookingForTank);
                                        count++;
                                }
                        }
                }
        }
        //If we didn't find any tanks, return false
        printf("Created %d number of tanks.\n", (int) tankList.size());
        if(tankList.empty())
                return false;
        return true;
}




/*
   getTankMove()
Authors: Dennis Kovarik
Parameters
ifstream &fin   - An input file object representing the tank's moves
Return Value
Returns an integer representing the tank's next move.

This function accepts, as parameters, an input file object called fin. This
file should just contain a sequence of integers for testing purposes. This
function just reads and returns the next integer in this file, which is used
to represent the tank's next move.
 */

int gameFunctions::getTankMove(std::ifstream &fin)
{
        int nextMove;

        if(fin >> nextMove)
        {
                return nextMove;
        }

        //-1 is invalid move
        return -1;
}

/*
   checkProjList(std::vector<projectile> &projList, std::vector<tank> &tankList)
   Authors: Jonathan McKee

  Parameters
    projList   - This vector contains all of the currently tracked projectiles
    tankList   - This vector tracks all of the current tanks.
  Return Value

  This function checks the entire list of projectiles to see if they will be moving into and object
  or into an empty space.  If the projectile moves off the map or hits an object is removed from
  the list and the appropriate counter is incremented.
 */
void gameFunctions::checkProjList(std::vector<projectile> &projList, std::vector<tank> &tankList)
{
        //get our counter
        int counter = projList.size();
        int owner;

        //loop while we still have a possible projectile to check
        while (counter > 0)
        {
                //Subtract at start of loop to get correct projectile
                counter--;
                //check projectile move
                if (ap->acheckProjMove(projList[counter]))//true move on - false check next
                {
                        continue;  //if we can move, move to next object
                }
                //if we can't move it means something is there and we need the x/y coord
                if (!ap->aprojHit(projList[counter])) //false = not a tank, true = tank
                {
                        //check objectList once it exists
                        owner = ap->afindTankNumber(ap->agetOwner(projList[counter]));
                        //record a miss for projectile owner
                        ap->aaddMiss(tankList[owner]);
                }
                //erase projectile from list (Using item 0 + counter)
                projList.erase(projList.begin()+counter);
        }
}

/*
   checkProjMove(projectile &proj)
   Authors: Jonathan McKee

  Parameters
    proj - This is the individual projectile we are tracking
  Return Value
    true - the projectile moved with no issue
    false - Something is already in the new position

  This function checks the move of a specific projectile to see if the new space is empty
    or if something is already there.
 */
bool gameFunctions::checkProjMove(projectile &proj)
{
        int x, y;
        ap->agetPosition(x, y, proj);
        ap->achangeMapObject(x, y, tileObject::EMPTY);
        //always move forward
        ap->amoveProjectile(proj);
        //get new position
        ap->agetPosition(x, y, proj);
        //check out of bounds
        if (x > ap->agetFieldX() || x < 1 || y > ap->agetFieldY() || y < 1)
                return false;
        //check if space is empty
        if (ap->agetMapObject(x, y) != tileObject::EMPTY && ap->agetMapObject(x,y) != tileObject::BUSH)
                return false; //Not empty
        ap->achangeMapObject(x, y, tileObject::PROJECTILE);
        return true; //Empty
}

/*
   projHit(projectile &proj, std::vector<tank> &tankList)
   Authors: Jonathan McKee

  Parameters
    proj   - This vector contains all of the currently tracked projectiles
    tankList   - This vector tracks all of the current tanks.
  Return Value

  This function checks what the projectile actually hit
 */
bool gameFunctions::projHit(projectile &proj, std::vector<tank> &tankList, std::vector<tankObject> &objectList)
{
        int x, y, i;
        int tankx, tanky;
        int owner;
        //get the projectiles new position
        ap->agetPosition(x, y, proj);
        //check out of bounds
        if (x > ap->agetFieldX() || x < 1 || y > ap->agetFieldY() || y < 1)
                return false;
        //find what the projectile hit
        for (i = tankList.size() - 1; i >= 0; i--)
        {
            ap->agetPos(tankx, tanky, tankList[i]);
            //we hit this tank!
            if (x == tankx && y == tanky && ap->agetHealth(tankList[i]) > 0)
            {
              //do damage to tank
              ap->atakeDamage(tankList[i], 1);
              //get the owner
              owner = ap->afindTankNumber(ap->agetOwner(proj));
              //record a hit for projectile owner
	            ap->aaddHit(tankList[owner]);
              //check this tanks health
              if (ap->agetHealth(tankList[i]) <= 0 )
              {
                //if <= 0 give owner a kill too
                ap->aaddKill(tankList[owner], 1);
		            ap->asetPlayerAliveCount( ap->agetPlayerAliveCount() - 1 );
              }
	            return true;
            }
            //we didn't hit this tank, moving on to next
        }
        //we didn't hit any tanks...
        //..but did we hit an object?
        for (i = objectList.size() - 1; i >= 0; i--)
        {
            //just reuse our tankx, tanky's
            ap->agetObjPos(tankx, tanky, objectList[i]);
            //Oh no we hit an object
            if (x == tankx && y == tanky)
            {
              //make it hurt
                //Phase 2 - addition
              //do we need to do something for this object?
              //find the owner
              owner = ap->afindTankNumber(ap->agetOwner(proj));
              //record a miss for projectile owner
	            ap->aaddMiss(tankList[owner]);
	            return true;
            }
            //This object was safe, lets check the next one

        }

        return false;
}

/*
   gameFunctions(std::vector<tank> &tankList, std::vector<projectile> &projList)
   Authors: Jonathan McKee

  Parameters
    projList   - This vector contains all of the currently tracked projectiles
    tankList   - This vector tracks all of the current tanks.
  Return Value

  This function loops through every projectile and every tank getting and checking their moves
 */
bool gameFunctions::gameTurn( std::vector<tank> &tankList, std::vector<projectile> &projList)
{
        int i = 0, temp;
        //(player.size() > 0) ? i = player.size() - 1 : i = 0;
        //Basic turn with default tank speed 1, projectile speed 2
        //All Projectiles
        if (projList.size() >= 1)
        {
                ap->acheckProjList();
        }
        //Not so Temp AI Checker
        if (tankList.size() >= 1 && !ap->acheckProjTurn())
        {
                printf("Number of tanks. Total: %d  Alive: %d\n", ap->agetPlayerCount(), ap->agetPlayerAliveCount());
                for(i = 0; i < ap->agetPlayerCount(); i++)
                { 
                        if (ap->agetHealth(tankList[i]) > 0){
                                printf("Player %d's turn.\n", i + 1);
                                temp = ap->adoMoves(i);
                                playerMove(temp, tankList[i]);
                        }else{
                                printf("Player %d is dead.\n", i + 1);
                        }
                }
        }
        ap->atoggleProjTurn();
        if( ap->agetPlayerAliveCount() <= 1 ){
                return false;//true if game should continue, false if it should end
        }
        //A check if any projectiles are where they shouldn't be
        return true;
}

/*
   playerMove(int move, tank &tank)
   Authors: Jonathan McKee

  Parameters
    dir   - This is the current direction of the tank
    tTank   - This is the tank Object we are checking.
  Return Value

  This function checks the move sent back by the player
 */
void gameFunctions::playerMove(int move, tank &tTank)
{
        int x, y, dir;
        tileObject empty = tileObject::EMPTY;
        tileObject tank = tileObject::TANK;
        switch(move)
        {
                case 0:
                        printf("Chose to do nothing.\n");
                        break;
                case 1:
                        printf("Chose to move up.\n");
                        if (pMoveValid(tTank, 0))
                        {
                                ap->agetPos(x, y, tTank);
                                ap->achangeMapObject(x, y, empty);
                                ap->amoveUp(tTank);
                                ap->agetPos(x, y, tTank);
                                if (ap->agetMapObject(x,y) == tileObject::EMPTY)
                                  ap->achangeMapObject(x, y, tank);
                                break;
                        }
                        printf("Invalid move selected. (up)\n");
                        dir = ap->asetDirection(tTank, 0);
                        break;
                case 2:
                        printf("Chose to move right.\n");
                        if (pMoveValid(tTank, 1))
                        {
                                ap->agetPos(x, y, tTank);
                                ap->achangeMapObject(x, y, tileObject::EMPTY);
                                ap->amoveRight(tTank);
                                ap->agetPos(x, y, tTank);
                                if (ap->agetMapObject(x,y) == tileObject::EMPTY)
                                  ap->achangeMapObject(x, y, tank);
                                break;
                        }
                        dir = ap->asetDirection(tTank, 1);
                        printf("Invalid move selected.(right)\n");
                        break;
                case 3:
                        printf("Chose to move down.\n");
                        if (pMoveValid(tTank, 2))
                        {
                                ap->agetPos(x, y, tTank);
                                ap->achangeMapObject(x, y, tileObject::EMPTY);
                                ap->amoveDown(tTank);
                                ap->agetPos(x, y, tTank);
                                if (ap->agetMapObject(x,y) == tileObject::EMPTY)
                                        ap->achangeMapObject(x, y, tank);
                                break;
                        }
                        dir = ap->asetDirection(tTank, 2);
                        printf("Invalid move selected.(down)\n");
                        break;
                case 4:
                        printf("Chose to move left.\n");
                        if (pMoveValid(tTank, 3))
                        {
                                ap->agetPos(x, y, tTank);
                                ap->achangeMapObject(x, y, tileObject::EMPTY);
                                ap->amoveLeft(tTank);
                                ap->agetPos(x, y, tTank);
                                if (ap->agetMapObject(x,y) == tileObject::EMPTY)
                                ap->achangeMapObject(x, y, tank);
                                break;
                        }
                        dir = ap->asetDirection(tTank, 3);
                        printf("Invalid move selected.(left)\n");
                        break;
                case 5:
                        printf("Chose to backup.\n");
                        dir = ap->agetDirection(tTank);
                        switch(dir)
                        {
                                case 0: 
                                        if (pMoveValid(tTank, 2)){
                                                ap->amoveDown(tTank);
                                        }
                                        ap->asetDirection(tTank, 0);
                                        break;
                                case 1:
                                        if (pMoveValid(tTank, 3)){
                                                ap->amoveLeft(tTank);
                                        }
                                        ap->asetDirection(tTank, 1);
                                        break;
                                case 2:
                                        if (pMoveValid(tTank, 0)){
                                                ap->amoveUp(tTank);
                                        }
                                        ap->asetDirection(tTank, 2);
                                        break;
                                case 3:
                                        if (pMoveValid(tTank, 1)){
                                                ap->amoveRight(tTank);
                                        }
                                        ap->asetDirection(tTank, 3);
                                        break;
                        }
                case 6:
                        printf("Chose to fire.\n");
                        ap->aFire(tTank);
                        break;
                case 7:
                        printf("Chose to turn up.\n");
                        ap->asetDirection(tTank, 0);
                        break;
                case 8:
                        printf("Chose to turn right.\n");
                        ap->asetDirection(tTank, 1);
                        break;
                        case 9:
                        printf("Chose to turn down.\n");
                        ap->asetDirection(tTank, 2);
                        break;
                case 10:
                        printf("Chose to turn left.\n");
                        ap->asetDirection(tTank, 3);
                        break;
        }
}
/*
   pMoveValid(tank &tTank, int direction, int type)
   Authors: Jonathan McKee

  Parameters
    tTank  - This is the tank we are validing the move for
    int direction - the tanks current direction
    int type - 0 for tank 1 for projectile, currently defaults to 0
  Return Value
    return true - the move is valid and can be made
    return false - invald move selected

  This function checks if the move being requested is a valid move
 */
bool gameFunctions::pMoveValid(tank &tTank, int direction, int type)
{
        //Direction:  0 - up, 1 - right, 2 - down, 3 - left
        //Type: 0 - Tank, 1 - Projectile
        type = 0;
        int x = ap->agetX(tTank);
        int y = ap->agetY(tTank);

        switch (direction)
        {
                case 0: //check y + 1
                        if (y + 1 > ap->agetFieldY())
                                return false;
                        if (ap->agetMapObject(x, y + 1) == tileObject::EMPTY 
                            || ap->agetMapObject(x, y + 1) == tileObject::PROJECTILE 
                            || ap->agetMapObject(x, y + 1) == tileObject::TREE 
                            || ap->agetMapObject(x, y + 1) == tileObject::BUSH
                            || ap->agetMapObject(x, y + 1) == tileObject::WATER)
                                return true;
                        break;
                case 1: //check x + 1
                        if (x + 1 > ap->agetFieldX())
                                return false;
                        if (ap->agetMapObject(x + 1, y) == tileObject::EMPTY 
                            || ap->agetMapObject(x + 1, y) == tileObject::PROJECTILE
                            || ap->agetMapObject(x + 1, y) == tileObject::TREE 
                            || ap->agetMapObject(x + 1, y) == tileObject::BUSH
                            || ap->agetMapObject(x + 1, y) == tileObject::WATER)
                                return true;
                        break;
                case 2: //check y - 1
                        if (y - 1 <= 0)
                                return false;
                        if (ap->agetMapObject(x, y - 1) == tileObject::EMPTY 
                            || ap->agetMapObject(x, y - 1) == tileObject::PROJECTILE
                            || ap->agetMapObject(x, y - 1) == tileObject::TREE 
                            || ap->agetMapObject(x, y - 1) == tileObject::BUSH
                            || ap->agetMapObject(x, y - 1) == tileObject::WATER)
                                return true;
                        break;
                case 3: //check x - 1
                        if (x - 1 <=0)
                                return false;
                        if (ap->agetMapObject(x - 1, y) == tileObject::EMPTY 
                            || ap->agetMapObject(x - 1, y) == tileObject::PROJECTILE
                            || ap->agetMapObject(x - 1, y) == tileObject::TREE 
                            || ap->agetMapObject(x - 1, y) == tileObject::BUSH
                            || ap->agetMapObject(x - 1, y) == tileObject::WATER)
                                return true;
                        break;
        }
        return false;
}
/*
   takeTurn()
Authors: Dennis Kovarik
Parameters
int nextMove    - An integer representing the tank's next move
tank &theTank   - An instance of the tank
vector<projectile> &projectileList - A vector instances of the
projectile class used to represent all projectiles
on the map
Return Value
Returns void

This function causes the tank to perform some action based on the value
held in the nextMove var. If nextMove is not the same as theTank's current
direction, then the function will just change the direction to the tank. If
nextMove is between 0 and 3 inclusive and nextMove is that same as the
tank's current direction, then the function will move the tank and return.
Otherwise if nextMove is equal to 4, then the function 'fire' is called to
simulate the tank firing.
 */

//This function is responsible for performing the tank turn
void gameFunctions::takeTurn(int nextMove, tank &theTank, std::vector<projectile> &projectileList)
{
        //If the direcetion is different than the current direction, then just
        //set the new direction
        //if(nextMove < 4 && theTank.getDirection() != nextMove)
        if(nextMove < 4 && ap->agetDirection(theTank) != nextMove)
        {
                //theTank.setDirection(nextMove);
                ap->asetDirection(theTank, nextMove);
        }
        //Next move is to fire the tank indicated by a 4 in input file
        else if(nextMove >= 4)
        {
                //fire(theTank, projectileList);
                ap->aFire(theTank);
        }
        //else move the tank
        //0 indicates move up
        else if(nextMove == 0)
        {
                //theTank.moveUp(1);
                ap->amoveUp(theTank);
        }
        //1 indicates move to the right
        else if(nextMove == 1)
        {
                //theTank.moveRight(1);
                ap->amoveRight(theTank);
        }
        //2 indicates move down
        else if(nextMove == 2)
        {
                //theTank.moveDown(1);
                ap->amoveDown(theTank);
        }
        //3 indicates move to the left
        else if(nextMove == 3)
        {
                //theTank.moveLeft(1);
                ap->amoveLeft(theTank);
        }


        return;
}
/*
   fire()
Authors: Dennis Kovarik
Parameters
tank theTank   - An instance of the tank
vector<projectile> &projectileList - A vector instances of the
projectile class used to represent all projectiles
on the map
Return Value
Returns true if the function was able to create an instance of the
projectile class and add it to the vector of projectiles
'projectileList'.

This function simulates the firing of the tank. It will create an instance
of the projectile class, set its x, y, direction, and owner fields to
theTank's x, y, direction, and playerId fields. The function will then
increment the projectile's position by 1 depending on its direction and add
it to the vector of projectiles projectileList.
 */

bool gameFunctions::fire(tank theTank, std::vector<projectile> &projectileList)
{
        int x, y, d;

        d = ap->agetDirection(theTank);

        ap->agetPos(x, y, theTank);

        if(d == 0)
        {
                y++;
        }
        else if(d == 1)
        {
                x++;
        }
        else if(d == 2)
        {
                y--;
        }
        else if(d == 3)
        {
                x--;
        }
        //check if off the map
        if (x < 1 || x > ap->agetFieldX() || y < 1 || y > ap->agetFieldY()){
                printf("Fired off the map.\n");
                ap->aaddMiss(theTank);
                return false;
        }
        //check if right next to a rock or tree
        if (ap->agetMapObject(x, y) == tileObject::ROCK || ap->agetMapObject(x, y) == tileObject::TREE){
                printf("Fired Directly into a rock or tree.\n");
                ap->aaddMiss(theTank);
                return false;
        }
        //check if right next to a tank
        projectile newProjectile(2, x, y, d, ap->agetPlayerId(theTank));

        projectileList.push_back(newProjectile);
        ap->achangeMapObject(x,y, tileObject::PROJECTILE);
        return true;
}

/*
   createObject()
Authors: Jonathan McKee
Parameters
vector<tankObject> &objectList - A vector instances of the
tankObject class used to represent all objects
on the map
Return Value
Returns true if the function was able to create the object

 */

bool gameFunctions::createObject(int x, int y, int type, std::vector<tankObject> &objectList)
{
        tankObject *newObject;
        printf("Adding an object.\n");
        switch (type)
        {
                case 1:
                        {
                                newObject = new tankObject(x, y, type, ap->agetTurn());
                                ap->achangeMapObject(x,y, tileObject::TREE);
                                break;}
                case 5:{
                               newObject = new tankObject(x, y, type, ap->agetTurn());
                               ap->achangeMapObject(x,y, tileObject::ROCK);
                               break;}
                case 7:{
                               newObject = new tankObject(x, y, type, ap->agetTurn());
                               ap->achangeMapObject(x,y, tileObject::BUSH);
                               break;}
                default:
                       return false;
        }
        objectList.push_back(*newObject);
        return true;
}

bool gameFunctions::checkMove(int Xcord, int Ycord)
{
        if(ap->agetMapObject(Xcord, Ycord) == tileObject::EMPTY)
                return true;
        return false;
}
/*
   checkProjectilesn()
Authors: Dennis Kovarik
Parameters
vector<tank> tankList - A vector of tanks representing all tanks on the
map.
vector<projectile> &projectileList - A vector instances of the
projectile class used to represent all projectiles
on the map
map &gamemap - An instance of the map class which holds the map itself

Return Value
Returns none

This function checks the projectile's current position against the map
boundaries and the positions of all the tanks. If a projectile is found to
have the same x and y positions as one of the tanks, then that projectile
will be erased from projectileList and damage will be added to the
appropriate tank by calling the tank class memberfunction 'takeDamage()'. If
the projectile is found to be off the map, then the projectile will just be
erased from projectileList.
 */

void gameFunctions::checkProjectiles(std::vector<tank> &tankList, std::vector<projectile> &projectileList, map &gameMap)
{
        int projectileX;    //projectile x position
        int projectileY;    //projectile y position
        int tankX;      //tank x position
        int  tankY;     //tank y position
        unsigned int i, j;    //simple count vars for loops



        //For each tank, check if it was hit by a projectile
        for(i = 0; i < tankList.size(); i++)
        {
                //Get each tank's x and y positions
                //tankList[i].getPos(tankX, tankY);
                ap->agetPos(tankX, tankY, tankList[i]);

                //For each projectile, check if it has the same x an y values
                //as the tank that we are currently checking
                for(j = 0; j < projectileList.size(); j++)
                {
                        //get the projectile's current position
                        //projectileList[j].getPosition(projectileX, projectileY);
                        ap->agetPosition(projectileX, projectileY, projectileList[j]);

                        //Check if the projectile is on the same square as the
                        //tank
                        if(tankX == projectileX && tankY == projectileY)
                        {
                                //If the projectile and the tank are on the same
                                //square, then add damage to the tanke and
                                //erase the projectile
                                projectileList.erase(projectileList.begin() + j);
                                //tankList[i].takeDamage(1);
                                ap->atakeDamage(tankList[i]);
                                j--;
                        }
                        //Check if the projectile is off the map
                        else if(projectileX < 1|| projectileY < 1
                                        || projectileX > ap->agetFieldX()
                                        || projectileX > ap->agetFieldX())
                                //|| projectileX > gameMap.getFieldX()
                                //|| projectileX > gameMap.getFieldX())
                        {
                                //Erase the projectile
                                projectileList.erase(projectileList.begin() + j);
                                //Back up one so we don't skip any projectiles
                                j--;
                        }
                }
        }
}
/*
   displayAscii()
Authors: Dennis Kovarik
Parameters
vector<tank> tankList - A vector of tanks representing all tanks on the
map.
vector<projectile> &projectileList - A vector instances of the
projectile class used to represent all projectiles
on the map
map &gamemap - An instance of the map class which holds the map itself

Return Value
Returns void

This function displays the map on the screen in ascii. It will create a new
2d array and populate it with tanks from tankList and projectiles from
projectileList. The characters used to represent the tanks differ slightly
based on their current direction. The function will use the map bounds
held in the map object gameMap as the bounds for the array. The array, which
represents the map, will be displayed to the screen. This function returns
void.
 */

bool gameFunctions::displayAscii(map &gameMap, std::vector<tank> &tankList, std::vector<projectile> &projectileList, std::vector<tankObject> &objectList)
{
        int dir;
        int tx, ty, px, py;
        char area[25][25];
        char c;
        int temp;
        unsigned int i, j;



        //Fill map with 'X'
        for(i = 0; i < 15; i++)
        {
                for(j = 0; j < 21; j++)
                {
                        area[i][j] = 'X';
                }
        }



        //Place projectiles on the map
        for(i = 0; i < projectileList.size(); i++)
        {
                //projectileList[i].getPosition(px, py);
                ap->agetPosition(px, py, projectileList[i]);
                area[py][px] = 'o';
        }


        //Place tanks on the map indicating current direction
        for(i = 0; i < tankList.size(); i++)
        {
                //tankList[i].getPos(tx, ty);
                ap->agetPos(tx, ty, tankList[i]);

                //dir = tankList[i].getDirection();
                dir = ap->agetDirection(tankList[i]);

                if(dir == 0 && ap->agetHealth(tankList[i]) > 0)
                {
                        area[ty][tx] = '^';
                }
                else if(dir == 1 && ap->agetHealth(tankList[i]) > 0)
                {
                        area[ty][tx] = '>';
                }
                else if(dir == 2 && ap->agetHealth(tankList[i]) > 0)
                {
                        area[ty][tx] = 'v';
                }
                else if(dir == 3 && ap->agetHealth(tankList[i]) > 0)
                {
                        area[ty][tx] = '<';
                }
                else if(ap->agetHealth(tankList[i]) > 0)
                {
                        area[ty][tx] = '?';
                }
        }

        //Place objects on the map
        for(i = 0; i < objectList.size(); i++)
        {
                ap->agetObjPos(px, py, objectList[i]);
                temp  = ap->agetObjType(objectList[i]);
                if (temp == 1) 
                        area[py][px] = 'T';
                if (temp == 5)
                        area[py][px] = 'R';
                if (temp == 7)
                        area[py][px] = 'B';
        }

        //Sets top boarder
        for(int i = 0; i <= ap->agetFieldX() + 1; i++)
                std::cout << "*  ";
        std::cout << std::endl;


        //Displays rows
        for(int i = 10; i > 0; i--)
        {
                std::cout << "*  ";
                for(int j = 1; j <= 20; j++)
                {
                        c = area[i][j];
                        ((c == 'X') ?std::cout << " " : std::cout << c);
                        std::cout << "  ";
                }
                std::cout << "*" << std::endl;
        }

        //Sets bottom boarder
        for(int i = 0; i <= ap->agetFieldX() + 1; i++)
                std::cout << "*  ";
        std::cout << std::endl;

        std::cout << std::endl;

        return true;
}

/*
   void drawHeader(int fieldx, int fieldy)
   Author(s): Gwyneth Kardelis

   Parameters
   int fieldx - the width of the field/map
   int fieldy - the hieght of the field/map
   Return Value
   none

   This function creates the players with life total and kills, game title and
   how to get to the help menu and other info for the header
 */
void gameFunctions::headerText(std::vector<tank> tankList, int fieldx, int fieldy)
{
        fieldy++;
        int x = glutGet(GLUT_WINDOW_WIDTH);
        int y = glutGet(GLUT_WINDOW_HEIGHT);

        int color[] = {255, 255, 255};

        int hits = 0;
        int life = 0;
        int misses = 0;
        int kills = 0;
        int count = 1;
        int offset = 30;
        char str[127];

        //title
        sprintf( str, "Battle Tanks");
        ap->adrawHeader(str, 255, 255, 255, x/2 - 40, y - 40, true);

        //turn counter
        sprintf( str, "Turn: %d", ap->agetTurn());
        ap->adrawHeader(str, 255, 255, 255, x - 70, y - 30, false);

        /* Removed -- William Doering
        //how to get to help
        sprintf( str, "Press h for help" );
        ap->adrawHeader(str, 255, 255, 255, x - 100, y - 60, false);
         */

        //Draw table header for player stats
        sprintf( str, "Player #:  HP  :  Hits  :  Misses  :  Kills");
        ap->adrawHeader(str, 245, 245, 245, 1, y - 15, false);

        //players
        for(std::vector<tank>::iterator it = tankList.begin(); it != tankList.end(); ++it)
        {
                ap->agetColors(color[0], color[1], color[2], *it);
                hits = ap->agetHits(*it);
                life = ap->agetHealth(*it);
                misses = ap->agetMiss(*it);
                kills = ap->agetKill(*it);
                sprintf( str, "Player %d:%*d%*d%*d%*d", count, 5, life, 7, hits, 12, misses, 12, kills);
                //drawHeader(fieldx, fieldy, str, color[0], color[1], color[2], 1, y - 15, false);
                ap->adrawHeader(str, color[0], color[1], color[2], 1, y - offset, false);
                count++;
                y -= 15;
        }

}

/*
   void drawHeader(int fieldx, int fieldy)
   Author(s): Gwyneth Kardelis

   Parameters
   int fieldx - the width of the field/map
   int fieldy - the hieght of the field/map
   char *str - what is to be displayed
   int r - the red color value
   int g - the green color value
   int b - the blue color value
   int xPos - the x position of the text
   int yPos - the y position of the text
   bool title - title (true it is the title otherwise it other header text)
   Return Value
   none

   This function is to draw the players with life total and kills, game title and
   how to get to the help menu
 */
void gameFunctions::drawHeader(int fieldx, int fieldy, char *str, int r, int g, int b,
                int xPos, int yPos, bool title)
{
        fieldy++;

        //set color
        glColor3ub(r, g, b);
        //set position
        glRasterPos2i(xPos, yPos); //place in the middle of the top

        //display title
        if(title == true)
        {
                while(*str)
                {
                        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *str);
                        str++;
                }
        }
        else if(title == false)//all other text
        {
                while(*str)
                {
                        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, *str);
                        str++;
                }
        }

}

int gameFunctions::aGameLoop(std::vector<tank> &tankList, std::vector<projectile> &projectileList, map &gameMap, gameSetting &settings)
{
        int turnRatio = 8;    //Game loop iterations to tank turns ratio
        //int turn = 0;     //The current turn number
        int nextMove;     //The tank's next move
        std::ifstream fin;    //Input file for testing purposes
        int alive = 2;      //Number of tanks still alive
        unsigned int i;     //Simple increment counter

        //spawnTanks(gameMap, tankList);
        ap->aspawnTanks();
        alive = tankList.size();
        //tankList[0].setDirection(1);
        //tankList[1].setDirection(3);
        ap->asetDirection(tankList[0],1);
        ap->asetDirection(tankList[1],3);

        //Open testing files
        fin.open("testing/QaTesting1");

        if(!fin.is_open())
        {
                printf("Testing file not found.\n");
                return 3;
        }


        //displayAscii(gameMap, tankList, projectileList);
        ap->adisplayAscii();

        //Game Loop
        for(int count = 0; alive > 1 && ap->agetTurn() < ap->agetMaxTurns() && !fin.eof(); count++)
        {
                std::system("clear");


                //iterate through all projectiles
                for(i = 0; i < projectileList.size(); i++)
                {
                        //move projectiles
                        //projectileList[i].moveProjectile();
                        //checkProjectiles(tankList, projectileList, gameMap);
                        ap->amoveProjectile(projectileList[i]);
                        ap->acheckProjectiles();
                }



                //manage tank turns
                //For now the tank turns will be in numberical order
                if(count % turnRatio == 0)
                {
                        //turn++;
                        //update turn counter
                        ap->aturnPassed();

                        for(i = 0; i < tankList.size(); i++)
                        {
                                //check that tank is not dead
                                //if( tankList[i].getHealth() > 0 )
                                if ( ap->agetHealth(tankList[i]) > 0 )
                                {
                                        //get tank move
                                        nextMove = getTankMove( fin );

                                        //take tank turn
                                        //takeTurn( nextMove, tankList[i], projectileList );
                                        ap->atakeTurnA(nextMove, tankList[i]);
                                }
                                else
                                {
                                        alive--;
                                }
                        }
                }
                //manage projectile


                //check for dead tanks?
                //May not need to, just don't give turns to dead tanks


                //displayAscii( gameMap, tankList, projectileList );
                ap->adisplayAscii();

                usleep(50000);
        }

        std::system( "clear" );

        //displayAscii( gameMap, tankList, projectileList );
        ap->adisplayAscii();

        //Display Winner?

        std::system( "clear" );

        fin.close();

        return 0;
}
/*
   void drawGrid(int fieldx, int fieldy)
   Author(s): Levi Butts

   Parameters
   int fieldx - the width of the field/map
   int fieldy - the hieght of the field/map
   Return Value
   none

   This function creates a 20 by 10 grid on the map
 */

void gameFunctions::drawGrid(int fieldx, int fieldy)
{
        fieldy++;
        int x = glutGet(GLUT_WINDOW_WIDTH);
        int y = glutGet(GLUT_WINDOW_HEIGHT);
        float xint = (float)x/(float)fieldx;
        float yint = (float)y/(float)fieldy;

        float color[] = {1.0f, 1.0f, 1.0f};

        for(int i = 1; i <= fieldx; i++)
        {
                glLineWidth(1);
                glColor3fv(color);
                glBegin(GL_LINES);
                glVertex2f((xint*i), 0);
                glVertex2f((xint*i), y - yint);
                glEnd();
        }

        for(int j = 1; j <= fieldy; j++)
        {
                glLineWidth(1);
                glColor3fv(color);
                glBegin(GL_LINES);
                glVertex2f(0, (yint*j));
                glVertex2f(x, (yint*j));
                glEnd();
        }

}
/*
   void drawTanks(int fieldx, int fieldy)
   Author(s): Levi Butts

   Parameters
   int fieldx - the width of the field/map
   int fieldy - the hieght of the field/map
   Return Value
   none

   This function creates the tanks on the map
 */

void gameFunctions::drawTanks(std::vector<tank> tankList, int fieldx, int fieldy)
{
        int color[] = {0, 0, 0};
        int count = 1;

        for(std::vector<tank>::iterator it = tankList.begin(); it != tankList.end(); ++it)
        {
                ap->agetColors(color[0], color[1], color[2], *it);
                //drawTank(it->getX(), it->getY(), fieldx, fieldy, color);
                drawTank(ap->agetX(*it), ap->agetY(*it), ap->agetFieldX(),
                                ap->agetFieldY(), color,ap->agetDirection(*it), ap->agetHealth(*it));
                //printf("Tank at: (%d, %d).\n",it->getX(),it->getY());
                printf("T%d: (%d, %d), ", count, ap->agetX(*it),ap->agetY(*it));
                count++;
        }
        printf("\n");
}

/*
	void drawTank(int fieldx, int fieldy)
	Author(s): Levi Butts

	Parameters
		int fieldx - the width of the field/map
		int fieldy - the hieght of the field/map
	Return Value
		none

	This function creates the tanks on the map
*/

void gameFunctions::drawTank(int x, int y, int fieldx, int fieldy, int color[],int dir, int health)
{
        fieldy++;

        int winX = glutGet(GLUT_WINDOW_WIDTH);
        int winY = glutGet(GLUT_WINDOW_HEIGHT);

        float xint = (float)winX/(float)fieldx;
        float yint = (float)winY/(float)fieldy;

        float tankLength = 3*xint/5;
        float tankHeight = 3*yint/5;

        float xOff = xint/5;
        float yOff = yint/5;

        int centX, centY;

        // std::cout << "Drawing tank at location (" << x << ", " << y << "), ";
        // std::cout << "for map of size " << fieldx << "X" << fieldy << "\n";

        //y = fieldy - y;
        x--; y--;
        if(y < 0)
                y++;

        // std::cout << "Drawing tank at relative coordinates: [" << x << ", " << y << "]\n";

        glColor3ub(0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f((xint*x + xOff - 1), (yint*y + yOff - 1));
        glVertex2f((xint*x + xOff + tankLength + 1), (yint*y + yOff - 1));
        glVertex2f((xint*x + xOff + tankLength + 1), (yint*y + yOff + tankHeight + 1));
        glVertex2f((xint*x + xOff - 1), (yint*y + yOff + tankHeight + 1));
        glEnd();

        glColor3ub(color[0], color[1], color[2]);
        glBegin(GL_POLYGON);
        glVertex2f((xint*x + xOff), (yint*y + yOff));
        glVertex2f((xint*x + xOff + tankLength), (yint*y + yOff));
        glVertex2f((xint*x + xOff + tankLength), (yint*y + yOff + tankHeight));
        glVertex2f((xint*x + xOff), (yint*y + yOff + tankHeight));
        glEnd();

        centX = xint*x + xOff + (tankLength/2);
        centY = yint*y + yOff + (tankHeight/2);


        switch(dir)
        {
                case 0:
                        glColor3ub(0, 0, 0);
                        glBegin(GL_POLYGON);
                        glVertex2f(centX - (tankLength/6) - 1, centY - 1);
                        glVertex2f(centX - (tankLength/6) - 1, centY + (2*tankHeight/3) + 1);
                        glVertex2f(centX + (tankLength/6) + 1, centY + (2*tankHeight/3) + 1);
                        glVertex2f(centX + (tankLength/6) + 1, centY - 1);
                        glEnd();

                        glColor3ub(color[0], color[1], color[2]);
                        glBegin(GL_POLYGON);
                        glVertex2f(centX - (tankLength/6), centY);
                        glVertex2f(centX - (tankLength/6), centY + (2*tankHeight/3));
                        glVertex2f(centX + (tankLength/6), centY + (2*tankHeight/3));
                        glVertex2f(centX + (tankLength/6), centY);
                        glEnd();

                        break;
                case 1:
                        glColor3ub(0, 0, 0);
                        glBegin(GL_POLYGON);
                        glVertex2f(centX - 1, centY - (tankHeight/6) - 1);
                        glVertex2f(centX + (2*tankLength/3) + 1, centY - (tankHeight/6) - 1);
                        glVertex2f(centX + (2*tankLength/3) + 1, centY + (tankHeight/6) + 1);
                        glVertex2f(centX - 1, centY + (tankHeight/6) + 1);
                        glEnd();

                        glColor3ub(color[0], color[1], color[2]);
                        glBegin(GL_POLYGON);
                        glVertex2f(centX, centY - (tankHeight/6));
                        glVertex2f(centX + (2*tankLength/3), centY - (tankHeight/6));
                        glVertex2f(centX + (2*tankLength/3), centY + (tankHeight/6));
                        glVertex2f(centX, centY + (tankHeight/6));
                        glEnd();

                        break;
                case 2:
                        glColor3ub(0, 0, 0);
                        glBegin(GL_POLYGON);
                        glVertex2f(centX - (tankLength/6) - 1, centY + 1);
                        glVertex2f(centX - (tankLength/6) - 1, centY - (2*tankHeight/3) - 1);
                        glVertex2f(centX + (tankLength/6) + 1, centY - (2*tankHeight/3) - 1);
                        glVertex2f(centX + (tankLength/6) + 1, centY + 1);
                        glEnd();

                        glColor3ub(color[0], color[1], color[2]);
                        glBegin(GL_POLYGON);
                        glVertex2f(centX - (tankLength/6), centY);
                        glVertex2f(centX - (tankLength/6), centY - (2*tankHeight/3));
                        glVertex2f(centX + (tankLength/6), centY - (2*tankHeight/3));
                        glVertex2f(centX + (tankLength/6), centY);
                        glEnd();

                        break;
                case 3:
                        glColor3ub(0, 0, 0);
                        glBegin(GL_POLYGON);
                        glVertex2f(centX + 1, centY - (tankHeight/6) - 1);
                        glVertex2f(centX - (2*tankLength/3) - 1, centY - (tankHeight/6) - 1);
                        glVertex2f(centX - (2*tankLength/3) - 1, centY + (tankHeight/6) + 1);
                        glVertex2f(centX + 1, centY + (tankHeight/6) + 1);
                        glEnd();

                        glColor3ub(color[0], color[1], color[2]);
                        glBegin(GL_POLYGON);
                        glVertex2f(centX, centY - (tankHeight/6));
                        glVertex2f(centX - (2*tankLength/3), centY - (tankHeight/6));
                        glVertex2f(centX - (2*tankLength/3), centY + (tankHeight/6));
                        glVertex2f(centX, centY + (tankHeight/6));
                        glEnd();

                        break;
        }

        int offsetx, offsety;
        float d2g = 3.141592654/180.0; //converts degrees to radians

        glColor3ub(0, 0, 0);
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) //creates a polygon with a 360 edges
        {
                float rad = i*d2g;
                glVertex2f(centX + cos(rad)*(3*tankLength/8), centY + sin(rad)*(3*tankHeight/8));
        }
        glEnd();

        glColor3ub(color[0], color[1], color[2]);
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) //creates a polygon with a 360 edges
        {
                float rad = i*d2g;
                if(i >= 0 && i < 90)
                {
                        offsetx = 0 - 1;
                        offsety = 0 - 1;
                }
                else if(i >= 90 && i < 180)
                {
                        offsetx = 1;
                        offsety = 0 - 1;
                }
                else if(i >= 180 && i < 270)
                {
                        offsetx = 1;
                        offsety = 1;
                }
                else if(i >= 270 && i < 360)
                {
                        offsetx = 0 - 1;
                        offsety = 1;
                }
                glVertex2f(centX + cos(rad)*(3*tankLength/8) + offsetx,
                                centY + sin(rad)*(3*tankHeight/8)+ offsety);
        }
        glEnd();

        if(health <= 0)
        {
                glLineWidth(4);
                glColor3ub(0, 0, 0);
                glBegin(GL_LINES);
                glVertex2f((xint*x), yint*y);
                glVertex2f((xint*(x+1)), yint*(y+1));
                glEnd();

                glLineWidth(4);
                glColor3ub(0, 0, 0);
                glBegin(GL_LINES);
                glVertex2f((xint*x), yint*(y+1));
                glVertex2f((xint*(x+1)), yint*y);
                glEnd();

                glLineWidth(2);
                glColor3ub(255, 0, 0);
                glBegin(GL_LINES);
                glVertex2f((xint*x), yint*y);
                glVertex2f((xint*(x+1)), yint*(y+1));
                glEnd();

                glLineWidth(2);
                glColor3ub(255, 0, 0);
                glBegin(GL_LINES);
                glVertex2f((xint*x), yint*(y+1));
                glVertex2f((xint*(x+1)), yint*y);
                glEnd();

        }


}
/*
	void setGameFunc(api *ap)
	Author(s): Jonathan McKee

	Parameters
		api *ap - A pointer to the API object
	Return Value
		none

	This function links the gameFunctions object to the API
*/

void gameFunctions::setGameFunc(api *ap)
{
        this->ap = ap;
}


/*
   void drawProjectiles(int fieldx, int fieldy)
   Author(s): William Doering

   Parameters
   int fieldx - the width of the field/map
   int fieldy - the hieght of the field/map
   int x - start x coordinates
   int y - start y coordinates
   int color[] - the color of the projectile
   Return Value
   none

   This function creates the protectiles coming from the tanks in their
   corresponding colors
 */
void gameFunctions::drawProjectiles(std::vector<projectile> projectileList, std::vector<tank> tankList, int fieldx, int fieldy)
{
        //Variables used
        int color[] = {0, 0, 0};	//Color of projectile
        int x, y;			//Position of projectile

        //Loop through and draw all projectiles
        for(std::vector<projectile>::iterator it = projectileList.begin(); it != projectileList.end(); ++it)
        {
                //Get position of current projectile and draw
                ap->agetPosition(x, y, *it);
                int tempID = ap->agetOwner(*it);
                for(std::vector<tank>::iterator tit = tankList.begin(); tit != tankList.end(); ++tit)
                {
                        if(ap->agetPlayerId(*tit) == tempID)
                        {
                                ap->agetColors(color[0], color[1], color[2], *tit);
                                break;
                        }
                }
                drawProjectile(x, y, ap->agetFieldX(), ap->agetFieldY(), color);
        }
}

/*
	void drawTank(int fieldx, int fieldy)
	Author(s): William Doering

	Parameters
		int fieldx - the width of the field/map
		int fieldy - the hieght of the field/map
		int x - start x coordinates
		int y - start y coordinates
		int color[] - the color of the projectile
	Return Value
		none

	This function creates the protectiles coming from the tanks in their
	corresponding colors
*/

void gameFunctions::drawProjectile(int x, int y, int fieldx, int fieldy, int color[])
{
        //Increment fieldy
        fieldy++;

        //Get window Dimensions
        int winX = glutGet(GLUT_WINDOW_WIDTH);
        int winY = glutGet(GLUT_WINDOW_HEIGHT);

        //Adjust for different window dimensions
        float xint = (float)winX/(float)fieldx;
        float yint = (float)winY/(float)fieldy;

        //Get dimensions of bullets in relation to window
        float pLength = 1*xint/6;
        float pHeight = 1*yint/6;

        //Get offset of bullets from edge
        float xOff = 2*xint/5;
        float yOff = 2*yint/5;

        //Declare center coordinates for bullets
        int centX;
        int centY;

        x--;
        y--;
        if (y < 0)
                y++;

        //Get center of bullet
        centX = xint*x + xOff + (pLength/2);
        centY = yint*y + yOff + (pHeight/2);

        //Convert degrees to radians
        float d2r = 3.141592654/180.0;

        glColor3ub(0, 0, 0);
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) //creates a polygon with a 360 edges
        {
                float rad = i*d2r;
                glVertex2f(centX + cos(rad)*pLength, centY + sin(rad)*pHeight);
        }
        glEnd();

        glColor3ub(color[0], color[1], color[2]);
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) //creates a polygon with a 360 edges
        {

                int offsetx, offsety;
                float rad = i*d2r;
                if(i >= 0 && i < 90)
                {
                        offsetx = 0 - 1;
                        offsety = 0 - 1;
                }
                else if(i >= 90 && i < 180)
                {
                        offsetx = 1;
                        offsety = 0 - 1;
                }
                else if(i >= 180 && i < 270)
                {
                        offsetx = 1;
                        offsety = 1;
                }
                else if(i >= 270 && i < 360)
                {
                        offsetx = 0 - 1;
                        offsety = 1;
                }
                glVertex2f(centX + cos(rad)*pLength + offsetx,
                                centY + sin(rad)*pHeight+ offsety);
        }
        glEnd();
}
/*
	void drawObjects(vector<tankObject> objectList, int fieldx, int fieldy)
	Author(s): Jonathan McKee

	Parameters
		objectList - The vector we pull our objects from
		int fieldx - the width of the field/map
		int fieldy - the hieght of the field/map
	Return Value
		none

	This function loops through our objectList in order to draw every object
*/

void gameFunctions::drawObjects(std::vector<tankObject> objectList, int fieldx, int fieldy)
{
        //printf("Drawing objects!");
        int x, y, type = 0, count = 1;
        int color[] = { 0, 0, 0};
        int sColor[] = { 0, 0, 0};
        for(std::vector<tankObject>::iterator it = objectList.begin(); it != objectList.end(); ++it)
        {
                type = ap->agetObjType(*it);
                ap->agetObjPos(x, y, *it);
                ap->agetObjColors(color[0], color[1], color[2], *it);
                if (type == 1)
                {
                  ap->agetObjSecondaryColors(sColor[0], sColor[1], sColor[2], *it);
                  drawTree(x, y, ap->agetFieldX(), ap->agetFieldY(), color, sColor);
                  //printf("T%d: (%d, %d), ", count, x, y);
                }
                else if (type == 5)
                {
                  drawRock(x, y, ap->agetFieldX(), ap->agetFieldY(), color);
                  //printf("T%d: (%d, %d), ", count, x, y);
                }
                else if (type == 7)
                {
                  drawBush(x, y, ap->agetFieldX(), ap->agetFieldY(), color);
                  //printf("T%d: (%d, %d), ", count, x, y);
                }
                count++;
        }
        //printf(" Drew %d objects.\n", count);
}

/*
	void drawTre(int x, int y, int fieldx, int fieldy, int color[], int sColor[])
	Author(s): Jonathan McKee

	Parameters
		int x - the x corrdinate
		int y - the y coordinate
		int fieldx - the width of the field/map
		int fieldy - the hieght of the field/map
		int color[] -  the array of colors for the trunk
		int sColor[] - the array of colors for the leaves
	Return Value
		none

	This function draws a tree on the OpenGL display at the x, y coordinate passed in
*/

void gameFunctions::drawTree(int x, int y, int fieldx, int fieldy, int color[], int sColor[])
{
        fieldy++;

        int winX = glutGet(GLUT_WINDOW_WIDTH);
        int winY = glutGet(GLUT_WINDOW_HEIGHT);

        float xint = (float)winX/(float)fieldx;
        float yint = (float)winY/(float)fieldy;

        float tankLength = 3*xint/5;
        float tankHeight = 3*yint/5;

        float xOff = xint/5;
        float yOff = yint/5;

        int centX, centY;

        // std::cout << "Drawing tank at location (" << x << ", " << y << "), ";
        // std::cout << "for map of size " << fieldx << "X" << fieldy << "\n";

        //y = fieldy - y;
        x--; y--;
        if(y < 0)
                y++;

        centX = xint*x + xOff + (tankLength/2);
        centY = yint*y + yOff + (tankHeight/2);

        
        glColor3ub(0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(centX - (tankLength/6) - 1, centY + 1);
        glVertex2f(centX - (tankLength/6) - 1, centY - (2*tankHeight/3) - 1);
        glVertex2f(centX + (tankLength/6) + 1, centY - (2*tankHeight/3) - 1);
        glVertex2f(centX + (tankLength/6) + 1, centY + 1);
        glEnd();

        glColor3ub(color[0], color[1], color[2]);
        glBegin(GL_POLYGON);
        glVertex2f(centX - (tankLength/6), centY);
        glVertex2f(centX - (tankLength/6), centY - (2*tankHeight/3));
        glVertex2f(centX + (tankLength/6), centY - (2*tankHeight/3));
        glVertex2f(centX + (tankLength/6), centY);
        glEnd();

        int offsetx, offsety;
        yOff *=1.75;
        centX = xint*x + xOff + (tankLength/2);
        centY = yint*y + yOff + (tankHeight/2);
        float d2g = 3.141592654/180.0; //converts degrees to radians
        
        //top ball
        glColor3ub(0, 0, 0);
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) //creates a polygon with a 360 edges
        {
                float rad = i*d2g;
                glVertex2f(centX + cos(rad)*(3*tankLength/6), centY + sin(rad)*(3*tankHeight/6));
        }
        glEnd();

        glColor3ub(sColor[0], sColor[1], sColor[2]);
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) //creates a polygon with a 360 edges
        {
                float rad = i*d2g;
                if(i >= 0 && i < 90)
                {
                        offsetx = 0 - 1;
                        offsety = 0 - 1;
                }
                else if(i >= 90 && i < 180)
                {
                        offsetx = 1;
                        offsety = 0 - 1;
                }
                else if(i >= 180 && i < 270)
                {
                        offsetx = 1;
                        offsety = 1;
                }
                else if(i >= 270 && i < 360)
                {
                        offsetx = 0 - 1;
                        offsety = 1;
                }
                glVertex2f(centX + cos(rad)*(3*tankLength/6) + offsetx,
                centY + sin(rad)*(3*tankHeight/6)+ offsety);
        }
        glEnd();

}

/*
	void drawRock(int x, int y, int fieldx, int fieldy, int color[])
	Author(s): Jonathan McKee

	Parameters
		int x - the x corrdinate
		int y - the y coordinate
		int fieldx - the width of the field/map
		int fieldy - the hieght of the field/map
		int color[] -  the array of colors for the trunk
	Return Value
		none

	This function draws a rock on the OpenGL display at the x, y coordinate passed in
*/
void gameFunctions::drawRock(int x, int y, int fieldx, int fieldy, int color[])
{
        //Increment fieldy
        fieldy++;

        //Get window Dimensions
        int winX = glutGet(GLUT_WINDOW_WIDTH);
        int winY = glutGet(GLUT_WINDOW_HEIGHT);

        //Adjust for different window dimensions
        float xint = (float)winX/(float)fieldx;
        float yint = (float)winY/(float)fieldy;

        //Get dimensions of rocks in relation to window
        float pLength = 1*xint/3;
        float pHeight = 1*yint/3;

        //Get offset of bullets from edge
        float xOff = 2*xint/6;
        float yOff = 2*yint/6;

        //Declare center coordinates for rocks
        int centX;
        int centY;

        x--;
        y--;
        if (y < 0)
                y++;

        //Get center of rocks
        centX = xint*x + xOff + (pLength/2);
        centY = yint*y + yOff + (pHeight/2);

        //Convert degrees to radians
        float d2r = 3.141592654/180.0;

        glColor3ub(0, 0, 0);
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) //creates a polygon with a 360 edges
        {
                float rad = i*d2r;
                glVertex2f(centX + cos(rad)*pLength, centY + sin(rad)*pHeight);
        }
        glEnd();

        glColor3ub(color[0], color[1], color[2]);
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) //creates a polygon with a 360 edges
        {

                int offsetx, offsety;
                float rad = i*d2r;
                if(i >= 0 && i < 90)
                {
                        offsetx = 0 - 1;
                        offsety = 0 - 1;
                }
                else if(i >= 90 && i < 180)
                {
                        offsetx = 1;
                        offsety = 0 - 1;
                }
                else if(i >= 180 && i < 270)
                {
                        offsetx = 1;
                        offsety = 1;
                }
                else if(i >= 270 && i < 360)
                {
                        offsetx = 0 - 1;
                        offsety = 1;
                }
                glVertex2f(centX + cos(rad)*pLength + offsetx,
                                centY + sin(rad)*pHeight+ offsety);
        }
        glEnd();
}

/*
	void drawBush(int x, int y, int fieldx, int fieldy, int color[])
	Author(s): Jonathan McKee

	Parameters
		int x - the x corrdinate
		int y - the y coordinate
		int fieldx - the width of the field/map
		int fieldy - the hieght of the field/map
		int color[] -  the array of colors for the trunk
	Return Value
		none

	This function draws a bush on the OpenGL display at the x, y coordinate passed in
*/
void gameFunctions::drawBush(int x, int y, int fieldx, int fieldy, int color[])
{
        //Increment fieldy
        fieldy++;

        //Get window Dimensions
        int winX = glutGet(GLUT_WINDOW_WIDTH);
        int winY = glutGet(GLUT_WINDOW_HEIGHT);

        //Adjust for different window dimensions
        float xint = (float)winX/(float)fieldx;
        float yint = (float)winY/(float)fieldy;

        //Get dimensions of rocks in relation to window
        float pLength = 1*xint/3;
        float pHeight = 1*yint/4;

        //Get offset of bullets from edge
        float xOff = 2*xint/6;
        float yOff = 2*yint/6;

        //Declare center coordinates for rocks
        int centX;
        int centY;

        x--;
        y--;
        if (y < 0)
                y++;
        
        //Get center of rocks
        centX = xint*x + xOff + (pLength/2);
        centY = yint*y + yOff - (pHeight/2);

        glColor3ub(color[0], color[1], color[2]);
        
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2f((centX), centY);
        glVertex2f((centX+(pLength/3)), centY+(pHeight*1.5));
        glEnd();
        glBegin(GL_LINES);
        glVertex2f((centX), centY);
        glVertex2f((centX), centY+(pHeight*2));
        glEnd();
        glBegin(GL_LINES);
        glVertex2f((centX), centY);
        glVertex2f((centX-(pLength/3)), centY+(pHeight*1.5));
        glEnd();
        glBegin(GL_LINES);
        glVertex2f((centX), centY);
        glVertex2f((centX-(pLength/1.5)), centY+(pHeight));
        glEnd();
        glBegin(GL_LINES);
        glVertex2f((centX), centY);
        glVertex2f((centX+(pLength/1.5)), centY+(pHeight));
        glEnd();
        
}

void gameFunctions::gameOverScreen(std::vector<tank> tankList)
{
    float winX = glutGet(GLUT_WINDOW_WIDTH);
    float winY = glutGet(GLUT_WINDOW_HEIGHT);

    float color[] = {1.0f, 1.0f, 1.0f};
    char str[127];

    sprintf( str, "Game Over.\n");

    std::cout << "Printing Game Over Screen\n";

    glColor3fv(color);
    glBegin(GL_POLYGON);
    glVertex2f(winX/3, winY/3);
    glVertex2f((2*winX/3), winY/3);
    glVertex2f((2*winX/3), (2*winY/3));
    glVertex2f(winX/3, (2*winY/3));
    glEnd();

    color[0] = 0.0f;
    color[1] = 0.0f;
    color[2] = 0.0f;

    glColor3fv(color);
    glBegin(GL_POLYGON);
    glVertex2f(winX/3 + 3, winY/3 + 3);
    glVertex2f((2*winX/3) - 3, winY/3 + 3);
    glVertex2f((2*winX/3) - 3, (2*winY/3) - 3);
    glVertex2f(winX/3 + 3, (2*winY/3) - 3);
    glEnd();


    color[0] = 1.0f;
    color[1] = 1.0f;
    color[2] = 1.0f;

    glColor3fv(color);
    glRasterPos2i((5.25*winX/12), (7*winY/12)); 
  
    for(int i = 0; i < 127; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
        if(str[i] == '\n')
            break;
    }    
  
    sprintf( str, "Player Tank Name:\n");
    glColor3fv(color);
    glRasterPos2i(((winX/3) + 30), (6.5*winY/12)); 

    for(int i = 0; i < 127; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
        if(str[i] == '\n')
            break;
    }    

    sprintf( str, "       Kills:\n");
    glColor3fv(color);
    glRasterPos2i(((7*winX/12)), (6.5*winY/12)); 

    for(int i = 0; i < 127; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
        if(str[i] == '\n')
            break;
    }    

    int count = 1;
    for(std::vector<tank>::iterator it = tankList.begin(); it != tankList.end(); ++it)
    {
        int colorI[] = {0, 0, 0};
        std::string temp;
        temp = ap->agetTankName(count - 1) + ':';
        ap->agetColors(colorI[0], colorI[1], colorI[2], *it);
        glColor3ub(colorI[0], colorI[1], colorI[2]);
        glRasterPos2i((winX/3 + 45), ((6.5*winY/12) - 15*count));

        for(unsigned int i = 0; i < temp.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, temp[i]);
           
        glColor3ub(colorI[0], colorI[1], colorI[2]);
        glRasterPos2i(((7*winX/12) + 45), ((6.5*winY/12) - 15*count));
        temp = std::to_string(ap->agetKill(*it));

        for(unsigned int i = 0; i < temp.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, temp[i]);

        count++;
    }

    sprintf( str, "Press Esc to exit.\n");
    glColor3fv(color);
    glRasterPos2i(((5.5*winX/12)), (1.1*winY/3)); 

    for(int i = 0; i < 127; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
        if(str[i] == '\n')
            break;
    }    


}

