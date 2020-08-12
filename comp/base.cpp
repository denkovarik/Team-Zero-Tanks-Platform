#include "base.h"


/*************************************************************************************************
*
*                           Available API Options
*
*
*************************************************************************************************/

/***************************
*
* Available Map options
*
***************************/

/*Builds a map for the current player and returns it*/
//int** apgetMap(int id);                       

/*Returns the map width*/
//int apgetMapX(int id);        

/*Returns the map height*/
//int apgetMapY(int id);        


/**************************
*
* Move validator
*
**************************/
/*Can check if the tank move is valid*/
//bool apcheckMove(int x, int y, int id);       

/**************************
*
* Tank Functions
*
**************************/
/* Returns the position of the current player*/
//bool apgetPos(int &x, int &y, int id);        

/*Returns the current X position*/
//int apgetTankX(int id);                       

/*Returns the current Y position*/
//int apgetTankY(int id);                       

/*Returns the tanks current health*/
//int apgetHealth(int id);                      

/*Returns the tanks current kill count*/
//int apgetKill(int id);                        

/*Returns the tanks current speed*/
//int apgetSpeed(int id);                       

/*returns the tanks current direction*/
//int apgetDirection(int id);                   

/*******************
*
* Turn Functions
*
*******************/
/*returns the current turn number*/
//int apgetTurn();          

/*returns the max turn number*/
//int apgetMaxTurns();  
