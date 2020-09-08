/****************************************************************************
*       tankTesting.cpp
*       Author(s): Jon McKee
*       Correction(s): Sam Backes
*       Last Date Modified: 9/22/2018 by Jon McKee
*
*       This file contains the catch testing cases and sections for the
*       tank class.  Upon completion will return the number of failed
*       test cases and failed number of sections.
*
*****************************************************************************/

#include "../../libraries/src/catch.hpp"
#include "../../api.h"
extern api *bossMan;

/*   Template for Test cases:

     TEST_CASE("Test for output")
     {
         StringClass tester("Hello");
         REQUIRE(testing.reverse() == "olleH");
         StringClass tester("olleh");
         REQUIRE(testing.reverse() == "Hello");
     }
*/

class tank;

/******************************************************************************
*  Tank creation testing with no coordinates (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses)
*    tank testTank - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the creation of a tank with no coordinates input. 
*                                                   
********************************************************************************/

TEST_CASE("Create a tank with no inputs")
{
   tank testTank;
   REQUIRE(sizeof(testTank)> 0);   
}

/******************************************************************************
*  Tank creation testing with coordinates (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the creation of a tank with coordinates. 
*                                                   
********************************************************************************/

TEST_CASE("Create a tank with starting inputs")
{
   //checking lower left grid square from map (1,1) from default.map
   SECTION( "Checking spawning tank at coords (1,1) ")
   {
      tank testTank(1, 1);
      REQUIRE(sizeof(testTank)> 0);
   }
   //checking upper right grid square from map (20,10) from default.map
   SECTION( "Checking spawning tank at coords (20, 10) ")
   {
      tank testTank(20,10);
      REQUIRE(sizeof(testTank)> 0);
   }
   //For the initial development we decided on a fixed map size
   //If we add dynamic map sizes this test will be good to check
   //proper tank spawning spots.
   SECTION("Checking out of range X Value, too high: 21")
   {
      tank testTank2(21, 1);
      CHECK(sizeof(testTank2)> 0);
      CHECK(testTank2.getX() != 21);
      CHECK(bossMan->agetX( testTank2 ) == 20);
      
   }
   SECTION( "Checking negative X Value: -10" )
   {
      tank testTank3(-10, 1);
      CHECK(sizeof(testTank3)> 0);
      CHECK(testTank3.getX() >= 1);
      CHECK(bossMan->agetX( testTank3 ) >= 1);
   }
   SECTION("Checking out of range Y Value, too high: 11")
   {
      tank testTank4(1, 11);
      CHECK(sizeof(testTank4)> 0);
      CHECK(testTank4.getY() != 11);
      CHECK(bossMan->agetY( testTank4 ) != 11);
   }
   SECTION(" Checking negative Y Value: - 10")
   {
      tank testTank5(1, -10);
      CHECK(sizeof(testTank5)> 0);
      CHECK(testTank5.getY() >= 1);
      CHECK(bossMan->agetY( testTank5 ) >= 1);
   }
}

/******************************************************************************
*  Tank color testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank6 - An instance of a Tank to be used for testing
*    int r, g, b - Temporary integers to store tank red, green, blue values
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the setting and getting color functions for tanks. The 
*     code looks repeated, but is necessary as the values are reset between 
*     the sections erasing results.. 
*                                                   
********************************************************************************/

TEST_CASE("Test Tank colors")
{
   tank testTank6;
   int r, g, b;
   //Check setting colors to a valid set (255, 255, 255)
   SECTION(" Checking setting Colors to 255, 255, 255 ")
   {
      REQUIRE(testTank6.setColors(255, 255, 255) == true);
      CHECK(testTank6.getColors(r, g, b) == true);
      CHECK(r == 255);
      CHECK(g == 255);
      CHECK(b == 255);
      REQUIRE(bossMan->asetColors(100, 120, 123, testTank6) == true);
      CHECK(bossMan->agetColors(r, g, b, testTank6) == true);
      CHECK(r == 100);
      CHECK(g == 120);
      CHECK(b == 123);
   }
   //Checking trying to set the red color value too high
   SECTION(" Checking red value too high (4000). Expected: false ")
   {
      testTank6.setColors(255, 255, 255);
      CHECK(testTank6.setColors(4000, 20, 20) == false);
      testTank6.getColors(r, g, b);
   }
   //Checking to ensure that no values changed with an invalid color
   SECTION(" Checking all values did not change. Expected: 255, 255, 255 ")
   {
      REQUIRE(r == 255);
      REQUIRE(g == 255);
      REQUIRE(b == 255);
   }
   //Checking trying to set the red color value too high
   SECTION(" Checking red value too high (4000). Expected: false ")
   {
      REQUIRE(testTank6.setColors(255, 255, 255) == true);
      bossMan->agetColors(r, g, b, testTank6);
      REQUIRE(r == 255);
      REQUIRE(g == 255);
      REQUIRE(b == 255);
      CHECK(bossMan->asetColors(4000, 20, 20, testTank6) == false);
      bossMan->agetColors(r, g, b, testTank6);
   }
   //Checking to ensure that no values changed with an invalid color
   SECTION(" Checking all values did not change. Expected: 255, 255, 255 ")
   {
      REQUIRE(r == 255);
      REQUIRE(g == 255);
      REQUIRE(b == 255);
   }
   //Checking trying to set the blue color value too high
   SECTION(" Checking blue value too high (4000). Expected: false ")
   {
      testTank6.setColors(255, 255, 255);
      CHECK(testTank6.setColors(20, 4000, 20) == false);
      testTank6.getColors(r, g, b);
   }//Checking to ensure that no values changed with an invalid blue input
   SECTION(" Checking all values did not change. Expected: 255, 255, 255 ")
   {
      REQUIRE(r == 255);
      REQUIRE(g == 255);
      REQUIRE(b == 255);
   }
   //Checking trying to set the blue color value too high
   SECTION(" Checking red value too high (4000). Expected: false ")
   {
      REQUIRE(testTank6.setColors(255, 255, 255) == true);
      CHECK(bossMan->asetColors(20, 4000, 20, testTank6) == false);
      bossMan->agetColors(r, g, b, testTank6);
   }
   //Checking to ensure that no values changed with an invalid color
   SECTION(" Checking all values did not change. Expected: 255, 255, 255 ")
   {
      REQUIRE(r == 255);
      REQUIRE(g == 255);
      REQUIRE(b == 255);
   }
   //Checking trying to set the green color value too high
   SECTION(" Checking green value too high (4000). Expected: false ")
   {
      REQUIRE(testTank6.setColors(255, 255, 255) == true);
      CHECK(bossMan->asetColors(20, 20, 4000, testTank6) == false);
      bossMan->agetColors(r, g, b, testTank6);
   }
   //Checking to ensure that no values changed with an invalid color
   SECTION(" Checking all values did not change. Expected: 255, 255, 255 ")
   {
      REQUIRE(r == 255);
      REQUIRE(g == 255);
      REQUIRE(b == 255);
   }
   //Checking trying to set a green color value to high
   SECTION(" Checking green value too high (4000). Expected: false ")
   {
      testTank6.setColors(255, 255, 255);
      CHECK(testTank6.setColors(20, 20, 4000) == false);
      testTank6.getColors(r, g, b);
   }//Checking to ensure that no values changed with invalid green input
   SECTION(" Checking all values did not change. Expected: 255, 255, 255 ")
   {
      REQUIRE(r == 255);
      REQUIRE(g == 255);
      REQUIRE(b == 255);
   }
   //Checking trying to set a green color value to high for api class
   SECTION(" Checking green value too high (4000). Expected: false ")
   {
      REQUIRE(testTank6.setColors(255, 255, 255) == true);
      CHECK(bossMan->asetColors(20, 20, 4000, testTank6) == false);
      bossMan->agetColors(r, g, b, testTank6);
   }//Checking to ensure that no values changed with invalid green input
   SECTION(" Checking all values did not change. Expected: 255, 255, 255 ")
   {
      REQUIRE(r == 255);
      REQUIRE(g == 255);
      REQUIRE(b == 255);
   }
   //Checking to ensure a negative red number is rejected
   SECTION(" Checking red value negative number (-20). Expected: false ")
   {
      testTank6.setColors(255, 255, 255);
      CHECK(testTank6.setColors(-20, 20, 20) == false);
      testTank6.getColors(r, g, b);
   }//Checking to ensure the colors were not modified by bad input
   SECTION(" Checking no values cahnged. Expected: 255, 255, 255 "){
      CHECK(r == 255);
      CHECK(g == 255);
      CHECK(b == 255);
   }
   //Checking to ensure api rejects negative red value
   SECTION(" Checking red value negative number (-20). Expected: false ")
   {
      REQUIRE(testTank6.setColors(255, 255, 255) == true);
      CHECK(bossMan->asetColors(-20, 20, 20, testTank6) == false);
      bossMan->agetColors(r, g, b, testTank6);
   }
   //Checking to ensure that no values changed with an invalid color
   SECTION(" Checking all values did not change. Expected: 255, 255, 255 ")
   {
      REQUIRE(r == 255);
      REQUIRE(g == 255);
      REQUIRE(b == 255);
   }
   //Checking to ensure a negative blue number is rejected
   SECTION(" Checking blue value negative number (-20). Expected: false ")
   {
      testTank6.setColors(255, 255, 255);
      CHECK(testTank6.setColors(20, -20, 20) == false);
      testTank6.getColors(r, g, b);
   }//Checking to ensure the colors were not modified by bad input
   SECTION(" Checking no values cahnged. Expected: 255, 255, 255 "){
      CHECK(r == 255);
      CHECK(g == 255);
      CHECK(b == 255);
   }
   //Checking to ensure api negative blue number is rejected
   SECTION(" Checking blue value negative number (-20). Expected: false ")
   {
      REQUIRE(testTank6.setColors(255, 255, 255) == true);
      CHECK(bossMan->asetColors(-20, 20, 20, testTank6) == false);
      bossMan->agetColors(r, g, b, testTank6);
   }
   //Checking to ensure that no values changed with an invalid color
   SECTION(" Checking all values did not change. Expected: 255, 255, 255 ")
   {
      REQUIRE(r == 255);
      REQUIRE(g == 255);
      REQUIRE(b == 255);
   }
   //Checking to ensure a negative green number is rejected
   SECTION(" Checking green value negative number (-20). Expected: false ")
   {
      testTank6.setColors(255, 255, 255);
      CHECK(testTank6.setColors(20, 20, -20) == false);
      testTank6.getColors(r, g, b);
   }//Checking to ensure the colors were not modified by bad input
   SECTION(" Checking no values cahnged. Expected: 255, 255, 255 "){
      CHECK(r == 255);
      CHECK(g == 255);
      CHECK(b == 255);
   }
   //Checking to ensure a negative green number is rejected for api
   SECTION(" Checking green value negative number (-20). Expected: false ")
   {
      REQUIRE(testTank6.setColors(255, 255, 255) == true);
      CHECK(bossMan->asetColors(20, 20, -20, testTank6) == false);
      bossMan->agetColors(r, g, b, testTank6);
   }
   //Checking to ensure the colors were not modified by bad input
   SECTION(" Checking no values cahnged. Expected: 255, 255, 255 "){
      CHECK(r == 255);
      CHECK(g == 255);
      CHECK(b == 255);
   }
   //Checking to ensure we can change all 3 numbers at once
   //including the extremes 0/255
   SECTION(" Checking a change in all 3 values(0, 1, 255). Expected: true, r = 0, g = 1, b = 255 "){
      testTank6.setColors(200, 200, 200);
      CHECK(testTank6.setColors(0, 1, 255) == true);
      REQUIRE(testTank6.getColors(r, g, b) == true);
      CHECK(r == 0);
      CHECK(g == 1);
      CHECK(b == 255);

      bossMan->asetColors(200, 200, 200, testTank6);
      CHECK(bossMan->asetColors(0, 1, 255, testTank6) == true);
      REQUIRE(bossMan->agetColors(r, g, b, testTank6) == true);
      CHECK(r == 0);
      CHECK(g == 1);
      CHECK(b == 255);
   }
}

/******************************************************************************
*  Tank upward movement testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank7 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the upward movement functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Tank Upward movement")
{
   //Check using the moveUp command to move one space with default value
   SECTION(" Moving tank up 1 position. Expected: true, Y = 3, Direction = 0 ")
   {
      tank testTank7(1, 2);
      CHECK(testTank7.moveUp() == true);
      REQUIRE(testTank7.getY() == 3);
      CHECK(testTank7.getDirection() == 0);
   }//Check moving upward by setting the Y value
   SECTION(" Setting Y value. Expected: true, Y = 4 ")
   {
      tank testTank7(1, 1);
      CHECK(testTank7.setY(4) == true);
      REQUIRE(testTank7.getY() == 4);
   }//Check moving upward by inputting a value to moveUp
   SECTION(" Moving Y up two values. Expected: true, Y = 6, Direction = 0 ")
   {
      tank testTank7(1, 4);
      CHECK(testTank7.moveUp(2) == true);
      REQUIRE(testTank7.getY() == 6);
      CHECK(testTank7.getDirection() == 0);
   }//Check moving up, to make sure we can't leave the map
   SECTION(" Checking moveUp() upward off the map. Expected: false, y = 10 ")
   {
      tank testTank7(10,10);
      CHECK(testTank7.moveUp() == false);
      CHECK(testTank7.getY() == 10);
   }//Second check moving up to make sure we can't leave the map
   SECTION(" Checking moveUp(6) off the map. Expected: false, y = 10 ")
   {
      tank testTank7(10,10);
      CHECK(testTank7.moveUp(6) == false);
      CHECK(testTank7.getY() == 10);
   }
   SECTION(" Checking moveUp(-1) off the map. Expected: false, y = 10")
   {
      tank testTank7(10,10);
      CHECK(testTank7.moveUp(-1) == false);
      CHECK(testTank7.getY() == 10);
   }
}

/******************************************************************************
*  Tank Api class upward movement interface testing 
*	(This is the test case purpse)
*
*  Author(s): Jon McKee, Dennis Kovarik
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank7 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the upward movement functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Api Tank Upward movement interface")
{
   //Check using the moveUp command to move one space with default value
   SECTION(" Moving tank up 1 position. Expected: true, Y = 3, Direction = 0 ")
   {
      //checking api class functionsi
      tank testTank8(1, 2);
      CHECK(bossMan->amoveUp(testTank8) == true);
      REQUIRE(bossMan->agetY(testTank8) == 3);
      CHECK(bossMan->agetDirection(testTank8) == 0);
   }//Check moving upward by setting the Y value
   SECTION(" Setting Y value. Expected: true, Y = 4 ")
   {
      //checking api class
      tank testTank8(1, 1);
      CHECK(bossMan->asetY(4, testTank8) == true);
      REQUIRE(bossMan->agetY(testTank8) == 4);
   }//Check moving upward by inputting a value to moveUp
   SECTION(" Moving Y up two values. Expected: true, Y = 6, Direction = 0 ")
   {
      //checking api class
      tank testTank8(1, 4);
      CHECK(bossMan->amoveUp(testTank8, 2) == true);
      REQUIRE(bossMan->agetY(testTank8) == 6);
      CHECK(bossMan->agetDirection(testTank8) == 0);
   }//Check moving up, to make sure we can't leave the map
   SECTION(" Checking moveUp() upward off the map. Expected: false, y = 10 ")
   {
      tank testTank7(10,10);
      CHECK(bossMan->amoveUp(testTank7) == false);
      CHECK(bossMan->agetY(testTank7) == 10);
   }//Second check moving up to make sure we can't leave the map
   SECTION(" Checking moveUp(6) off the map. Expected: false, y = 10 ")
   {
      tank testTank7(10,10);
      CHECK(bossMan->amoveUp(testTank7, 6) == false);
      CHECK(bossMan->agetY(testTank7) == 10);
   }
   SECTION(" Checking moveUp(-1) off the map. Expected: false, y = 10")
   {
      tank testTank7(10,10);
      CHECK(bossMan->amoveUp(testTank7, -1) == false);
      CHECK(bossMan->agetY(testTank7) == 10);
   }
}

/******************************************************************************
*  Tank right movement testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank8 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the right movement functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Tank Right movement")
{
   //Checking moveRight by 1 using the default value
   SECTION(" Checking tank movement right by 1. Expected: true, X = 2, Direction = 1 ")
   {
      tank testTank8(1, 1);
      CHECK(testTank8.moveRight() == true);
      REQUIRE(testTank8.getX() == 2);
      CHECK(testTank8.getDirection() == 1);
   }//Checking moving right by setting the X value
   SECTION(" Setting X to 4. Expected: true, X = 4 ")
   {
      tank testTank8(1, 1);
      CHECK(testTank8.setX(4) == true);
      REQUIRE(testTank8.getX() == 4);
   }//checking moveRight by 2 using an input of 2
   SECTION(" Moving X right two values. Expected: true, X = 6, Direction = 1 ")
   {
      tank testTank8(4, 1);
      CHECK(testTank8.moveRight(2) == true);
      REQUIRE(testTank8.getX() == 6);
      CHECK(testTank8.getDirection() == 1);
   }//Check moving right to make sure we don't leave the map
   SECTION(" Checking moveRight() off the map. Expected: false, X = 20 ")
   {
      tank testTank8(20,10);
      CHECK(testTank8.moveRight() == false);
      CHECK(testTank8.getX() == 20);
   }//Second check moving right to make sure we don't leave the map
   SECTION(" Checking moveRight(6) off the map. Expected: false, X = 20 ")
   {
      tank testTank8(20,10);
      CHECK(testTank8.moveRight() == false);
   SECTION(" Checking moveRight(6) off the map. Expected: false, X = 20 ")
   {
      tank testTank8(20,10);
      CHECK(testTank8.moveRight(6) == false);
      CHECK(testTank8.getX() == 20);
   }
      CHECK(testTank8.getX() == 20);
   }
   SECTION(" Checking moveRight(-1) off the map. Expected: false, X = 20 ")
   {
      tank testTank8(20,10);
      CHECK(testTank8.moveRight(-1) == false);
      CHECK(testTank8.getX() == 20);
   }
}

/******************************************************************************
*  Tank right movement testing for api class(This is the test case purpse)
*
*  Author(s): Jon McKee, Dennis Kovarik
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank8 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the right movement functions 
*                                                   
********************************************************************************/
TEST_CASE("Testing Api class Tank Right movement interface")
{
   //Checking moveRight by 1 using the default value
   SECTION(" Checking tank movement right by 1. Expected: true, X = 2, Direction = 1 ")
   {
      tank testTank8(1, 1);
      CHECK(bossMan->amoveRight(testTank8) == true);
      REQUIRE(bossMan->agetX(testTank8) == 2);
      CHECK(bossMan->agetDirection(testTank8) == 1);
   }//Checking moving right by setting the X value
   SECTION(" Setting X to 4. Expected: true, X = 4 ")
   {
      tank testTank8(1, 1);
      CHECK(bossMan->asetX(4, testTank8) == true);
      REQUIRE(bossMan->agetX(testTank8) == 4);
   }//checking moveRight by 2 using an input of 2
   SECTION(" Moving X right two values. Expected: true, X = 6, Direction = 1 ")
   {
      tank testTank8(4, 1);
      CHECK(bossMan->amoveRight(testTank8, 2) == true);
      REQUIRE(bossMan->agetX(testTank8) == 6);
      CHECK(bossMan->agetDirection(testTank8) == 1);
   }//Check moving right to make sure we don't leave the map
   SECTION(" Checking moveRight() off the map. Expected: false, X = 20 ")
   {
      tank testTank8(20,10);
      CHECK(bossMan->amoveRight(testTank8) == false);
      CHECK(bossMan->agetX(testTank8) == 20);
   }//Second check moving right to make sure we don't leave the map
   SECTION(" Checking moveRight(6) off the map. Expected: false, X = 20 ")
   {
      tank testTank8(20,10);
      CHECK(bossMan->amoveRight(testTank8) == false);
   SECTION(" Checking moveRight(6) off the map. Expected: false, X = 20 ")
   {
      tank testTank8(20,10);
      CHECK(bossMan->amoveRight(testTank8, 6) == false);
      CHECK(bossMan->agetX(testTank8) == 20);
   }
      CHECK(testTank8.getX() == 20);
   }
   SECTION(" Checking moveRight(-1) off the map. Expected: false, X = 20 ")
   {
      tank testTank8(20,10);
      CHECK(bossMan->amoveRight(testTank8, -1) == false);
      CHECK(bossMan->agetX(testTank8) == 20);
   }
}


/******************************************************************************
*  Tank down movement testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank9 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the down movement functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Tank Down movement")
{
   //check moveDown with default value 
   SECTION(" Moving down 1 space. Expected: true, Y = 7, Direction = 2 ")
   {
      tank testTank9(8, 8);
      CHECK(testTank9.moveDown() == true);
      REQUIRE(testTank9.getY() == 7);
      CHECK(testTank9.getDirection() == 2);
   }//Check moving down by setting Y coordinate
   SECTION(" Setting Y coordinate to. Expected: true, Y = 6 ")
   {
      tank testTank9(8, 8);
      CHECK(testTank9.setY(6) == true);
      REQUIRE(testTank9.getY() == 6);
   }//Check moveDown with an input of 2
   SECTION(" Moving down two spaces. Expected: true, Y = 4, Direction = 2 ")
   {
      tank testTank9(8, 6);
      CHECK(testTank9.moveDown(2) == true);
      REQUIRE(testTank9.getY() == 4);
      CHECK(testTank9.getDirection() == 2);
   }//Check moving off the map from 1,1 using default value
   SECTION(" Trying to move off the map. Expected: false ")
   {
      tank testTank9(1, 1);
      CHECK(testTank9.moveDown() == false);
      CHECK(testTank9.getY() == 1);
   }//Check moving off the map with a large input
   SECTION(" Trying to move off the map. Expected: false ")
   {
      tank testTank9(3, 3);
      CHECK(testTank9.moveDown(6) == false);
      CHECK(testTank9.getY() == 3);
   }
   SECTION(" Trying to down(-1). Expected: false, y = 3")
   {
      tank testTank9(3, 3);
      CHECK(testTank9.moveDown(-1) == false);
      CHECK(testTank9.getY() == 3);
   }
}

/******************************************************************************
*  Api Tank down movement interface testing (This is the test case purpse)
*
*  Author(s): Jon McKee, Dennis Kovarik
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank9 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the down movement functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Api class Tank Down movement interface")
{
   //check moveDown with default value 
   SECTION(" Moving down 1 space. Expected: true, Y = 7, Direction = 2 ")
   {
      tank testTank9(8, 8);
      CHECK(bossMan->amoveDown(testTank9) == true);
      REQUIRE(bossMan->agetY(testTank9) == 7);
      CHECK(bossMan->agetDirection(testTank9) == 2);
   }//Check moving down by setting Y coordinate
   SECTION(" Setting Y coordinate to. Expected: true, Y = 6 ")
   {
      tank testTank9(8, 8);
      CHECK(bossMan->asetY(6, testTank9) == true);
      REQUIRE(bossMan->agetY(testTank9) == 6);
   }//Check moveDown with an input of 2
   SECTION(" Moving down two spaces. Expected: true, Y = 4, Direction = 2 ")
   {
      tank testTank9(8, 6);
      CHECK(bossMan->amoveDown(testTank9, 2) == true);
      REQUIRE(bossMan->agetY(testTank9) == 4);
      CHECK(bossMan->agetDirection(testTank9) == 2);
   }//Check moving off the map from 1,1 using default value
   SECTION(" Trying to move off the map. Expected: false ")
   {
      tank testTank9(1, 1);
      CHECK(bossMan->amoveDown(testTank9) == false);
      CHECK(bossMan->agetY(testTank9) == 1);
   }//Check moving off the map with a large input
   SECTION(" Trying to move off the map. Expected: false ")
   {
      tank testTank9(3, 3);
      CHECK(bossMan->amoveDown(testTank9, 6) == false);
      CHECK(bossMan->agetY(testTank9) == 3);
   }
   SECTION(" Trying to down(-1). Expected: false, y = 3")
   {
      tank testTank9(3, 3);
      CHECK(bossMan->amoveDown(testTank9, -1) == false);
      CHECK(bossMan->agetY(testTank9) == 3);
   }
}
/******************************************************************************
*  Tank left movement testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank10 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the left movement functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Tank Left movement")
{
   //Test moveLeft 1 space with default number
   SECTION(" Moving left 1 space. Expected: true, X = 7, Direction = 3 ")
   {
      tank testTank10(8, 8);
      CHECK(testTank10.moveLeft() == true);
      REQUIRE(testTank10.getX() == 7);
      CHECK(testTank10.getDirection() == 3);
   }//Test moving left by setting the x value
   SECTION(" Setting X to 6. Expected: true, X = 6 ")
   {
      tank testTank10(8, 8);
      CHECK(testTank10.setX(6) == true);
      REQUIRE(testTank10.getX() == 6);
   }//Test moveLeft 2 spaces with 2 input
   SECTION(" Move left 2 spaces. Expected: true, X = 4, Direction = 3 ")
   {
      tank testTank10(6, 8);
      CHECK(testTank10.moveLeft(2) == true);
      REQUIRE(testTank10.getX() == 4);
      CHECK(testTank10.getDirection() == 3);
   }
   //test move left off map with moveLeft
   SECTION(" Trying to move off grid by no value. Expected: false ")
   {
      tank testTank10(1, 1);
      CHECK(testTank10.moveLeft() == false);
   }//test move left off map with larger input
   SECTION(" Trying to move off grid by value 6. Expected: false ")
   {
      tank testTank10(3, 3);
      CHECK(testTank10.moveLeft(6) == false);
      CHECK(testTank10.getX() == 3);
   }
   SECTION(" Trying to move left(-1). Expected: false, x = 3 ")
   {
      tank testTank10(3, 3);
      CHECK(testTank10.moveLeft(-1) == false);
      CHECK(testTank10.getX() == 3);
   }
}

/******************************************************************************
*  Api class Tank left movement testing interface 
	(This is the test case purpse)
*
*  Author(s): Jon McKee, Dennis Kovarik
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank10 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the left movement functions 
*                                                   
********************************************************************************/
TEST_CASE("Api class Test Tank Left movement interface")
{
   //Test moveLeft 1 space with default number
   SECTION(" Moving left 1 space. Expected: true, X = 7, Direction = 3 ")
   {
      tank testTank10(8, 8);
      CHECK(bossMan->amoveLeft(testTank10) == true);
      REQUIRE(bossMan->agetX(testTank10) == 7);
      CHECK(bossMan->agetDirection(testTank10) == 3);
   }//Test moving left by setting the x value
   SECTION(" Setting X to 6. Expected: true, X = 6 ")
   {
      tank testTank10(8, 8);
      CHECK(bossMan->asetX(6, testTank10) == true);
      REQUIRE(bossMan->agetX(testTank10) == 6);
   }//Test moveLeft 2 spaces with 2 input
   SECTION(" Move left 2 spaces. Expected: true, X = 4, Direction = 3 ")
   {
      tank testTank10(6, 8);
      CHECK(bossMan->amoveLeft(testTank10, 2) == true);
      REQUIRE(bossMan->agetX(testTank10) == 4);
      CHECK(bossMan->agetDirection(testTank10) == 3);
   }
   //test move left off map with moveLeft
   SECTION(" Trying to move off grid by no value. Expected: false ")
   {
      tank testTank10(1, 1);
      CHECK(bossMan->amoveLeft(testTank10) == false);
   }//test move left off map with larger input
   SECTION(" Trying to move off grid by value 6. Expected: false ")
   {
      tank testTank10(3, 3);
      CHECK(bossMan->amoveLeft(testTank10, 6) == false);
      CHECK(bossMan->agetX(testTank10) == 3);
   }
   SECTION(" Trying to move left(-1). Expected: false, x = 3 ")
   {
      tank testTank10(3, 3);
      CHECK(bossMan->amoveLeft(testTank10, -1) == false);
      CHECK(bossMan->agetX(testTank10) == 3);
   }
}

/******************************************************************************
*  Tank spawning via set_ testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank11 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks that if spawning a tank via set_ it is in the map. We
*  currently do not test a coordinate after setX as these are spawning tests
*  so an invalid coordinate should stop the tank from spawning and it having no
*  valid position.  Checking value of 0 is commented out in case we decide to 
*  give tanks a default position of (0, 0) before being moved onto the field.
*                                                   
********************************************************************************/

TEST_CASE("Test tank spawning positions")
{
   SECTION(" Trying to set position off grid up. Expected: false ")
   {
      tank testTank10;
      CHECK(testTank10.setY(11) == false);
      //CHECK(testTank10.getY() == 0);
   }
   SECTION(" Trying to set position off grid right. Expected: false ")
   {
      tank testTank10;
      CHECK(testTank10.setX(21) == false);
      //CHECK(testTank10.getX() == 0);
   }
   SECTION(" Trying to set position off grid down. Expected: false ")
   {
      tank testTank10;
      CHECK(testTank10.setY(-1) == false);
      //CHECK(testTank10.getY() == 0);
   }
   SECTION(" Trying to set position off grid left. Expected: false ")
   {
      tank testTank10;
      CHECK(testTank10.setX(-1) == false);
      //CHECK(testTank10.getX() == 0);
   }
}

/******************************************************************************
*  Api Class Tank spawning interface via set_ testing 
*	(This is the test case purpse)
*
*  Author(s): Jon McKee, Dennis Kovarik
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank11 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the Api interface for spawning a tank via set_ it is 
*  in the map. We currently do not test a coordinate after setX as these are 
*  spawning tests so an invalid coordinate should stop the tank from spawning 
*  and it having no valid position.  Checking value of 0 is commented out in 
*  case we decide to give tanks a default position of (0, 0) before being moved 
*  onto the field.
*                                                   
********************************************************************************/
TEST_CASE("Api Class interface Testing for tank spawning positions")
{
   SECTION(" Trying to set position off grid up. Expected: false ")
   {
      tank testTank10;
      CHECK(bossMan->asetY(11, testTank10) == false);
      //CHECK(testTank10.getY() == 0);
   }
   SECTION(" Trying to set position off grid right. Expected: false ")
   {
      tank testTank10;
      CHECK(bossMan->asetX(21, testTank10) == false);
      //CHECK(testTank10.getX() == 0);
   }
   SECTION(" Trying to set position off grid down. Expected: false ")
   {
      tank testTank10;
      CHECK(bossMan->asetY(-1, testTank10) == false);
      //CHECK(testTank10.getY() == 0);
   }
   SECTION(" Trying to set position off grid left. Expected: false ")
   {
      tank testTank10;
      CHECK(bossMan->asetX(-1, testTank10) == false);
      //CHECK(testTank10.getX() == 0);
   }
}

/******************************************************************************
*  Tank Direction testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank11 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks changing the tank directions movement functions 
*                                                   
********************************************************************************/

TEST_CASE("Test tank Direction")
{
   //Checking default direction of a tank
   SECTION(" Checking default direction (Expect: 0) ")
   {
      tank testTank11;
      CHECK(testTank11.getDirection() == 0);
   }//Checking setting direction to 1
   SECTION(" Setting direction to 1. Expected: true, direction = 1 ")
   {
      tank testTank11;
      REQUIRE(testTank11.setDirection(1) == true);
      REQUIRE(testTank11.getDirection() == 1);
   }//Checking setting direction to 2
   SECTION(" Setting direction to 2. Expected: true, direction = 2 ")
   {
      tank testTank11;
      REQUIRE(testTank11.setDirection(2) == true);
      REQUIRE(testTank11.getDirection() == 2);
   }//Checking setting direction to 3
   SECTION(" Setting direction to 3. Expected: true, direction = 3 ")
   {
      tank testTank11;
      REQUIRE(testTank11.setDirection(3) == true);
      REQUIRE(testTank11.getDirection() == 3);
   }//Checking setting from a valid direction back to 0
   SECTION(" Setting direction to 0. Expected: true, direction = 0")
   {
      tank testTank11;
      testTank11.setDirection(2);
      CHECK(testTank11.setDirection(0) == true);
      CHECK(testTank11.getDirection() == 0);
   }//Checking setting direction to -1
   SECTION(" Setting direction to -1. Expected: fail, direction = 3 ")
   {
      tank testTank11;
      testTank11.setDirection(3);
      CHECK(testTank11.setDirection(-1) == false);
      CHECK(testTank11.getDirection() == 3);
   }//Checking setting direction to 4
   SECTION(" Setting direction to 4. Expected: fail, direction = 3")
   {
      tank testTank11;
      testTank11.setDirection(3);
      CHECK(testTank11.setDirection(4) == false);
      CHECK(testTank11.getDirection() == 3);
   }
}

/******************************************************************************
*  Api class Tank Direction testing interface (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank11 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the Api Class interface for changing the tank 
*  directions movement functions 
*                                                   
********************************************************************************/
TEST_CASE("Test Api class tank Direction interface")
{
   //Checking default direction of a tank
   SECTION(" Checking default direction (Expect: 0) ")
   {
      tank testTank11;
      CHECK(bossMan->agetDirection(testTank11) == 0);
   }//Checking setting direction to 1
   SECTION(" Setting direction to 1. Expected: true, direction = 1 ")
   {
      tank testTank11;
      REQUIRE(bossMan->asetDirection(testTank11, 1) == true);
      REQUIRE(bossMan->agetDirection(testTank11) == 1);
   }//Checking setting direction to 2
   SECTION(" Setting direction to 2. Expected: true, direction = 2 ")
   {
      tank testTank11;
      REQUIRE(bossMan->asetDirection(testTank11, 2) == true);
      REQUIRE(bossMan->agetDirection(testTank11) == 2);
   }//Checking setting direction to 3
   SECTION(" Setting direction to 3. Expected: true, direction = 3 ")
   {
      tank testTank11;
      REQUIRE(bossMan->asetDirection(testTank11, 3) == true);
      REQUIRE(bossMan->agetDirection(testTank11) == 3);
   }//Checking setting from a valid direction back to 0
   SECTION(" Setting direction to 0. Expected: true, direction = 0")
   {
      tank testTank11;
      testTank11.setDirection(2);
      REQUIRE(bossMan->asetDirection(testTank11, 0) == true);
      REQUIRE(bossMan->agetDirection(testTank11) == 0);
   }//Checking setting direction to -1
   SECTION(" Setting direction to -1. Expected: fail, direction = 3 ")
   {
      tank testTank11;
      testTank11.setDirection(3);
      REQUIRE(bossMan->asetDirection(testTank11, -1) == false);
      REQUIRE(bossMan->agetDirection(testTank11) == 3);
   }//Checking setting direction to 4
   SECTION(" Setting direction to 4. Expected: fail, direction = 3")
   {
      tank testTank11;
      testTank11.setDirection(3);
      REQUIRE(bossMan->asetDirection(testTank11, 4) == false);
      REQUIRE(bossMan->agetDirection(testTank11) == 3);
   }
}

/******************************************************************************
*  Tank speed testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank12 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks changing the speed value functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Tank Speed")
{
   //Checking the default speed at value 1
   SECTION(" Checking default speed: 1 ")
   {
      tank testTank12;
      CHECK(testTank12.getSpeed() == 1);
   }//Checking setting speed to 4
   SECTION(" Setting speed to 4 (High but allowed speed). Expected: setting True, speed = 4")
   {
      tank testTank12;
      CHECK(testTank12.setSpeed(4) == true);
      CHECK(testTank12.getSpeed() == 4);
   }//checking setting speed to 0
   SECTION(" Setting speed to 0 (Stuck speed). Expected: setting True, speed = 0")
   {
      tank testTank12;
      CHECK(testTank12.setSpeed(0) == true);
      CHECK(testTank12.getSpeed() == 0);
   }//Checking setting speed to -1
   SECTION(" Setting speed to negative value. Expected: setting false, speed = 1")
   {
      tank testTank12;
      CHECK(testTank12.setSpeed(-1) == false);
      CHECK(testTank12.getSpeed() == 1);
   }//Checking setting speed to too high a value
   SECTION(" Setting speed to 10. (Too high value, expect default value 1) ")
   {
      tank testTank12;
      CHECK(testTank12.setSpeed(10) == false);
      CHECK(testTank12.getSpeed() == 1);
   }
}

/******************************************************************************
*  Api class Tank speed testing interface (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank12 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks Api class interface for changing the speed value 
*  functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Api interface Tank Speed")
{
   //Checking the default speed at value 1
   SECTION(" Checking default speed: 1 ")
   {
      tank testTank12;
      CHECK(bossMan->agetSpeed(testTank12) == 1);
   }//Checking setting speed to 4
   SECTION(" Setting speed to 4 (High but allowed speed). Expected: setting True, speed = 4")
   {
      tank testTank12;
      CHECK(bossMan->asetSpeed(4, testTank12) == true);
      CHECK(bossMan->agetSpeed(testTank12) == 4);
   }//checking setting speed to 0
   SECTION(" Setting speed to 0 (Stuck speed). Expected: setting True, speed = 0")
   {
      tank testTank12;
      CHECK(bossMan->asetSpeed(0, testTank12) == true);
      CHECK(bossMan->agetSpeed(testTank12) == 0);
   }//Checking setting speed to -1
   SECTION(" Setting speed to negative value. Expected: setting false, speed = 1")
   {
      tank testTank12;
      CHECK(bossMan->asetSpeed(-1, testTank12) == false);
      CHECK(bossMan->agetSpeed(testTank12) == 1);
   }//Checking setting speed to too high a value
   SECTION(" Setting speed to 10. (Too high value, expect default value 1) ")
   {
      tank testTank12;
      CHECK(bossMan->asetSpeed(10, testTank12) == false);
      CHECK(bossMan->agetSpeed(testTank12) == 1);
   }
}

/******************************************************************************
*  Tank Kill tracker testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank12 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the kill tracker functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Kill Tracker")
{
   //Checking default value of 0
   SECTION(" Checking initial kill value: 0 ")
   {
      tank testTank13;
      CHECK(testTank13.getKill() == 0);
   }
   //Checking setting kills to 2
   SECTION(" Setting kills to 2 ")
   {
      tank testTank13;
      CHECK(testTank13.setKill(2) == true);
      CHECK(testTank13.getKill() == 2);
   }//Checking add 1 via addKill()
   SECTION(" Add 1 via no arguments: 1 ")
   {
      tank testTank13;
      CHECK(testTank13.addKill() == true);
      CHECK(testTank13.getKill() == 1);
   }//Checking add 1 via addKill(1)
   SECTION(" Adding one kill with argument: 1 ")
   {
      tank testTank13;
      CHECK(testTank13.addKill(1) == true);
      CHECK(testTank13.getKill() == 1);
   }//Checking adding 10 kills
   SECTION(" Adding ten kills. Expected: 10 ")
   {
      tank testTank13;
      REQUIRE(testTank13.addKill(10) == true);
      REQUIRE(testTank13.getKill() == 10);
   }//Checking setting kills back to 0
   SECTION(" Setting kills to 0. Expected: 0")
   {
      tank testTank13;
      CHECK(testTank13.addKill(10) == true);
      CHECK(testTank13.setKill(0) == true);
      CHECK(testTank13.getKill() == 0);
   }//Checking subtracting a kill via -1
   SECTION(" Adding -1 kills: Expected: False, Kills = 0")
   {
      tank testTank13;
      CHECK(testTank13.addKill(-1) == false);
      CHECK(testTank13.getKill() == 0);
   }
   SECTION(" Setting -1 kills: Expected: False, Kills = 0")
   {
      tank testTank13;
      CHECK(testTank13.setKill(-1) == false);
      CHECK(testTank13.getKill() == 0);
   }
}

/******************************************************************************
*  Api interface Tank Kill tracker testing (This is the test case purpse)
*
*  Author(s): Jon McKee, Dennis Kovark
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank12 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case checks the Api interface for the kill tracker functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Api interface for Kill Tracker")
{
   //Checking default value of 0
   SECTION(" Checking initial kill value: 0 ")
   {
      tank testTank13;
      CHECK(bossMan->agetKill(testTank13) == 0);
   }
   //Checking setting kills to 2
   SECTION(" Setting kills to 2 ")
   {
      tank testTank13;
      CHECK(bossMan->asetKill(testTank13, 2) == true);
      CHECK(bossMan->agetKill(testTank13) == 2);
   }
}
/******************************************************************************
*  Tank health tracker testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank14 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case now checks the health tracker functions 
*                                                   
********************************************************************************/

TEST_CASE("Test Health Tracker")
{
   //Checking default value at 10
   SECTION(" Checking initial health value. Expected: 10 ")
   {
      tank testTank14;
      CHECK(testTank14.getHealth() == 10);
   }//Checking setting health to 3
   SECTION(" Setting health to 3. Expected: 3 ")
   {
      tank testTank14;
      CHECK(testTank14.setHealth(3) == true);
      CHECK(testTank14.getHealth() == 3);
   }//Checking dealing 1 damage with takeDamage()
   SECTION(" Adding 1 damage with no argument: Health = 9 ")
   {
      tank testTank14;
      CHECK(testTank14.takeDamage() == true);
      CHECK(testTank14.getHealth() == 9);
   }
   //Checking dealing 2 damage with takeDamage(2)
   SECTION(" Adding 2 damage via agument: Health = 8 ")
   {
      tank testTank14;
      CHECK(testTank14.takeDamage(2) == true);
      CHECK(testTank14.getHealth() == 8);
   }//Checking adding 10 damage
   SECTION(" Adding 10 damage. Expected health: 0 ")
   {
      tank testTank14;
      REQUIRE(testTank14.takeDamage(10) == true);
      REQUIRE(testTank14.getHealth() == 0);
   }//Checking setting health back to 10
   SECTION(" Setting health back to 10. Expected health = 10")
   {
      tank testTank14;
      testTank14.takeDamage(10);
      CHECK(testTank14.setHealth(10) == true);
      CHECK(testTank14.getHealth() == 10);
   }//Checking adding health by dealing -1 damage
   SECTION(" Adding -1 damage.  Expected: False, health = 10 ")
   {
      tank testTank14;
      CHECK(testTank14.takeDamage(-1) == false);
      CHECK(testTank14.getHealth() == 10);
   }
   SECTION(" Setting -1 health.  Expected: False, health = 10 ")
   {
      tank testTank14;
      CHECK(testTank14.setHealth(-1) == false);
      CHECK(testTank14.getHealth() == 10);
   }
   //Checking Api Interface
   SECTION(" Setting -1 health.  Expected: False, health = 10 ")
   {
      tank testTank14;
      CHECK(bossMan->asetHealth(-1, testTank14) == false);
      CHECK(bossMan->agetHealth(testTank14) == 10);
   }
   SECTION(" Adding 1 damage with no argument: Health = 9 ")
   {
      tank testTank14;
      CHECK(bossMan->atakeDamage(testTank14) == true);
      CHECK(bossMan->agetHealth(testTank14) == 9);
   }
   SECTION("Test Api interface function aisAlive on expect true ")
   {
      tank testTank14;
      CHECK(bossMan->aisAlive(testTank14) == true);
   }
}

/******************************************************************************
*  Tank setPos getPos testing (This is the test case purpse)
*
*  Author(s): Jon McKee
*  Parameters:  (These are parameters the test uses in all sections)
*    tank testTank15 - An instance of a Tank to be used for testing
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case now checks the limits of the setPos function and the value
*    returned by getPos.
*                                                   
********************************************************************************/

TEST_CASE("Test setPos and getPos functions")
{
   SECTION(" Trying to set tank to (0, 1). Expected: False ")
   {
      tank testTank15;
      CHECK(testTank15.setPos(0, 1) == false);
   }
   SECTION(" Trying to set tank to (1, 0). Expected: False ")
   {
      tank testTank15;
      CHECK(testTank15.setPos(1, 0) == false);
   }
   SECTION(" Trying to set tank to (21, 1). Expected: False ")
   {
      tank testTank15;
      CHECK(testTank15.setPos(21, 1) == false);
   }
   SECTION(" Trying to set tank to (1, 11). Expected: False ")
   {
      tank testTank15;
      CHECK(testTank15.setPos(1, 11) == false);
   }
   SECTION(" Trying to set tank to (5, 5). Expected: True ")
   {
      tank testTank15;
      CHECK(testTank15.setPos(5, 5) == true);
   }
   SECTION(" Trying to set tank to (5, 6) and get (5 ,6) back. Expected: Set = True, Get = True, x = 5, y = 6 ")
   {
      tank testTank15;
      int x, y;
      CHECK(testTank15.setPos(5, 6) == true);
      CHECK(testTank15.getPos(x, y) == true);
      CHECK(x == 5);
      CHECK(y == 6);
   }
   //Testing Api interface
   SECTION(" Trying to set tank to (5, 6) and get (5 ,6) back. Expected: Set = True, Get = True, x = 5, y = 6 ")
   {
      tank testTank15;
      int x, y;
      CHECK(bossMan->asetPos(5, 6, testTank15) == true);
      CHECK(bossMan->agetPos(x, y, testTank15) == true);
      CHECK(x == 5);
      CHECK(y == 6);
   }
}
