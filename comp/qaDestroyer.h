#ifndef _QADESTROYER_
#define _QADESTROYER_
#include "base.h"
#include <iostream>
#include "src/constants.h"
#include "../api.h"



class qaDestroyer : public comp
{
public:
	qaDestroyer();
	~qaDestroyer();
	std::string tankName();
	ActionCommand performAction();
	void whatTankSees();

protected:
	int getPlayerId();
	bool checkLocalMap( int x, int y );
	void setPlayerAP(api *ap){this->ap = ap;};
	ActionCommand changeDir( int currDir );
	void setPlayerNumber( int pNum ){ playerNumber = pNum; }

private:
	int playerNumber;
	api *ap;
	int **map;
	int dir;
	int speed = 1;
	int myX;
	int myY;

	friend class api;	
};



extern "C" comp* createTank()
{
	return new qaDestroyer();
}


extern "C" void destroyTank( comp *p )
{
	delete p;
}
#endif
