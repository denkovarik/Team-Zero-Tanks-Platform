/*
 *	classObjects.h
 *	Author: Jonathan McKee
 *	Templated from classTank written by Sam Backes
 *  Code Reviewers: 
 *	Last Date Modified: 10/13/18
 *
 *	This is the header file for the object class. It contains the object class information
 */
#ifndef _CLASSOBJECT_H_
#define _CLASSOBJECT_H_
#include <string>
#include <stdio.h>
#include <stdlib.h>
class api;

class tankObject
{
   public:
     //Constructors
     tankObject(int x, int y, int newType, int turn);			//object Constructor with starting xy
#ifndef CATCH
   protected:
#endif     
     //Object Colors
     bool setObjColors(int r, int g, int b);	//Set the colors of the tank
     bool getObjColors(int &r, int &g, int &b);	//Returns the colors of the tank
     
     //Object Secondary Colors
     bool setObjSecondaryColors(int r, int g, int b);	//Set the colors of the tank
     bool getObjSecondaryColors(int &r, int &g, int &b);	//Returns the colors of the tank
     
     //Modify Object type
     bool setObjType(int newType); //change object type
     int getObjType(){return type;} //returns object type


     //Object Location
     bool setObjPos(int x, int y);			//Manually set the position of the tank
     bool getObjPos(int &x, int &y);		//Return the current position of the tank

     //The objects health modifiers
     bool takeDamage(int dmg = 1);			//Damages the object (default 1)
     bool setHealth(int hp);			      //Manually set the health
     int getHealth();				            //Returns the current health


   private:
     int red, green, blue;	 //main color of object
     int sRed, sGreen, sBlue; //set secondary colors
     int objectX, objectY;	 //XY position
     int health = 10;				 //default 10 for rock, 5 for tree
     int type = 0;           //0 None, 1 - Tree, 5 - Rock, 7 - Bush
     int createTurn = 0;     //The turn the object was made

     friend class api;

};
#endif
