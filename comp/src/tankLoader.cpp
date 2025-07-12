#include "tankLoader.h"

/*
	ActionCommand doMoves(int player)
	Author(s): Dr Hinker

	Parameters
		int player - the tank whose move we want to check
	Return Value
		Returns the tanks proposed move

	This function takes a player input and uses that as an index
  to locate the specific tank.  We then call that tanks doMoves
  function to get the player move.
*/
// Loop over the tanks in the _tanks vector and call their performAction method
ActionCommand tankLoader::doMoves(int player)
{
   //printf("Accessing Comp number: %d\n", player);
   //printf("Tank name: %s\.n", _tanks[player].ptr->tankName().c_str()); 
   return _tanks[player].ptr->performAction();
   //{
      //std::cout << "Move from " << t.ptr->tankName() << " is " <<
      //   ActionCommand_Name[t.ptr->performAction()] << std::endl;
   //}
}

/*
	void doMoves()
	Author(s): Dr Hinker

	Parameters
	Return Value

	This function loops through our tanks library and calls the
  destructor for each tank.
*/
// Free the tank objects and their associated shared objects
void tankLoader::unloadTanks()
{
   for(tankHandle& t : _tanks)
   {
      t.destroyFunc(t.ptr);
      dlclose(t.library);
   }
}

/*
	void loadTanks(string dir)
	Author(s): Dr Hinker

	Parameters
    string dir - this is the string of the directory to look for
    tanks in.
	Return Value

	This function loops through the specified directory looking
  for shared tank libraries to load into the game
*/
// Attempt to load all the shared objects in directory 'dir' which meet the
// tank object interface
void tankLoader::loadTanks(std::string dir)
{
   // number of players loaded
   int count = 0;
   // Pointer to a directory in the file system
   DIR *dp;
   // Pointer to a directory entry
   struct dirent *dirp;

   std::cout << "Adding tanks from " << dir << std::endl;

   // If we can't open the directory 'dir' throw error and return   
   if ((dp = opendir(dir.c_str())) == NULL)
   {
      std::cout << "Error(" << errno << ") opening " << dir << std::endl;
      return;
   }

   // While there are elements in the directory
   while ((dirp = readdir(dp)) != nullptr)
   {
      std::string fileName = std::string(dirp->d_name);

      // If the fileName ends in .so
      if (fileName.find(".so") != std::string::npos)
      {
         tankHandle newTank;

         std::string path = dir + "/" + fileName;
         std::cout << "Loading tank from " << path << std::endl;

         // Attempt to open a dynamic library at 'path'
         newTank.library = dlopen(path.c_str(), RTLD_LAZY);
         if (newTank.library == nullptr)
         {
            std::cout << "unable to open tank as shared object " << fileName << " " << dlerror() << std::endl;
            continue;
         }

         // Clear the error codes
         dlerror();
         bool failed = false;

         // Try to find the 'createTank' symbol in the .so library opened before
         newTank.createFunc = (tankCreate_t *) dlsym(newTank.library, "createTank");
         const char *err = dlerror();
         if (err)
         {
            std::cout << "Unable to load createTank function: " << err << std::endl;
            failed = true;
         }

         // Clear the error codes
         dlerror();

         // Try to find the 'destroyFunc' symbol in the .so opened before 
         newTank.destroyFunc = (tankDestroy_t*) dlsym(newTank.library, "destroyTank");
         err = dlerror();
         if (err)
         {
            std::cout << "Unable to load destroyTank function: " << err << std::endl;
            failed = true;
         }

         // Save a pointer to the tank object's constructor 
         newTank.ptr = newTank.createFunc();
         if (newTank.ptr == nullptr)
         {
            std::cout << "Failed to create player" << std::endl;
            failed = true;
         }

         // If anything failed, close this library
         if (failed)
         {
            dlclose(newTank.library); 
         }
         else
         {
            // If everything passed, add this tankHandle to the vector of
            // loaded tankHandles
            std::cout << "Added tank " << newTank.ptr->tankName() << std::endl;
            _tanks.push_back(newTank);
            count++;
         }
      }
   }
   ap->asetPlayerCount(count);
   closedir(dp);
}
/**************************************************
*	setPlayerNumber(int tIndex, int pNum)
*	Authors: Jonathan McKee
*	Parameters
*		int tIdenx  - The index number for finding the player
*		int pNum  	- The player number to assign
*	Return Value
*
*	This function set's the player's tank number equal to the unique
*	number assigned to the tank.
*
***************************************************/

void tankLoader::setPlayerNumber(int tIndex, int pNum)
{
  _tanks[tIndex].ptr->setPlayerNumber(pNum);
}

/**************************************************
*	setPlayerAO(int tIndex)
*	Authors: Jonathan McKee
*	Parameters
*		int tIdenx  - The index number for finding the player
*	Return Value
*
*	This function set's the player's AP equal to the
* calling API object, without this the player won't
* be able to make API calls..
*
***************************************************/
void tankLoader::setPlayerAP(int tIndex)
{
  _tanks[tIndex].ptr->setPlayerAP(ap);
}

/**************************************************
*	setTankLoader(api *ap)
*	Authors: Jonathan McKee
*	Parameters
*		api *ap  - The index number for finding the player
*	Return Value
*
*	This function set's the tankLoaders API pointer to
* the calling api object.
*
***************************************************/
void tankLoader::setTankLoad(api *ap)
{
    this->ap = ap;
}

std::string tankLoader::getTankName(int index)
{
	if( (unsigned int)index >= _tanks.size() )
	{
		return "error tank index out of bounds";
	}

	return _tanks[index].ptr->tankName();
}
