/*
 *	classGame.cpp
 *   	Author: JD Pessoa, AdeshKumar Naik
 *    	Reviewer: Levi Butt, Adesh Kumar
 *      Last Date Modified: 10/4/18
*/

#include "classGame.h"
#include "../api.h"

/*
 *        gamesetting()
 *        Author: JD Pessoa
 *        Reviewer: Levi Butt
 *        Parameters
 *             N/A
 *        Return Value
 *             N/A
 *               
 *      Constuctor for the game setting class
 *           **/

gameSetting::gameSetting()
{

}
/* 	~gamesetting()
 *  	 Author: JD Pessoa
 *  	  Reviewer: Levi Butt
 *  	  Parameters
 *          N/A
 *       Return Value
 *  	              N/A
 *  	     
 *     Destructor for the game setting class
 *  	      
 * */

gameSetting::~gameSetting()
{
}

/*
 *        bool gameSetting::setSize(int new_cols, int new_rows)
 *        Author: JD Pessoa
 *        Reviewer: Levi Butt
 *        Parameters
 *  	          int new_cols - no of cols for the game
 *                int new_rows - no of rows for the game
 *        Return Value
 *                True    - rows and cols are set to the parameters passed
 *          
 *       Sets the value of rows and cols with the parameters passed in
 *          
 * */

bool gameSetting::setSize(int new_cols, int new_rows)
{
  //Check if rows is a valid value, assign if true
  if(new_rows <= 10 && new_rows >= 2)
    rows = new_rows;
  //Check if rows is a valid value, assign if true
  if(new_cols <= 20 && new_cols >= 2)
    cols = new_cols;
  //Check if both values were assigned return false otherwise
  if(cols == new_cols && rows == new_rows)
    return true;
  return false;
}

/*
 *  *     bool gameSetting::getSize(int new_cols, int new_rows)
 *        Author: JD Pessoa
 *         Reviewer: Levi Butt
 *          Parameters
 *              int width  -  width of the Map/Field
 *               int height -  height of the Map/Field
 *             Return Value
 *                 True    - if the return variables are set to rows and cols
 *          
 * Sets the return variables to the sizes saved
 *                  
 * **/

bool gameSetting::getSize(int &width, int &height)
{
  //Set the return variables to the sizes saved, test if sueccessful
  height = rows;
  width = cols;
  if(rows == height && cols == width)
  {
    return true;
  }
  return false;
}

/*    bool gameSetting::setGameMode ( string new_game_mode )
 *      Author: JD Pessoa
 *       Reviewer: Levi Butt
 *       Parameters
 *  	      string new_game_mode - The game mode which is a string
 *       Return Value
 *            True    - if the game mode passed in is valid and set to the current game_mode
 *                 
 *       Sets the game mode to the one passed in
 *               
 * */

bool gameSetting::setGameMode(std::string new_game_mode)
{
  //Copy gamemode to temp and case insensitize it
  transform(new_game_mode.begin(), new_game_mode.end(), new_game_mode.begin(), ::tolower);
  //See if it is a valid string and set to game_mode if yes
  if((new_game_mode == "tanks") || (new_game_mode == "planes") || (new_game_mode == "boats"))
  {
    game_mode = new_game_mode;
    return true;
  }
  //Return false otherwise
  return false;
}


/*    bool gameSetting::getGameMode()
 *    Author: JD Pessoa
 *     Reviewer: Levi Butt
 *    Parameters
 *         N/A    
 *    Return Value
 *      returns the game_mode
 * */

std::string gameSetting::getGameMode()
{
  //Return the game mode variable;
  return game_mode;
}

/**Turns Functions**/
/*    void gameSetting::turnPassed()
 *     Author: JD Pessoa
 *     Reviewer: Levi Butt
 *      Parameters
 *           N/A
 *       Return 
 *          returns the no of turns
 *             **/

void gameSetting::turnPassed()
{
  turns++;
}
/*    void gameSetting::turnPassed()
 *          Author: JD Pessoa
 *           Reviewer: Levi Butt
 *             Parameters
 *                N/A
 *               Return 
 *                 returns the no of turns
 **/

int gameSetting::getTurn()
{
  //Return turn counter
  return turns;
}
/*    void gameSetting::resetTurn()
 *         Author: JD Pessoa
 *          Reviewer: Levi Butt
 *           Parameters
 *               N/A
 *             Return
 *                sets the turns to 0
 **/

void gameSetting::resetTurn()
{
  //Reset turns to 0
  turns = 0;
}

//**Idle Time Fuctions**//
//**Idle Time Fuctions**//
/* 	int gameSetting::getIdleTime()
 *      Author: JD Pessoa
  *	Reviewer: Levi Butt
   *	Parameters
    *	   N/A
     *	Return 
      *	   idle_time 
       * */

int gameSetting::getIdleTime()
{
  //Return idle time
  return idle_time;
}
/*      bool gameSetting::setIdleTime(int idle)
 *      Author: JD Pessoa
 *      Reviewer: Levi Butt
 *      Parameters
 *         int idle - idle time
 *      Return 
 *        True if idle_time of the game is set to the idle time passed
 *             
 * */

bool gameSetting::setIdleTime(int idle)
{
  //Set idle time and check if sucessful
  idle_time = idle;
  if(idle_time == idle)
    return true;
  return false;
}

//**Other**//
/*	int gameSetting::getUIMode()
 *	Author: JD Pessoa
 *	Reviewer: Levi Butt
 *	Parameters
 *	   N/A
 *	Return
 *	  int - Ui game mode
 *	Returns the UI game Mode
 *	
 **/

int gameSetting::getUIMode()
{
  //Return value of ui
  return ui;
}
/*      bool gameSetting::setUIMode(int ui_new)
 *       	Author:	JD Pessoa
 *        	Reviewer: Levi Butt
 *         	Parameters
 *          	   int ui_new - the gameMode(ASCII/OpenGl)
 *          	Returns
 *           	   True - if the Ui game mode is valid
 *         
 *    	   Sets the UI Mode to a valid mode passed in
 *         
 * */

bool gameSetting::setUIMode(int ui_new)
{
  //Checks if ui is a valid value, then set it
  if(ui_new >= 2)
  {
    return false;
  }
  ui = ui_new;
  return true;
}
/**
 *	bool gameSetting::checkMaxTurns(int turn)
 *	Author: Adeshkumar Naik
 *	Reviewer: Levi Butt
 *	Parameters
 *	  int turn - the current number of turns
 *	Return
 *	   True - if turn has hit maxturn limit
 *
 *	   Checks if the turn counter passed in has hit the max turn limit
 *
 *
 * */

bool gameSetting::checkMaxTurns(int turn)
{
/**	
 *	string gameSetting::getMapName()
 *	Author: Adeshkumar Naik
 *	Reviewer: Levi Butt
 *	Parameters:
 *	   N/A
 *	Return 
 *	   String map_name - the map name
 *
 *	   Returns map name
 *
 *
 * */
	//checks if turn has hit the maxGame Turn Limit
  if(turn >= maxGameTurns)
    return true;
  return false;
}
/**
 *	bool gameSetting::setMaxTurns(int turns)
 *	Author: Adeshkumar Naik
 *	Reviewer: Levi Butt
 *	Parameters
 *	   int turns - the number of turns that max turns will be set to
 *
 *	Return
 *	   True - if maxGameTurns is set to the turn parameter passed in
 *
 *	   Sets the maxGameTurns with the parameter turns passed in
 *
 *
 * */

bool gameSetting::setMaxTurns(int turns)
{
  maxGameTurns = turns;
  return true;
}

/**Set and Get Functions**/
/**
 *  *      bool gameSetting::getMaxTurns()
 *   *      Author: Adeshkumar Naik
 *    *      Reviewr: Levi Butt
 *     *      Parameters
 *      *         N/A
 *       *      Returns
 *        *         int maxGameTurns
 *         *
 *          * */
int gameSetting::getMaxTurns()
{
	//sets the maxGameTurns to turns parameter passed in
  return maxGameTurns;
}
/**
 *	bool gameSetting::setMapName(string mapName)
 *	Author: Adeshkumar Naik
 *	Reviewer: Levi Butt
 *	Parameters:
 *	   string mapName- the mapName to set map_name
 *	Return 
 *	  True - if map_name is set to mapName
 *
 *	  transforms the parameter to lower case and then sets 
 *	  map_name to mapName
*/
bool gameSetting::setMapName(std::string name)
{
  this->mapName = name;
  return true;
}
/**	
 *  	string gameSetting::getMapName()
 *   	Author: Adeshkumar Naik
 *    	Reviewer: Levi Butt
 *     	Parameters:
 *      	   N/A
 *      Return 
 *      	String map_name - the map name
 *        
 *             Returns map name
 *           
 *            
 * */

std::string gameSetting::getMapName()
{
  return mapName;
}
/*
 *	bool gameSetting::setSetting(api *ap)
 *	Author:	Jon Mckee
 *	Reviwer: Levi Butt
 *	Parameters:
 *		api pointer
 *	Return 
 *		True - api function is equalized to ap
 *
 * 	Setsetting is called
 * */
  bool gameSetting::setSetting(api *ap)
{
        this->ap = ap;
        return ap->setSetting(this);
}
