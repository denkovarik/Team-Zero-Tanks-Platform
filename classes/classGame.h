/*
 * classGame.cpp
 * Author: JD Pessoa
 * Author: JD Pessoa, Adeshkumar Naik
 * Reviewer: Gwyn Kardelis, Adesh Kumar
 * Last Date Modified: 10/2/18
 */   


#ifndef _CLASSGAME_H_
#define _CLASSGAME_H_

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

class api;
class gameSetting
{
public:
  gameSetting();		//game setting Constructor
  ~gameSetting();		//game setting Destructor
#ifndef CATCH
protected:
#endif
                  
  bool setSize(int new_cols, int new_rows);		//Sets the Size of the Map  
  bool getSize(int &height, int &width);		//Returns the Size of the Map



  bool setGameMode(std::string new_game_mode);		//Sets the Game Mode to the parameter passed 
  std::string getGameMode();				//Returns the Game Mode 

  void turnPassed();					//Increments the Turns 
  int getTurn();					 //Returns the Turns
  void resetTurn();					//Resets the Turns to 0

  int getIdleTime();					     //Returns the IdleTime
  bool setIdleTime(int idle);				//Sets the IdleTime

  int getUIMode();					//Returns the UI Game Mode

  bool setUIMode(int new_ui);				//Sets the UI Game Mode

  bool checkMaxTurns(int turn);				//Returns the Max turns
  bool setMaxTurns(int turns);				//Sets the Max Turns
  int getMaxTurns();					//checks the Max Turns

  std::string getMapName();				//returns the Map Name
  bool setMapName(std::string name);			//sets the Map Name

  bool setSetting(api *ap);				//api settting function
private:
  api *ap;
  int rows = 10; //How tall the board is
  int cols = 20; //How wide the board is
  std::string game_mode =
    "tanks"; //The current game mode initialized to tanks by default
  std::string mapName = "default.map";
  int turns = 0; //Number of turn passed
  int maxGameTurns = 200;
  int idle_time = 200; //Wait time
  int ui = 0; //0 for ASCII, 1 for OpenGL

  friend class api;
};
#endif
