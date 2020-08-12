/*
  classMap.h
  Author(s): Levi Butts, William Doering, Gwyneth Kardelis

  This file has the enum class of all the different objects
  that could be in the field and be displayed on the screen
  It also contains the map class which holds the field array
  which is everything and and thing that has to deal with
  what gets displayed to the screen and how.
*/
#ifndef __CLASSMAP_H_
#define __CLASSMAP_H_
#include <string>
//forward declaration
class tank;
class api;
/*
  enum class tileObject
  Author(s): Levi Butts

  This holds all the different items that could be in
  the map.
*/
enum class tileObject
{
  EMPTY,
  TANK,
  PROJECTILE,
  TREE,
  ROCK,
  WATER,
  BUSH
};

int convertTileObj(tileObject obj);

/*
  class map
  Author(s): Levi Butts, William Doering, Gwyneth Kardelis

        This is used to load the map and all of its components graphics
*/
class map
{
public:
  map();
  ~map();
#ifndef CATCH
protected:
#endif
  tileObject getMapObject(int x, int y);
  int getFieldX();
  int getFieldY();
  std::string getGameMode();
  int readMap(std::string mapName = "default.map");

  map* getMap();
  bool changeMapObject(int x, int y, tileObject newObj);

  bool setMap(api *ap);
#ifndef CATCH
private:
#endif
  api *ap;
  int** field;
  friend class api;
};

#endif
