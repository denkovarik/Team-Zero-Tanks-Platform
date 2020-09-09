# README

CSC340 - Software Engineering Large Team Project

## Introduction
This project was created during the course CSC 340 Introduction to Software Engineering at the South Dakota School of Mines and Technology. This project is a platform that supports multiple tanks playing against each other on. Developers can design tanks to compete on this platform. 

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
If on Windows using linux subshell, make sure you have Xming running. You also my need type to following command into the shell to get the display to work.
* export DISPLAY=:0.0

### Run Platform with Default Parameters
* Run the Platform with Default Parameters
  * ./battletanks


## Creditsbatt
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
