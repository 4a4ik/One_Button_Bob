#include "Game.h"
#include"TextureManager.h"
#include"Player.h"
#include"Background.h"

TextureManager TheTextureManager; // working with images
Player ThePlayer( 300, 320 );

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if(m_pWindow != 0) // window init success
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if(m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

				// to load
				if(!TheTextureManager.load("files/img/hero.png", "animate", m_pRenderer))
				{
					return false;
				}

				if(!TheTextureManager.load("files/img/bg.png", "bg", m_pRenderer))
				{
					return false;
				}

			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}



	Running = true;
	std::cout << "init success\n";
	return true;

}

void Game::handle_events()
{
	SDL_Event game_event;
	while (SDL_PollEvent(&game_event))
	{
		//If user closes he window
		if (game_event.type == SDL_QUIT)
		{
			Running = false;
		}

		if( game_event.type == SDL_KEYDOWN && game_event.key.repeat == 0 )
		{
			ThePlayer.handle_input( 1, game_event.key.keysym.scancode );
		}

		else if( game_event.type == SDL_KEYUP )
		{
			ThePlayer.handle_input( 0, game_event.key.keysym.scancode );
		}
		
    }

	
}

void Game::update()
{
	ThePlayer.update();


	SDL_RenderClear(m_pRenderer); // Delete everything from screen

	TheTextureManager.draw( "bg", 0, 0, 640, 480, m_pRenderer, 0 );

	TheTextureManager.drawFrame( "animate", (int)ThePlayer.x, (int)ThePlayer.y, ThePlayer.m_width, ThePlayer.m_height,
		2, ThePlayer.frame, m_pRenderer, 1 );

	SDL_RenderPresent(m_pRenderer); // Draw everything

}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	SDL_Quit();
}