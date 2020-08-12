/****************************************************************************
*       gameTesting.cpp
*       Author(s): Jon McKee
*       Last Date Modified: 9/22/2018 by Jon McKee
*
*       This file contains the catch testing cases and sections for the
*       gameSettibgs class. Upon completion will return the number of failed
*       test cases and failed number of sections.
*
*****************************************************************************/
#include "../../libraries/src/catch.hpp"
#include "../../classes/classGame.h"
#include "../../api.h"
#include <fstream>

/*   Template for Test cases:

     TEST_CASE("Test for output")
     {
     SECTION("Test section")
     {
       StringClass tester("Hello");
       REQUIRE(testing.reverse() == "olleH");
     }
     SECTION("Next Test section")
     {
       StringClass tester("olleh");
       REQUIRE(testing.reverse() == "Hello");
     }
     }
 */
extern api *bossMan;

class gameSetting;            //forward class declaration
typedef gameSetting settings; //use settings instead of gameSetting

/******************************************************************************
*  Testing creating a gameSetting object (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    settings game - An instance of a gameSettings object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the creation of a gameSetting object 
*                                                   
********************************************************************************/
TEST_CASE("Testing creating game settings")
{
  //Test the creation of an empty game object
  SECTION("Create a blank gameSetting");
  {
    settings game;
    REQUIRE(sizeof(game)>0);
  }
}
/******************************************************************************
*  Testing game object defaults (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    settings game - An instance of a gameSettings object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the default values of the game object 
*                                                   
********************************************************************************/
TEST_CASE("Testing default values for game object")
{
  //Test the creation of an empty game object
  SECTION("Tesing Rows and Cols.  Expected: True, X = 20, y = 10");
  {
    int x = 0, y = 0;
    settings game;
    REQUIRE(game.getSize(x, y) == true);
    REQUIRE(x == 20);
    REQUIRE(y == 10);
  }
  SECTION("Testing game_mode.  Expected: 'tanks'")
  {
    settings game;
    REQUIRE(game.getGameMode() == "tanks");
  }
  SECTION("Testing turns.  Expected: Turns = 0"){
    settings game;
    REQUIRE(game.getTurn() == 0);
  }
  SECTION("Testing idle_time.  Expected: Idle_time = 200"){
    settings game;
    REQUIRE(game.getIdleTime() == 200);
  }
  SECTION("Testing ui.  Expected: ui = 0")
    {
    settings game;
    REQUIRE(game.getUIMode() == 0);
    }
}

/******************************************************************************
*  Testing reading map dimensions gameSetting object (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    settings game - An instance of a gameSettings object to be used for testing
*    int x, int y - used to store the dimensions for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test checks the set and get fuctions for the dimensions of the map 
*                                                   
********************************************************************************/

TEST_CASE("Testing get and set dimensions sane limits")
{
  //checking trying to set a map size of 0x0
  SECTION("Testing 0 x 0. Expected result: setting failed, getting true, size not 0x0")
  {
    int x, y;
    settings game;
    CHECK(game.setSize(0, 0) == false);
    CHECK(game.getSize(x, y) == true);
    CHECK(x != 0);
    CHECK(y != 0);
  }
  //checking setting 1 invalid parameter
  SECTION("Testing -1 x 10. Expected result: setting failed, getting true, x != -1, y=10")
  {
    int x, y;
    settings game;
    CHECK(game.setSize(-1, 10) == false);
    CHECK(game.getSize(x, y) == true);
    CHECK(x != -1);
    CHECK(y == 10);
  }
  //checking setting invalid parameter in other position
  SECTION("Testing 10 x -1. Expected result: setting failed, getting true, x = 10, y != -1")
  {
    int x, y;
    settings game;
    CHECK(game.setSize(10, -1) == false);
    CHECK(game.getSize(x, y) == true);
    CHECK(x == 10);
    CHECK(y != -1);
  }
  //checking too small of a map
  SECTION("Testing 1 x 1. Expected result: setting failed, getting true, size != (1,1) ")
  {
    int x, y;
    settings game;
    CHECK(game.setSize(1, 1) == false);
    CHECK(game.getSize(x, y) == true);
    CHECK(x != 1);
    CHECK(y != 1);
  }
  //checking valid square map
  SECTION("Testing 10 x 10. Expected result: setting true, getting true, size (10,10) ")
  {
    int x, y;
    settings game;
    CHECK(game.setSize(10, 10) == true);
    CHECK(game.getSize(x, y) == true);
    CHECK(x == 10);
    CHECK(x == 10);
  }
  //checking default map size
  SECTION("Testing 20 x 10. Expected result: setting true, getting true, size (20,10) ")
  {
    int x, y;
    settings game;
    CHECK(game.setSize(20, 10) == true);
    CHECK(game.getSize(x, y) == true);
    CHECK(x == 20);
    CHECK(y == 10);
  }
  //checking map Y value too large
  SECTION("Testing invalid size Y, 20 x 11. Expected result: setting false, getting true, y != 11 ")
  {
    int x, y;
    settings game;
    CHECK(game.setSize(20, 11) == false);
    CHECK(game.getSize(x, y) == true);
    CHECK(y != 11);
  }
  //checking map X value too large
  SECTION("Testing invalid size X, 10 x 21. Expected result: setting false, getting true, x != 21 ")
  {
    int x, y;
    settings game;
    CHECK(game.setSize(21, 10) == false);
    CHECK(game.getSize(x, y) == true);
    CHECK(x != 21);
  }
}

/******************************************************************************
*  Testing reading and setting VALID game modes (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    settings game - An instance of a gameSettings object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the reading and accepting of game modes
*                                                   
********************************************************************************/

TEST_CASE(" Testing Game Settings Valid Game Modes ")
{
  //testing the word: tanks
  SECTION("Testing tanks.  Expected: true, tanks")
  {
    settings game;
    CHECK(game.setGameMode("tanks")==true);
    CHECK(game.getGameMode() == "tanks");
  }
  //testing the word: planes
  SECTION("Testing planes. Expected: true, planes")
  {
    settings game;
    CHECK(game.setGameMode("planes")==true);
    CHECK(game.getGameMode() == "planes");
  }
  //testing the word: boats
  SECTION("Testing boats. Expected: true, boats")
  {
    settings game;
    CHECK(game.setGameMode("boats")==true);
    CHECK(game.getGameMode()=="boats");
  }
  //testing the word: TANKS
  SECTION("Testing TANKS. Expected: true, tanks")
  {
    settings game;
    CHECK(game.setGameMode("TANKS")==true);
    CHECK(game.getGameMode()=="tanks");
  }
  //testing the word: PLANES
  SECTION("Testing PLANES. Expected: true, planes")
  {
    settings game;
    CHECK(game.setGameMode("PLANES")==true);
    CHECK(game.getGameMode()=="planes");
  }
  //testing the word: BOATS
  SECTION("Testing BOATS. Expected: true, boats")
  {
    settings game;
    CHECK(game.setGameMode("BOATS")==true);
    CHECK(game.getGameMode()=="boats");
  }
  //testing the word: Tanks
  SECTION("Testing Tanks. Expected: true, tanks")
  {
    settings game;
    CHECK(game.setGameMode("Tanks")==true);
    CHECK(game.getGameMode()=="tanks");
  }
  //testing the word: Planes
  SECTION("Testing Planes. Expected: true, planes")
  {
    settings game;
    CHECK(game.setGameMode("Planes")==true);
    CHECK(game.getGameMode()=="planes");
  }
  //testing the word: Boats
  SECTION("Testing Boats. Expected: true, boats")
  {
    settings game;
    CHECK(game.setGameMode("Boats")==true);
    CHECK(game.getGameMode()=="boats");
  }
  //testing the word: tAnKs
  SECTION("Testing tAnKs. Expected: true, tanks")
  {
    settings game;
    CHECK(game.setGameMode("tAnKs")==true);
    CHECK(game.getGameMode()=="tanks");
  }
  //testing the word: pLaNes
  SECTION("Testing pLaNes. Expected: true, planes") 
  {
    settings game;
    CHECK(game.setGameMode("pLaNes")==true);
    CHECK(game.getGameMode()=="planes");
  }
  //testing the word: bOaTs
  SECTION("Testing bOaTs. Expected: true, boats") 
  {
    settings game;
    CHECK(game.setGameMode("bOaTs")==true);
    CHECK(game.getGameMode()=="boats");
  }
}

/******************************************************************************
*  Testing INVALID game modes (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    settings game - An instance of a gameSettings object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the reading and rejecting of gameSetting object.  The
*  expected result for all tests will be False, with default game mode of tanks.
*  We will only check the gamemode on the first section, as the rest of the tests
*  should all default back to tanks as well.
*                                                   
********************************************************************************/

TEST_CASE("Testing invalid game modes (gameSettings)")
{
  //Testing the gamemode cars
  SECTION("Testing cars. Expected: setting false, actual tanks") 
  {
    settings game;
    CHECK(game.setGameMode("cars")==false);
    CHECK(game.getGameMode()=="tanks");
  }
  //Testing the gamemode zepplins
  SECTION("Testing zepplins. Expected: setting false. ") 
  {
    settings game;
    CHECK(game.setGameMode("zepplins")==false);
  }
  //Testing the gamemode tankboats
  SECTION("Testing tankboats. Expected: setting false. ") 
  {
    settings game;
    CHECK(game.setGameMode("tankboats")==false);
  }
  //Testing the gamemode airplanes
  SECTION("Testing airplanes. Expected: setting false. ") 
  {
    settings game;
    CHECK(game.setGameMode("airplanes")==false);
  }

}

/******************************************************************************
*  Testing gameSetting turn counter (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    settings game - An instance of a gameSettings object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the turn functions of the gameSetting object 
*                                                   
********************************************************************************/

TEST_CASE("Testing turn number")
{
  //check we start on turn 0.
  SECTION("Starting turn number. Expected: 0")
  {
    settings game;
    CHECK(game.getTurn()==0);
  }
  //check adding 4 turns (1 turn 4 times)
  SECTION("Adding 4 turns(individually). Expected: 4")
  {
    settings game;
    game.turnPassed();
    game.turnPassed();
    game.turnPassed();
    game.turnPassed();
    CHECK(game.getTurn()==4);
  }
  //check resetting turns back to 0 
  SECTION("Resetting turns. Expected: 0")
  {
    settings game;
    game.turnPassed();
    game.turnPassed();
    game.turnPassed();
    game.turnPassed();
    game.resetTurn();
    CHECK(game.getTurn()==0);
  }
  //check resetting turns back to 0 from 4 and adding 2
  SECTION("Resetting turns, then adding 2 turns.  Expected: 2 ")
  {
    settings game;
    game.turnPassed();
    game.turnPassed();
    game.turnPassed();
    game.turnPassed();
    game.resetTurn();
    game.turnPassed();
    game.turnPassed();
    CHECK(game.getTurn()==2);
  }
}


/******************************************************************************
*  Testing idle functions (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    settings game - An instance of a gameSettings object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the default value, setting the value, and getting the
*  value.
*                                                   
********************************************************************************/
TEST_CASE("Testing idle functions")
{
  SECTION("Testing default idle. Expected: 200")
  {
      settings game;
      CHECK(game.getIdleTime() == 200);
  }
  SECTION("Testing changing idle. Expected: true, 600")
  {
      settings game;
      CHECK(game.setIdleTime(600) == true);
      CHECK(game.getIdleTime() == 600);
  }
}

/******************************************************************************
*  Testing UI setting functions (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    settings game - An instance of a gameSettings object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the default value, setting the value, and getting the
*  value.
*                                                   
********************************************************************************/
TEST_CASE("Testing ui setting functions")
{
  SECTION("Testing default UI. Expected: 0")
  {
      settings game;
      CHECK(game.getUIMode() == 0);
  }
  SECTION("Testing changing UI to valid number. Expected: true, 1")
  {
      settings game;
      CHECK(game.setUIMode(1) == true);
      CHECK(game.getUIMode() == 1);
  }
  SECTION("Testing changing UI to invalid number. Expected: false, 0")
  {
      settings game;
      CHECK(game.setUIMode(5) == false);
      CHECK(game.getUIMode() == 0);
  }
}

/******************************************************************************
*  Testing Max turn functions (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    settings game - An instance of a gameSettings object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  These tests check the max turn related functions
*                                                   
********************************************************************************/
TEST_CASE("Testing max turn functions")
{
  SECTION("Testing getting max turn. Expected: 1")
  {
      bossMan->asetMaxTurns(1);
      CHECK(bossMan->agetMaxTurns() == 1);
      CHECK(bossMan->apgetMaxTurns() == 1);
  }
  SECTION("Testing max turn. Expected: false, true")
  {
      bossMan->aresetTurn();
      CHECK(bossMan->acheckMaxTurn() == false);
      bossMan->aturnPassed();
      CHECK(bossMan->acheckMaxTurn() == true);
  }
}
