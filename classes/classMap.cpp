/*
	classMap.cpp
	Author(s): Levi Butts, William Doering, Gwyneth Kardelis
	Reviewer:
	Last Date Modified: 10/2/2018

  This file is displays the game using GLUT. It creates the tanks,
  obstactals, projectile, and field to the screen for the user.
*/

#include "../api.h"
#include "../libraries/src/alloc2d.h"

/*
	map::map()
	Author(s): William Doering
	Reviewer:

  Parameters
    none
  Return Value
    none

  This is the constructor for the map class. This function
  sets the headpointer to nullptr.
*/
map::map()
{
}

/*
	map::~map()
	Author(s): Levi Butts
	Reviewer:

  Parameters
    none
  Return Value
    none

  This is the destructor for the map class.
*/
map::~map()
{
}


/*
	bool map::readMap(std::string Mapname)
	Author(s): Levi Butts
	Reviewer:

	Parameters
	Return Value
		bool - returns true if the map file opens and is in the
		correct game mode otherwise returns false

	This function opens the file for the map that is withint the previous
	directories of the project and if it exists there and is in the correct
	game mode the mapfile is read into the field array.
*/
int map::readMap(std::string mapName)
{
  if (ap->agetMapName() != mapName)
         ap->asetMapName(mapName); 
  //mapName = "maps/" + ap->agetMapName();
  mapName = "maps/" + mapName;
  std::ifstream mapFile;
  std::string gameMode;
  std::string temp;
  int fieldx, fieldy;

  // printf("attempting to open map file: %s\n", mapName.c_str());
  mapFile.open(mapName, std::ios::in | std::ios::binary);

  if(!mapFile)
  {
    printf("Unable to open file: %s\n", mapName.c_str());
    printf("Please check map name.\n");
    return 3;
  }

  // printf("Map file opened successfully.\n");

  //pulls out the gameMode
  getline(mapFile, gameMode, '\n');
  printf("     GameMode: %s\n", gameMode.c_str()); 
  transform(gameMode.begin(), gameMode.end(), gameMode.begin(), ::tolower);
  if(gameMode.compare("tanks") != 0 &&
     gameMode.compare("planes") != 0 &&
     gameMode.compare("boats") != 0)
  {
    printf("Invalid game mode detected in map, please check map file.\n");
    return 4;
  }
  printf("Game::Saving game mode.\n");
  ap->asetGameMode(gameMode);
  //pull out the rows value
  getline(mapFile, temp, 'x');
  fieldx = stoi(temp);
  //pull out the columns values
  getline(mapFile, temp, '\n');
  fieldy = stoi(temp);
  printf("Game::Setting map size:\n");
  printf("     FieldX: %d\n", fieldx);
  printf("     FieldY: %d\n", fieldy);
  ap->asetFieldX(fieldx);
  ap->asetFieldY(fieldy);
  //create a new 2D array that has 1 extra row and 1 extra column
  field = alloc2D(fieldy + 1, fieldx + 1);
  //Transcribe the map line by line to the new field array, starting at (1,1)
  for(int i = fieldy; i >= 1; i--)
  {
    getline(mapFile, temp, '\n');
    for(int j = 1; j <= fieldx; j++)
    {
      field[i][j] = temp[j-1];
      if (temp[j-1] == 'B')
              ap->acreateObject(j, i, 7);
      else if (temp[j-1] == 'T')
              ap->acreateObject(j, i, 1);
      else if (temp[j-1] == 'R')
              ap->acreateObject(j, i, 5);
    }
  }

  mapFile.close();

  return 0;
}

/*
  map* map::getMap()
  Author(s): Levi Butts
	Reviewer:
  Parameters
    none
  Return Value
    map* this

	Returns a pointer to a map that already exists.
*/
map* map::getMap()
{
  return this;
}


/*
  tileObject map::getMapObject(int x, int y)
  Author(s): Levi Butts

  Parameter
    int x - the x coordinate of the map/field
    int y - the y coordinate of the map/field
  Return Value
    tileObject::"something" - the function returns what is at each coordinate

  This function reads in what ascii is at each coordinate in the array and assigns
  the corresponding tileobject to it
*/
tileObject map::getMapObject(int x, int y)
{

  //printf("At postion: (%d, %d) there is a: %d\n", x, y, field[x][y]);

  switch(field[y][x])
  {
    case 'T':
      return tileObject::TREE;
    case 'R':
      return tileObject::ROCK;
    case 'P':
      return tileObject::PROJECTILE;
    case 'W':
      return tileObject::WATER;
    case 'X':
      return tileObject::EMPTY;
    case 'B':
      return tileObject::BUSH;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case 'E':
      return tileObject::TANK;
  }
  return tileObject::EMPTY;
}

/*	Author(s): Levi Butts
	Reviewer:

	Parameters
    int x - the x coordinate of the map/field
		int y - the y coordinate of the map/field
		tileObject newObj - the object at that coordinate
	Return Value
		bool - returns true when the object at the coordinates
		is updated correctly to what should be there otherwise
		it returns false

	The function checks to see if the object at the coordinates
	has change(e.g. the tank moved into that space or a projectile
	was fire, etc)
*/
bool map::changeMapObject(int x, int y, tileObject newObj)
{
	tileObject currObj = getMapObject(x, y);

	if(newObj != tileObject::EMPTY && 
    newObj != tileObject::TANK &&
		newObj != tileObject::PROJECTILE && 
    newObj != tileObject::TREE &&
		newObj != tileObject::ROCK && 
    newObj != tileObject::WATER &&
    newObj != tileObject::BUSH)
		return false;

	if(currObj == newObj){
	//printf("Same object not changing\n");
      return true;
  }

	field[y][x] = convertTileObj(newObj);
	if(currObj == newObj)
		return false;

	return true;
}


/*
	int converTileObj(tileObject)
	Author(s): Levi Butts
	Reviewer:

  Parameters
    tileObject obj - the object in the map (the tank or an obstacle)
  Return Value
    int - returns the binary value of the object

  This function converts the tileObjects back into ascii.
*/
int convertTileObj(tileObject obj)
{
  switch(obj)
  {
    case tileObject::TREE:
      return 'T';
    case tileObject::ROCK:
      return 'R';
    case tileObject::WATER:
      return 'W';
    case tileObject::PROJECTILE:
      return 'P';
    case tileObject::TANK:
      return 'E';
    case tileObject::EMPTY:
      return 'X';
    case tileObject::BUSH:
      return 'B';
    default:
      break;
  }
  return 'X';
}





bool map::setMap(api *ap){
  this->ap = ap;
  return ap->setMap(this);
}

int map::getFieldX()
  {
    return ap->agetFieldX();
  }
int map::getFieldY()
  {
    return ap->agetFieldY();
  }
std::string map::getGameMode()
  {
    return ap->agetGameMode();
  }
