#include "../../libraries/src/catch.hpp"
#include "../../api.h"
#include <fstream>

extern api *bossMan;

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

//class map;            //forward class declaration

/******************************************************************************
*  Testing creating a map object (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    map map - An instance of a Maps object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the creation of a map object
*
********************************************************************************/
TEST_CASE("Testing creating map")
{

//Test the creation of an empty map object
  SECTION("Create a blank Map");
  {
    map map;
    REQUIRE(sizeof(map) > 0);
  }
}

/******************************************************************************
*  Testing reading map dimensions Map object (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    map map - An instance of a Maps object to be used for testing
*    int x, int y - used to store the dimensions for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test checks the set and get fuctions for the dimensions of the map
*
********************************************************************************/

TEST_CASE("Testing the map dimensions")
{
  SECTION("Testing 20 x 10. Expected result: setting true, Y = 10, X = 20")
  {
    CHECK(bossMan->areadMap() == 0);
    CHECK(bossMan->agetFieldY() == 10);
    CHECK(bossMan->agetFieldX() == 20);
  }
}

/******************************************************************************
*  Testing reading and setting VALID map game modes (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    map map - An instance of a Maps object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the reading and accepting of map modes
*
********************************************************************************/

TEST_CASE(" Testing Valid Game Modes ")
{
  //testing the word: tanks
  SECTION("Testing tanks.  Expected: true, tanks")
  {
    CHECK((bossMan->asetGameMode("tanks")) == true);
    CHECK(bossMan->agetGameMode() == "tanks");
  }
  //testing the word: planes
  SECTION("Testing planes. Expected: true, planes")
  {
    CHECK((bossMan->asetGameMode("planes")) == true);
    CHECK(bossMan->agetGameMode() == "planes");
  }
  //testing the word: boats
  SECTION("Testing boats. Expected: true, boats")
  {
    CHECK((bossMan->asetGameMode("boats")) == true);
    CHECK(bossMan->agetGameMode()=="boats");
  }
  //testing the word: TANKS
  SECTION("Testing TANKS. Expected: true, tanks")
  {
    CHECK(bossMan->asetGameMode("TANKS")==true);
    CHECK(bossMan->agetGameMode()=="tanks");
  }
  //testing the word: PLANES
  SECTION("Testing PLANES. Expected: true, planes")
  {
    CHECK(bossMan->asetGameMode("PLANES")==true);
    CHECK(bossMan->agetGameMode()=="planes");
  }
  //testing the word: BOATS
  SECTION("Testing BOATS. Expected: true, boats")
  {
    CHECK(bossMan->asetGameMode("BOATS")==true);
    CHECK(bossMan->agetGameMode()=="boats");
  }
  //testing the word: Tanks
  SECTION("Testing Tanks. Expected: true, tanks")
  {
    CHECK(bossMan->asetGameMode("Tanks")==true);
    CHECK(bossMan->agetGameMode()=="tanks");
  }
  //testing the word: Planes
  SECTION("Testing Planes. Expected: true, planes")
  {
    CHECK(bossMan->asetGameMode("Planes")==true);
    CHECK(bossMan->agetGameMode()=="planes");
  }
  //testing the word: Boats
  SECTION("Testing Boats. Expected: true, boats")
  {
    CHECK(bossMan->asetGameMode("Boats")==true);
    CHECK(bossMan->agetGameMode()=="boats");
  }
}

/******************************************************************************
*  Testing INVALID map modes (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    map map - An instance of a Maps object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the reading and rejecting of Map object.  The
*  expected result for all tests will be False, with default map mode of tanks.
*  We will only check the mapmode on the first section, as the rest of the tests
*  should all default back to tanks as well.
*
********************************************************************************/

TEST_CASE("Testing invalid map modes")
{
  //reset gamemode variable
  CHECK(bossMan->asetGameMode("tanks")== true);
  CHECK(bossMan->agetGameMode()=="tanks");
  //Testing the mapmode cars
  SECTION("Testing cars. Expected: setting false, actual tanks")
  {
    CHECK(bossMan->asetGameMode("cars")==false);
  }
  //Testing the mapmode zepplins
  SECTION("Testing zepplins. Expected: setting false. ")
  {
    CHECK(bossMan->asetGameMode("zepplins")==false);
  }
  //Testing the mapmode tankboats
  SECTION("Testing tankboats. Expected: setting false. ")
  {
    CHECK(bossMan->asetGameMode("tankboats")==false);
  }
  //Testing the mapmode airplanes
  SECTION("Testing airplanes. Expected: setting false. ")
  {
    CHECK(bossMan->asetGameMode("airplanes")==false);
  }

}

/******************************************************************************
*  Testing reading the map file (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    map map - An instance of a Maps object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks reading in the map setting and then setting turns to
*  a default value of 0.  We then check the copy constructor making sure that the
*  data is loaded and copied successfully.
*
********************************************************************************/

TEST_CASE("Testing map reading")
{
  //Checking the reading of a map file
  SECTION("Testing default.map by filename. Expected: size (20,10), mode = tanks, turn = 0 ")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->agetFieldX() == 20);
      CHECK(bossMan->agetFieldY() == 10);
      CHECK(bossMan->agetGameMode() == "tanks");
  }
  SECTION("Testing get map")
  {
      map mapOne;
      map *mapTwo;

      CHECK(bossMan->areadMap() == 0);
      mapTwo = mapOne.getMap();
      //check if the new map pointer got the old api pointer
      CHECK(mapOne.ap == mapTwo->ap);
      CHECK(bossMan->agetFieldX() == 20);
      CHECK(bossMan->agetFieldY() == 10);
      CHECK(bossMan->agetGameMode() == "tanks");

  }
}


TEST_CASE("Testing changing tile objects")
{
  //Checking the reading of a map file
  SECTION("Testing X at 1,1 to X.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(1,1,tileObject::EMPTY) == true);
  }
  SECTION("Testing X at 1,1 to Projectile.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(1,1,tileObject::PROJECTILE) == true);
  }
  SECTION("Testing X at 1,1 to Rock.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(1,1,tileObject::ROCK) == true);
  }
  SECTION("Testing X at 1,1 to Tree.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(1,1,tileObject::TREE) == true);
  }
  SECTION("Testing X at 1,1 to water.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(1,1,tileObject::WATER) == true);
  }
  SECTION("Testing X at 1,10 to empty.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(1,10,tileObject::EMPTY) == true);
  }
  SECTION("Testing Tank back to 1,10. Expected: false")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(1,10,tileObject::TANK) == true);
  }
  SECTION("Testing Projectile at (5,5) to empty and back again. Expected: true, true, false")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(5,5,tileObject::EMPTY) == true);
      CHECK(bossMan->achangeMapObject(5,5,tileObject::PROJECTILE) == true);
  }
}

TEST_CASE("Getting map tile objects")
{
  //Checking the reading of a map file
  SECTION("Testing setting tree at 1,1 and then getting.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(1,1,tileObject::TREE) == true);
      CHECK(bossMan->agetMapObject(1,1) == tileObject::TREE);
  }
  SECTION("Testing setting rock at 1,1 and then getting.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(1,1,tileObject::ROCK) == true);
      CHECK(bossMan->agetMapObject(1,1) == tileObject::ROCK);
  }
  SECTION("Testing setting water at 1,1 and then getting.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->achangeMapObject(1,1,tileObject::WATER) == true);
      CHECK(bossMan->agetMapObject(1,1) == tileObject::WATER);
  }
  SECTION("Testing getting empty at 1,2.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->agetMapObject(1,2) == tileObject::EMPTY );
  }
  SECTION("Testing getting tank at 1,10.  Expected: true")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->agetMapObject(1,1) == tileObject::TANK );
  }
  SECTION("Testing getting unknown at 7,5.  Expected: true")
  {
      CHECK(bossMan->areadMap("../testing/test.map") == 0);
      CHECK(bossMan->agetMapObject(5,7) == tileObject::EMPTY );
  }
}

/******************************************************************************
*  Testing reading the map file with additional symbols (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    map map - An instance of a Maps object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks reading in the map setting and then setting turns to
*  a default value of 0.  We then check the copy constructor making sure that the
*  data is loaded and copied successfully.
*
********************************************************************************/

TEST_CASE("Testing map reading with additional symbols")
{
  //Checking the reading of a map file
  SECTION("Testing test.map by filename with (T R P W ). Expected: size (20,10), mode = tanks, turn = 0 ")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->agetFieldX() == 20);
      CHECK(bossMan->agetFieldY() == 10);
      CHECK(bossMan->agetGameMode() == "tanks");
  }
}

/******************************************************************************
*  Testing displaying the map file (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    map map - An instance of a Maps object to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks that the display function does not cause an error.  
*   Output must be manually checked for correctness
*
********************************************************************************/

TEST_CASE("Displaying map")
{
  //Checking the reading of a map file
  SECTION("Testing displaying default.map")
  {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->adisplayAscii() == true);
  }
}
