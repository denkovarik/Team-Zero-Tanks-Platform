/*
 *	classTank.h
 *	Author: Sam Backes, Adeshkumar
 *	Reviewer: Gwyn Kardelis, Adesh Kumar
 *	Last Date Modified: 10/4/18
 *
 *	This is the header file for the tank class. It contains the tank class functions and data
 */
#ifndef _CLASSTANK_H_
#define _CLASSTANK_H_
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
class api;

class tank
{
   public:
     //Constructors
     tank();					//Tank Constructor
     tank(int x, int y);			//Tank Constructor with starting xy
#ifndef CATCH
   protected:
#endif     
     //Tank Color
     bool setColors(int r, int g, int b);	//Set the colors of the tank
     bool getColors(int &r, int &g, int &b);	//Returns the colors of the tank
     
     //Tank Movement
     bool setPos(int x, int y);			//Manually set the position of the tank
     bool getPos(int &x, int &y);		//Return the current position of the tank
     bool setX(int x);				//Manually set the x position of the tank
     bool setY(int y);				//Manually set the y position of the tank
     int getX();				//Return the current x position of the tank
     int getY();    				//Return the current y positoin of the tank

     bool moveUp(int y = 1);			//Moves the tank up (default 1)
     bool moveRight(int x = 1);			//Moves the tank right (default 1)
     bool moveDown(int y = 1);			//Moves the tank down (default 1)
     bool moveLeft(int x = 1);			//Moves the tank left (default 1)

     //Set and get stats
     bool setDirection(int newDir);		//Manually set the direction of the tank
     int getDirection();			//Return the current direction of the tank

     bool setSpeed(int newSpeed);		//Manually set the speed of the tank
     int getSpeed();				//Return the current speed of the tank
     
     bool addKill(int kill = 1);			//Adds kills to the tank's stats (default 1)
     bool setKill(int kill);			//Manually set the number of tank kills
     int getKill();				//Returns the current number of kills
     
     bool addHit(int hit = 1);			//Adds hit to the tank's stats (default 1)
     bool setHit(int hit);			//Manually set the number of tank hits
     int getHit();				//Returns the current number of hits
     
     bool takeDamage(int dmg = 1);			//Gives the tank damage (negative health, default 1)
     bool setHealth(int hp);			//Manually set the health
     int getHealth();				//Returns the current health

     int getPlayerId();				//Returns the player's random ID number

     int getMiss();				// Returns the misses	for Player
     bool addMiss(int miss=1);			// Increments the misses



   private:
     std::string name;				//Name string for tank
     int red, green, blue;			//Color of the tank
     int tankX, tankY;				//XY position
     int direction = 0;				//Which way is the tank facing. 0 = North, 3 = West
     int speed = 1;				//How many spaces does the tank move in a turn
     int kills = 0;					//How many objects the tank has killed
     int health = 10;				//How many hits can this tank take
     int playerId;
     int hits = 0;		
     int miss =0;

     friend class api;

};
#endif
