#include"includes.h"
#include"Game.h"

const int FPS = 40;
const int DELAY_TIME = 1000 / FPS;

int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL)); // random numbers

	Game TheGame;
	Uint32 frameStart, frameTime;
	
	if(TheGame.init("ONE BUTTON BOB", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 1))
	{
		while(TheGame.Running)
		{
			frameStart = SDL_GetTicks(); // Start counting time

			TheGame.handle_events();
			TheGame.update();

			frameTime = SDL_GetTicks() - frameStart; // time spended for 1 iteration

			if(frameTime< DELAY_TIME) // If less than FPS
				SDL_Delay((int)(DELAY_TIME - frameTime)); // wait
		}
	}
	else
	{
		std::cout << "Can't init the game :/  " << SDL_GetError() << std::endl;
		system("PAUSE"); // to keep console open after crash
		return -1;
		
	}
	
	TheGame.clean();

	return 0;
}