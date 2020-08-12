/*
 *	classTank.cpp
 * 	Author: Sam Backes, Adeshkumar
 * 	Reviewer: Gwyn Kardelis, Adesh Kumar
 * 	Last Date Modified: 10/5/18
 *
 *	This is the file that contains the class functions for the tank class.
*/

#include "classTank.h"
#include "../api.h"

/*
 * 	tank()
 * 	Author: Sam Backes
 * 	Reviewer: Gwyn Kardelis, Adesh Kumar
 * 	Parameters
 * 		N/A
 * 	Return Value
 * 		N/A
 *
 * 	Constuctor for the tank class
 */
tank::tank()
{
	//Generate random number between 1 and 9999
	playerId = rand() % 9999 + 1;
  printf("Player Id: %d\n",playerId);
}


/*
 * 	tank(int x, int y)
 * 	Author: Sam Backes
 * 	Reviewer: Gwyn Kardelis, Adesh Kumar
 * 	Parameters
 * 		int x - x spawn position
 * 		int y - y spawn position
 * 	Return Value
 * 		N/A
 *
 * 	Constuctor for the tank class with a premade position
*/
tank::tank(int x, int y)
{
	//Check if tank will be spawned outside the map and cap it if so
	if(x > 20)
		x = 20;
	if(y > 10)
		y = 10;
	if(x < 1)
	       x = 1;
	if(y < 1)
	       y = 1;	

	tankX = x;
	tankY = y;

        //Initialize random seed
        srand (time(NULL));

        //Generate random number between 1 and 9999
        playerId = rand() % 9999 + 1;
}

/*
 *      setColors(int r, int g, int b)
 *      Author: Sam Backes
 *      Reviewer: Gwyn Kardelis, Adesh Kumar
 *      Parameters
 *              int r - the red color value
 *              int g - the green color value
 *		int b - the blue color value
 *      Return Value
 *              False - Incorrect color
 *		True  - Correct color and saved
 *
 *      Manually set the RGB values of the tank
*/
bool tank::setColors(int r, int g, int b)
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
 *      getColors(int &r, int &g, int &b)
 *      Author: Sam Backes
 *      Reviewer: Gwyn Kardelis, Adesh Kumar
 *      Parameters
 *              int r - the red color value
 *		int g - the green color value
 * 		int b - the blue color value
 *      Return Value
 *              True - Colors found and saved
 *
 *      Saves the RGB values of the tank to the passed in variables
*/
bool tank::getColors(int &r, int &g, int &b)
{
	r = red;
	g = green;
	b = blue;
	return true;
}

/*
 *      setPos(int x, int y)
 *      Author: Sam Backes
 *      Reviewer: Gwyn Kardelis, Adesh Kumar
 *      Parameters
 *              int x - x position
 *              int y - y position
 *      Return Value
 *              False - Incorrect position
 *		True  - Correct position and saved
 *
 *      Sets the x and y positions of the tank manually
*/
bool tank::setPos(int x, int y)
{
	//Check if tank will spawn outside of map and cap it if so
	if(x <= 0 || y <= 0)
		return false;
	if(x > 20 || y > 10)
		return false;

	tankX = x;
	tankY = y;
	return true;
}

/*
        getPos(int &x, int &y)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                x - the x position
		y - the y position
        Return Value
                True - Values found and saved

        Saves the tank's xy position to the passed in variables
*/
bool tank::getPos(int &x, int &y)
{
	x = tankX;
	y = tankY;
	return true;
}

/*
        setX(int x)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                x - the x position
        Return Value
                False - Incorrect position
		True  - Correct position and saved

        Manually set the x position of a tank
*/
bool tank::setX(int x)
{
	//Stop if too small or too big for map
	if(x <= 0)
		return false;
	if(x > 20)
		return false;

	tankX = x;
	return true;
}

/*
        setY(int y)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                y - the y position
        Return Value
                False - Incorrect position
		True  - Correct position and saved

        Manually set the y position
*/
bool tank::setY(int y)
{
	//Stop if too small or too big for map
	if(y <= 0)
		return false;
	if(y > 10)
		return false;

	tankY = y;
	return true;
}

/*
        getX()
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                N/A
        Return Value
                x - the x position of the tank

        Just returns the current x position of the tank
*/
int tank::getX()
{
	return tankX;
}

/*
        getY()
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                N/A
        Return Value
                y - the y position of the tank 

        Just returns the current y position of the tank
*/
int tank::getY()
{
	return tankY;
}

/*
        moveUp(int y)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                int y - the number of spaces to move up (default 1)
        Return Value
                False - Incorrect value or would move off map
		True  - Correct value and tank has moved

        Moves the tank up by adding y to the vertical position
*/
bool tank::moveUp(int y)
{
	//Stop if incorrect input
	if(y <= 0)
		return false;
	//Stop if command would move off map
	if((y + tankY) > 10)
		return false;
	//Move the tank
	tankY += y;

	//Change the direction to face up
	direction = 0;
	return true;
}

/*
        moveRight(int x)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                int x - the number of spaces to move right (default 1)
        Return Value
                False - Incorrect value or would move tank off map
		True  - Correct value and tank has been moved

        Moves the tank right by adding x to the horizontal position
*/
bool tank::moveRight(int x)
{
	//Stop if incorrect input
	if(x <= 0)
		return false;
	//Stop if command would move off map
	if((x + tankX) > 20)
		return false;
	//Move the tank
	tankX += x;

	//Change the direction to face right
	direction = 1;
	return true;
}

/*
        moveDown(int y)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                y - the number of spaces to move down (default 1)
        Return Value
                False - Incorrect value or would move tank off map
		True  - Correct value and tank has been moved

        Moves the tank down by subtracting y from the vertical position
*/
bool tank::moveDown(int y)
{
	//Stop if incorrect input
	if(y <= 0)
		return false;
	//Stop if command would move off map
	if((tankY - y) < 1)
	       return false;	
	//Move the tank
	tankY -= y;
	//Change the direction to face down
	direction = 2;
	return true;
}

/*
        moveLeft(int x)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                x - the number of spaces to move left (default 1)
        Return Value
                False - Incorrect value or would move tank off map
		True  - Correct value and tank has been moved

        Moves the tank left by subtracting x from the horizontal position
*/
bool tank::moveLeft(int x)
{
	//Stop if incorrect input
	if(x <= 0)
		return false;
	//Stop if command would move off map
	if((tankX - x) < 1)
		return false;
	//Move the tank
	tankX -= x;

	//Change the direction to face left
	direction = 3;
	return true;
}

/*
        setDirection(int newDir)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                int newDir - the direction to change to
        Return Value
                False - Incorrect value
		True  - Correct value and saved

        Manually set the direction of the tank
*/
bool tank::setDirection(int newDir)
{
	if(newDir > 3 || newDir < 0)
		return false;

	direction = newDir;
	return true;
}

/*
        getDirection()
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                N/A
        Return Value
                Direction - the current direction of the tank

        Just returns the current direction of the tank
*/
int tank::getDirection()
{
	return direction;
}

/*
        setSpeed(int newSpeed)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                int newSpeed - the new speed (no kidding!)
        Return Value
                False - Incorrect value
		True  - Correct value and saved

        Manually set the speed of the tank
*/
bool tank::setSpeed(int newSpeed)
{
	//If negative, set to default
	if(newSpeed < 0)
	{
		speed = 1;
		return false;
	}
	//If too big, set to default
	if(newSpeed >= 10)
	{
		speed = 1;
		return false;
	}
	speed = newSpeed;
	return true;
}

/*
        getSpeed()
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                N/A
        Return Value
                int speed - the current speed of the tank

        Just returns the current speed of the tank
*/
int tank::getSpeed()
{
	return speed;
}

/*
        addKill(int kill)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                int kill - the number of kills to add (default 1)
        Return Value
                False - Incorrect value
		True  - Correct value and saved

        Adds 'kill' to the current kill counter of the tank
*/
bool tank::addKill(int kill)
{
	//Check if we're actually adding
	if(kill <= 0)
		return false;

	kills += kill;
	return true;
}

/*
        setKill(int kill)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                int kill - the number of kills a tank has
        Return Value
                False - Incorrect value
		True  - Correct value and saved

        Manually set the number of kills a tank has
*/
bool tank::setKill(int kill)
{
	if(kill < 0)
		return false;

	kills = kill;
	return true;
}

/*
        getKill()
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                N/A
        Return Value
                int kills - the number of kills a tank currently has

        Just returns the number of kills a tank currently has
*/
int tank::getKill()
{
	return kills;
}
/*
        addHit(int hit)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                int hit - the number of hits to add (default 1)
        Return Value
                False - Incorrect value
		True  - Correct value and saved

        Adds 'hit' to the current hit counter of the tank
*/
bool tank::addHit(int hit)
{
	//Check if we're actually adding
	if(hit <= 0)
		return false;

	hits += hit;
	return true;
}

/*
        setHit(int hit)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                int hit - the number of hits a tank has
        Return Value
                False - Incorrect value
		True  - Correct value and saved

        Manually set the number of hits a tank has
*/
bool tank::setHit(int hit)
{
	if(hit < 0)
		return false;

	hits = hit;
	return true;
}
/*
        getHit()
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                N/A
        Return Value
                int kills - the number of kills a tank currently has

        Just returns the number of kills a tank currently has
*/
int tank::getHit()
{
	return hits;
}

/*
        takeDamage(int dmg)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                int dmg - the amount of damage the tank takes (default 1)
        Return Value
                False - Incorrect value (zero or negative dmg)
		True  - Correct value and stat saved

        Subtracts damage from the tank's current health
*/
bool tank::takeDamage(int dmg)
{
	if(dmg <= 0)
		return false;

	health -= dmg;
	return true;
}

/*
        setHealth(int hp)
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                int hp - the amount of health you wish the tank to have
        Return Value
                False - Incorrect value
		True  - Correct value and saved
        Manually sets the amount of health a tank has
*/
bool tank::setHealth(int hp)
{
	if(hp < 0)
		return false;

	health = hp;
	return true;
}

/*
        getHealth()
        Author: Sam Backes
        Reviewer: Gwyn Kardelis, Adesh Kumar
        Parameters
                N/A
        Return Value
                int health - the current amount of health a tank has

        Just returns the current amount of health a tank has
*/
int tank::getHealth()
{
	return health;
}

/*
 * 	getPlayerId()
 * 	Author: Sam Backes
 * 	Reviewer: Gwyn Kardelis, Adesh Kumar
 * 	Parameters
 * 		N/A
 * 	Return Value
 * 		int playerId - the tank's random id number
 *
 * 	Just returns the tank's player ID number
 */
int tank::getPlayerId()
{
	return playerId;
}

/**
 *	bool tank::IncrementMisses(int miss)
 *	Author: Adeshkumar Naik
 *	Reviewer: Gwyn Kardelis, Adeshkumar
 *	Parameter
 *		int miss
 *	Return Value
 *		True - Misses is incremented 
 *
 *	Increments one by default unless more misses are passed through parameter
 **/
bool tank::addMiss(int miss)
{
		if(miss<=0)
		return false;

		this->miss +=miss;
		return true;
}
/*
 *	int tank::getMiss()
 *	Author:	Adeshkumar Naik
 *	Reviewer: Gwyn Kardelis, Adeshkumar
 *	Parameter
 *		N/A
 *	Return Value
 *		int Misses - total no of misses for a tank
 *	
 *
 * */

int tank::getMiss()
{
		return miss;
}

