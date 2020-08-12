#include "../../libraries/src/catch.hpp"
#include "../../classes/classProjectile.h"
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

//class projectile;  //Forward declaration make sure this class name matches the class in classProjectile.h

//Sample projectile constructors
/*TEST_CASE("Create a projectile")
{
   projectile testProj;
   REQUIRE(sizeof(testProj)> 0);   
}

TEST_CASE("Create a projectile with starting inputs")
{
   projectile testProj(1, 1);
   REQUIRE(sizeof(testProj)> 0);
   SECTION("Checking out of range X Value: 200")
   {
      tank testProj2(200, 1);
      CHECK(sizeof(testProj)> 0);
      CHECK(testProj2.getX() != 200);
   }
}*/






/******************************************************************************
*  Test Projectile Class postion getter (This is the test case purpse)
*
*  Author(s): Dennis Kovarik
*  Parameters:  (These are parameters the test uses)
*    projectile testProj - An instance of the projectile class for testing 
*    			   purposes
*  Return Value:
*    Returns the two integer values x and y by reference
*
*  This test case checks that the getPosition function of the projectil class
*  returns the right values given intial conditions. Also tests api interface. 
*                                                   
********************************************************************************/
TEST_CASE("Testing getPosition expect x == 2 and y == 3")
{
  int x, y;
  projectile testProj(1,2,3,0, 5);
  CHECK(testProj.getPosition(x, y) == true);
  CHECK(x == 2);
  CHECK(y == 3);
  //Testing api interface
  bossMan->agetPosition(x, y, testProj);
  CHECK(x == 2);
  CHECK(y == 3);
}

/******************************************************************************
*  Test Projectile Class direction getter (This is the test case purpse)
*
*  Author(s): Dennis Kovarik
*  Parameters:  (These are parameters the test uses)
*    projectile testProj - An instance of the projectile class for testing 
*    			   purposes
*  Return Value:
*    Returns the an intereger values representing the projectile's direction
*
*  This test case checks that the getDirection function of the projectil class
*  returns the right values given intial conditions. Also tests api interface. 
*                                                   
********************************************************************************/
TEST_CASE("Testing getDirection expect 0")
{
  projectile testProj(1,2,3,0, 5);
  CHECK(testProj.getDirection() == 0);
}

/******************************************************************************
*  Test Projectile Class owner getter (This is the test case purpse)
*
*  Author(s): Dennis Kovarik
*  Parameters:  (These are parameters the test uses)
*    projectile testProj - An instance of the projectile class for testing 
*    			   purposes
*  Return Value:
*    Returns the two integer value representing the projectile's owner
*
*  This test case checks that the getOwner function of the projectil class
*  returns the right values given intial conditions. Also tests api interface. 
*                                                   
********************************************************************************/
TEST_CASE("Testing getOwner expect 5")
{
  projectile testProj(1,2,3,0, 5);
  CHECK(testProj.getOwner() == 5);
  CHECK(bossMan->agetOwner(testProj) == 5);
}

/******************************************************************************
*  Test Projectile Class velocity getter (This is the test case purpse)
*
*  Author(s): Dennis Kovarik
*  Parameters:  (These are parameters the test uses)
*    projectile testProj - An instance of the projectile class for testing 
*    			   purposes
*  Return Value:
*    Returns the two integer value representing the projectiles velocity
*
*  This test case checks that the getVelocity function of the projectil class
*  returns the right values given intial conditions. Also tests api interface. 
*                                                   
********************************************************************************/
TEST_CASE("Testing getVelocity expect 1")
{
  projectile testProj(1,2,3,0, 5);
  CHECK(testProj.getVelocity() == 1);
}

/******************************************************************************
*  Test Projectile Class moveProjectile function(This is the test case purpse)
*
*  Author(s): Dennis
*  Parameters:  (These are parameters the test uses)
*    projectile testProj - An instance of the projectile class for testing 
*    			   purposes
*  Return Value:
*    Returns true if projectile was successfully moved
*    Returns false if projectile could not be moved
*
*  This test case checks that the moveProjectile function of the projectil class
*  increments the position of the test projectile. 
*                                                   
********************************************************************************/
TEST_CASE("Move projectile from 2,3 to 2,4 owned by player 6")
{
  int x, y;
  projectile testProj(1,2,3,0, 6);
  CHECK(testProj.moveProjectile() == true);
  CHECK(testProj.getPosition(x, y) == true);
  CHECK(x == 2);
  CHECK(y == 4);
}

/******************************************************************************
*  Test Api class interface for the Projectile Class moveProjectile 
*    function(This is the test case purpse)
*
*  Author(s): Dennis
*  Parameters:  (These are parameters the test uses)
*    projectile testProj - An instance of the projectile class for testing 
*    			   purposes
*  Return Value:
*    Returns void
*
*  This test case checks that the Api class interface amoveProjectile correctly 
*  moves the projectile. 
*                                                   
********************************************************************************/
TEST_CASE("Testing Api interface move projectile from 2,3 to 2,4 owned by player 6")
{
  int x, y;
  projectile testProj(1,2,3,0, 6);
  bossMan->amoveProjectile(testProj);
  bossMan->agetPosition(x, y, testProj);
  CHECK(x == 2);
  CHECK(y == 4);
}
