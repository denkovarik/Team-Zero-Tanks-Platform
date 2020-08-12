#ifndef _CLASSPROJECTILE_H_
#define _CLASSPROJECTILE_H_
/*
  classProjectile.h
  Authors: Aidan Anderson, Dennis Kovarik, Adeshkumar Naik
  Last Date Modified: 10/2/2018

  This is the header file that defines a projectile
*/

//forward declaration
class api;
class projectile
{
public:
  //Constriuctor and Destructor
  projectile(int vel, int startX, int startY, int dir, int ownerProj);
  ~projectile();

#ifndef CATCH
protected:
#endif
  //Returns the velocity of the projectile
  int getVelocity();

  //Returns the current x and y position of projectile
  bool getPosition(int &x, int &y);

  //Returns the projectile's direction
  int getDirection();

  //Returns the owner
  int getOwner();

  //Increments the projectile's current position
  bool moveProjectile();

private:
  int velocity;   //The Projectile's velocity
  int xPos = 0;   //The Projectile's x position
  int yPos = 0;   //The Projectile's y position
  int direction;    //The Projectile's direction
  int owner;    //owner of the projectile fired
  //0 == up
  //1 == right
  //2 == down
  //3 == left
  friend class api;
};


#endif
