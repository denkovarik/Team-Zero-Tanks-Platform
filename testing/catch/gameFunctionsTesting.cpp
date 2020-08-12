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
#include "../../api.h"
#include <fstream>
#include <vector>

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

/******************************************************************************
*  Testing if spawnTanks() function can be called in gameFunctions.cpp and that
*  the areadMap and afindTankNumber functions return the right values
*    (This is the test case purpse)
*
*  Author(s): Dennis Kovarik
*  Parameters:  (These are parameters the test uses in all sections)
*    none
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks that the spawnTanks() function can be called and the 
*  the afindTankNumber, and areadMap return the correct values.
*
********************************************************************************/
TEST_CASE("Testing functions in gameFunctions file")
{
   SECTION("Test calling the spawnTanks() function")
   {
      CHECK(bossMan->afindTankNumber(1) == -1);
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->aspawnTanks() == true);      
   }
}

/******************************************************************************
*  Testing if Api class function agameTurn can be called and returns the 
*  correct values.
*    (This is the test case purpse)
*
*  Author(s): Dennis Kovarik
*  Parameters:  (These are parameters the test uses in all sections)
*    none
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks that the agameTurn() function can be called and returns
*  the correct values.
*
********************************************************************************/
TEST_CASE("Testing function agameTurn()")
{
   SECTION("Test checking gameloop")
   {
      //CHECK(bossMan->areadMap() == 0);
      //CHECK(bossMan->aspawnTanks() == true);
      //CHECK(bossMan->agameTurn() == true);
   }
}

/******************************************************************************
*  Testing if Api class function adisplayAscii can be called and returns the 
*  correct values.
*    (This is the test case purpse)
*
*  Author(s): Dennis Kovarik
*  Parameters:  (These are parameters the test uses in all sections)
*    none
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks that the adisplayAscii() function can be called and 
*  returns the correct values.
*
********************************************************************************/
TEST_CASE("Testing function adisplayAscii()")
{
   SECTION("Test calling adisplayAscii")
   {
      CHECK(bossMan->areadMap() == 0);
      CHECK(bossMan->aspawnTanks() == true);
      CHECK(bossMan->adisplayAscii() == true);
   }

}

