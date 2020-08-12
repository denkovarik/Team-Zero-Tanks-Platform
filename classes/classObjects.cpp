/*
 *	classObject.cpp
 *  Author: Jonathan McKee
 * 	Templated from classTank by: Jonathan McKee
 * 	Reviewer:
 * 	Last Date Modified: 10/13/18
 *
 *	This is the file that contains the class functions for the object class.
*/

#include "classObjects.h"
#include "../api.h"

/*
 * 	tankObject(int x, int y, int newType, int turn)
 * 	Author: Jonathan McKee
 * 	Reviewer: 
 * 	Parameters
 * 		int x - x spawn position
 * 		int y - y spawn position
 *    int newType - the type of object being made
 *    int turn - the turn the oject was created on
 * 	Return Value
 * 		N/A
 *
 * 	Constuctor for the object class with a premade position
*/
tankObject::tankObject(int x, int y, int newType, int turn)
{
	//Check if object will be spawned outside the map and cap it if so
	if(x > 20)
		x = 20;
	if(y > 10)
		y = 10;
	if(x < 1)
	       x = 1;
	if(y < 1)
	       y = 1;	

	objectX = x;
	objectY = y;

  type = newType;
  createTurn = turn;
  //defaults based on type:
  switch (newType)
  {
          case 1:  //tree
                  health = 4;
                  red = 150, green = 113, blue = 23;//Brown
                  sRed = 0, sGreen = 230, sBlue = 77;//Green
              break;
          case 5:  //rock
                  health = 10;
                  red = 169, green = 169, blue = 169;//Grey
              break;
          case 7:  //bush
                  health = 4;
                  red = 164, green = 198, blue = 57;//Green
              break;
          default: //do nothing
              break;
  }

}

/*
 *      setColors(int r, int g, int b)
 *      Author: Jonathan McKee
 *      Reviewer:
 *      Parameters
 *              int r - the red color value
 *              int g - the green color value
 *		int b - the blue color value
 *      Return Value
 *              False - Incorrect color
 *		True  - Correct color and saved
 *
 *      Manually set the RGB values of the object
*/
bool tankObject::setObjColors(int r, int g, int b)
{
	//Values too big
	if(r > 255 || g > 255 || b > 255)
		return false;
	if(r < 0 || g < 0 || b < 0)
		return false;

	red = r;
	green = g;
	blue = b;
	return true;
}

/*
 *      setSecondaryColors(int r, int g, int b)
 *      Author: Jonathan McKee
 *      Reviewer:
 *      Parameters
 *              int r - the red color value
 *              int g - the green color value
 *		          int b - the blue color value
 *      Return Value
 *              False - Incorrect color
 *		  True  - Correct color and saved
 *
 *      Manually set the RGB values of the object
*/
bool tankObject::setObjSecondaryColors(int r, int g, int b)
{
	//Values too big
	if(r > 255 || g > 255 || b > 255)
		return false;
	if(r < 0 || g < 0 || b < 0)
		return false;

	sRed = r;
	sGreen = g;
	sBlue = b;
	return true;
}

/*
 *      getColors(int &r, int &g, int &b)
 *      Author: Jonathan McKee
 *      Reviewer: 
 *      Parameters
 *              int r - the red color value
 *		int g - the green color value
 * 		int b - the blue color value
 *      Return Value
 *              True - Colors found and saved
 *
 *      Saves the RGB values of the object to the passed in variables
*/
bool tankObject::getObjColors(int &r, int &g, int &b)
{
	r = red;
	g = green;
	b = blue;
	return true;
}

/*
 *      getSecondaryColors(int &r, int &g, int &b)
 *      Author: Jonathan McKee
 *      Reviewer: 
 *      Parameters
 *              int r - the red color value
 *		          int g - the green color value
 * 		          int b - the blue color value
 *      Return Value
 *              True - Colors found and saved
 *
 *      Saves the RGB values of the object to the passed in variables
*/

bool tankObject::getObjSecondaryColors(int &r, int &g, int &b)
{
	r = sRed;
	g = sGreen;
	b = sBlue;
	return true;
}

/*
 *      setPos(int x, int y)
 *      Author: Jonathan McKee
 *      Reviewer: 
 *      Parameters
 *              int x - x position
 *              int y - y position
 *      Return Value
 *              False - Incorrect position
 *		True  - Correct position and saved
 *
 *      Sets the x and y positions of the object manually
*/
bool tankObject::setObjPos(int x, int y)
{
	//Check if object will spawn outside of map and cap it if so
	if(x <= 0 || y <= 0)
		return false;
	if(x > 20 || y > 10)
		return false;

	objectX = x;
	objectY = y;
	return true;
}

/*
        getPos(int &x, int &y)
        Author: Jonathan McKee
        Reviewer: 
        Parameters
                x - the x position
		y - the y position
        Return Value
                True - Values found and saved

        Saves the object's xy position to the passed in variables
*/
bool tankObject::getObjPos(int &x, int &y)
{
	x = objectX;
	y = objectY;
	return true;
}

/*
        takeDamage(int dmg)
        Author: Jonathan McKee
        Reviewer: 
        Parameters
                int dmg - the amount of damage the object takes (default 1)
        Return Value
                False - Incorrect value (zero or negative dmg)
		True  - Correct value and stat saved

        Subtracts damage from the object's current health
*/
bool tankObject::takeDamage(int dmg)
{
	if(dmg <= 0)
		return false;

	health -= dmg;
	return true;
}

/*
        setHealth(int hp)
        Author: Jonathan McKee
        Reviewer: 
        Parameters
                int hp - the amount of health you wish the object to have
        Return Value
                False - Incorrect value
		True  - Correct value and saved
        Manually sets the amount of health a object has
*/
bool tankObject::setHealth(int hp)
{
	if(hp < 0)
		return false;

	health = hp;
	return true;
}

/*
        getHealth()
        Author: Jonathan McKee
        Reviewer: 
        Parameters
                N/A
        Return Value
                int health - the current amount of health a object has

        Just returns the current amount of health a object has
*/
int tankObject::getHealth()
{
	return health;
}

/*
        setObjType()
        Author: Jonathan McKee
        Reviewer: 
        Parameters
                N/A
        Return Value
                int health - the current amount of health a object has

        Just returns the current amount of health a object has
*/
bool tankObject::setObjType(int newType)
{
  if (newType != 1 || newType != 5 || newType != 7)
    return false;
  type = newType;
  return true;
}
