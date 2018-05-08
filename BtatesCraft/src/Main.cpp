#include <iostream>
#include "Game.h"






int main()
{
	
	Game game("BtatesCraft",1000,1000);
		
	
	
		
		
		while (game.IsRunning())
		{
			
			game.GameLoop();
			
			
		}
		
		
	return 0;
}