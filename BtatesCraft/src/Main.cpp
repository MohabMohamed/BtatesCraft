#include <iostream>
#include "Game.h"






int main()
{
	
	Game game("BtatesCraft",500,500);
		
	
	
		
		
		while (game.IsRunning())
		{
			
			game.GameLoop();
			
			
		}
		
		
	return 0;
}