/*
  classProjectile.cpp
  Authors: Aidan Anderson, Dennis Kovarik, Adeshkumar Naik
  Last Date Modified: 10/2/2018
*/



#include "classProjectile.h"



/*
  projectile( int vel, int startX, int startY, int dir )
  Authors: Adian Anderson, Dennis Kovarik, Adeshkumar Naik
  Parameters
    int vel - An integer representing the velocity of the projectile.
        For right now, this var won't be used.
    int startX - An integer representing the starting x position of
               the projectile
    int startY - An integer represenging the starting y position of
           the projectile.
  Return Value
    none

  This is the constructor for the projectile class. It takes in 4
  parameters and sets the velocity, starting x and y position, and the
  direction of the projectile.
*/
projectile::projectile(int vel, int startX, int startY, int dir, int ownerProj)
{
  //For now just set the velocity equal to 1
  velocity = 1;

  //Set the starting x position
  xPos = startX;

  //Set the starting y position
  yPos = startY;

  //Set the projectile's direction;
  direction = dir % 4;

  //sets the owner of the projectile
  owner = ownerProj;

  return;
}




/*
  ~projectile()
  Authors: Adian Anderson, Dennis Kovarik
  Parameters
    none.
  Return Value
    none

  This is the destructor for the projectile class. It destroys an instance
  of the projectile object.
*/
projectile::~projectile()
{
  return;

}




/*
  getVelocity()
  Authors: Adian Anderson, Dennis Kovarik
  Parameters
    none.
  Return Value
    Returns an integer representing the projectile's velocity.

  This is a member function of the projectile class that just returns
  an integer representing the projectile's veleocity.
*/
int projectile::getVelocity()
{
  return velocity;
}




/*
  getPosition( int &x, int &y )
  Authors: Adian Anderson, Dennis Kovarik
  Parameters
    int &x - An integer representing the projectile's current x
       postion to be returned by reference.
    int &y - An integer representing the projectile's current y
      position to be returned by reference.
  Return Value
    Returns true if able to successfull return the projectile's x
    and y positions by reference.

  This is a member function of the projectile class that just returns
  two integers, by reference, representing the projectile's current
  position. If successful, the function itself will return true..
*/
bool projectile::getPosition(int &x, int &y)
{
  x = xPos;
  y = yPos;

  return true;
}




/*
  getVelocity()
  Authors: Adian Anderson, Dennis Kovarik
  Parameters
    none.
  Return Value
    Returns an integer representing the projectile's direction.

  This is a member function of the projectile class that just returns
  an integer representing the projectile's direction.
*/
int projectile::getDirection()
{
  return direction;

}




/*
  moveProjectile()
  Authors: Adian Anderson, Dennis Kovarik
  Parameters
    none.
  Return Value
    Returns an boolean value indicating whether or not the function
    was able to successfully increment the projectile's position

  This is a member function of the projectile class that is used to update
  the projectile's position. It will always increment the pojectile's
  position by one. It will then return true if it was successfully able to
  update the projectile's position. Note that this function does no error
  checking for the projectile moving off of the map.
*/
bool projectile::moveProjectile()
{
  //Move projectile based on its current direction
  //Moving North
  if(direction == 0)
  {
    yPos += velocity;
  }
  //Moving East
  else if(direction == 1)
  {
    xPos += velocity;
  }
  //Moving South
  else if(direction == 2)
  {
    yPos -= velocity;
  }
  //Moving west
  else if(direction == 3)
  {
    xPos -= velocity;
  }

  return true;
}
/*  int projectile::getOwner()
*  Authors: Adeshkumar Naik
* Parameters: None
*  Return
*   int owner
*  This function returns the owner of the projectile. That is it returns the playerID that fired
* the projectile
*
* */
int projectile::getOwner()
{
        return owner;
}
