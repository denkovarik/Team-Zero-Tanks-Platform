#include "qaDestroyer.h"
#include "../libraries/src/alloc2d.h"

using namespace std;



qaDestroyer::qaDestroyer() {
map = alloc2D(11, 21);
}
qaDestroyer::~qaDestroyer() {}

string qaDestroyer::tankName()
{
		

	return "QA Destroyer";
}

void qaDestroyer::whatTankSees()
{
	ap->apgetMap( playerNumber, map );

/*	for( int i = 10; i > 0; i-- )
	{
		for( int j = 1; j <= 20; j++ )
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}*/
}

ActionCommand qaDestroyer::performAction()
{
  static int moves[] = { 0, 6, 7, 6, 1, 6, 1, 4, 1, 2, 6, 1, 2, 3 };
  whatTankSees();

	if( ap->apgetTurn() < 14 )
	{
		return ActionCommand( moves[ap->apgetTurn()] );
	}

	//return ActionCommand( 6  );
	return ActionCommand( rand() % 7 );
}
