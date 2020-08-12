#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>

//Enum for available tank actions
enum ActionCommand{DO_NOTHING, M_UP, M_RIGHT, M_DOWN, M_LEFT, BACKUP, FIRE, T_UP, T_RIGHT, T_DOWN, T_LEFT};

const std::string ActionCommand_Name[] =
{
  "Do Nothing", "Move Up", "Move Right", "Move Down", "Move Left", "Back Up", "Fire Cannon", "Turn Up", "Turn Right", "Turn Down", "Turn Left"
};

#endif
