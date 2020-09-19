# Team Zero Tanks Platform

![alt text](https://github.com/denkovarik/Team-Zero-Tanks-Platform/blob/master/images/teamZeroPlatformCapture.PNG)

## Introduction
This project was created during the course CSC 340 Introduction to Software Engineering at the South Dakota School of Mines and Technology. This project is a platform that supports multiple tanks playing against each other on. Developers can design tanks to compete on this platform. 

A simple API has been developed, but there is not much documentation out on it yet. The tanks that currently run on the platform either act randomly or just very simply. 

## Setup
Note that this projects were developed and tested in Ubuntu on the command line.

### Required Software
* git
* g++
   * Linux C++ Compiler 
* freeglut3-dev
   * OpenGL - Development libraries
* SOIL
   * Image processing package
* make
   * Linux compiler script manager
* gdb
   * Linux debugger

### Optional Software for Windows Users
* Xming
   * X-server package for displaying platform on windows
   
### Clone the repository
* Clone with SSH
  * git clone git@github.com:denkovarik/Team-Zero-Tanks-Platform.git
* Clone with HTTPS
  * git clone https://github.com/denkovarik/Team-Zero-Tanks-Platform.git
    
### Build the Project
* make

If on Windows using linux subshell, make sure you have Xming running. You also my need type to following command into the shell to get the display to work.
* export DISPLAY=:0.0

## Testing
All commands are to be executed from the project root directory.
* Compile All Tests
  * make test
* Compile and Run All Tests
  * ./testing/runTests.sh
* Compile and Run Catch Tests for Game Class
  * ./testing/vCatch.sh
* Compile and Run Make Tests
  * ./testing/vMake.sh
* Compile and Run ASCII Starting Verification Script
  * ./testing/vProgASCII.sh
* Compile and Run Tests of OpenGL
  * ./testing/vProgOpenGL.sh
* Compile and Run Coverage
  * ./testing/runCoverage.sh

## Usage

* ./battletanks
* ./battletanks -map <mapName.map>
* ./battletanks -idle <int value for idle between each turn>
* ./battletanks -maxturn <maximum number of turns>
* ./battletanks -ui "ascii"
* ./battletanks -map <mapName.map> -idle <int value for idle between each turn>

### Run Platform with Default Parameters
Run the Platform with Default Parameters
* ./battletanks
  
### Specified Game Map
There are only 2 maps out so far for this platform. They are named "default.map" and "defaultObject.map". This parameter is specified with the '-map' keyword followed by the name of the map.
* ./battletanks -map default.map
* ./battletanks -map defaultObject.map

### Specify Game Speed
This parameter specifies idle for each turn, and it is passed in using the '-idle' keyword followed by an integer value for the idle time. For this parameter, lower values for this paramter will cause the game to run faster.
* ./battletanks -idle 10

### Specify the Maximum Number of Turns
This parameter specifies the maximum number of turns the game runs for. This parameter is specified with the '-maxturn' keyword followed by an integer value for the maximum number of turns. 
* ./battletanks -maxturn 10

### Run Platform in Ascii
This parameter specifies the UI for the platform. This parameter is set by using the keyword '-ui' followed by the UI method, which can either be "opengl" or "ascii". The default is "opengl". The "ascii" version was used for development and testing purposes. 
* Run in OpenGl mode
  * ./battletanks -ui "opengl"
* Run in Ascii mode
  * ./battletanks -ui "ascii"

## Credits
* Wesley Adams (Team Lead)
* Jonathan Mckee
* Sam Backes
* Levi Butt
* William Doering
* Gwyneth Kardelis
* JD Pessoa
* Aidan Anderson
* AdeshKumar Naik
* Dennis Kovarik
