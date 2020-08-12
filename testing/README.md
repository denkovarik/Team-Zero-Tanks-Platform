Description of the testing directory.
-Jonathan McKee 11 Sep 2018

testing/

This folder contains sample map files with pre-determined results.
default.map is a 10x12 tanks map with two players.
NotAMap.map is not a map file.

runTests.sh   -  Executes all of the bash level testing scripts
vExitCodes.sh -  Checks for error codes returned from main
vMake.sh      -  Tests the make file to ensure it compiles
vProg.sh      -  Tests basic functionality of beginning functions


testing/catch/

catch.hpp           -  Catch header file for the catch testing framework
gameTesting.cpp     - Tests the classGame.h/.cpp functionality
startTanksCatch.cpp - Our guard file for the catch header.  This allows us to make without recompiling the catch.hpp everytime
startTanksCatch.o   - Precompiled object file of the startTankCatch.cpp
tankTesting.cpp     - Tests tje classTank.h/.cpp functionality

