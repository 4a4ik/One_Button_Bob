#include "Game.h"
#include"TextureManager.h"
#include"Player.h"
#include"Tiles.h"
#include"includes.h"
#include"Score.h"
#include"Boomerang.h"
#include"Force_meter.h"
#include"Explosion.h"

#define BOSS_X 507
#define BOSS_Y 232
#define EXPLOSIONS_NUM 10

std::vector<Explosion> explosions;

TextureManager TheTextureManager; // working with images
Player ThePlayer( 0, 287 );

Force_meter Fmeter;

int boss_hp;
bool ENDING = false;
bool FINALE = false;

std::string names[] = {
	"tiles", "torch", "lava", "ledder", "arrow", "bomb", "bat", "ghost", "platform", "spike_ceiling", "rock", "boss"
};

const int map_types[] = {
	0, CLICK_SHOOT, CLICK_STOP, CLICK_ACCELERATE, 
	CLICK_LEDDER, CLICK_SHOOT, CLICK_JUMP_STOP, CLICK_STOP, CLICK_JUMP, CLICK_LEDDER, CLICK_ACCELERATE, CLICK_BOSS, END
};

Boomerang TheBoomerang( 38, 305 );

Score myScore;

std::vector<Tile> tiles;

bool DEVELOPER = false;
int DEV_TYPE = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	for( int n = 0; n < EXPLOSIONS_NUM; n++)
		explosions.push_back( Explosion( BOSS_X, BOSS_Y ));

	level = 1;
	clicks = 0;
	pause = true;

	level_name = "level_01";

	map_type = map_types[ level ];

	int flags = 0;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";

		//Initialize SDL_mixer  AUDIO
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
			printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", TTF_GetError() );
            return false;
        }

		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if(m_pWindow != 0) // window init success
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
			if(m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

				// to load
				if(!TheTextureManager.load("files/img/hero.png", "hero", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_01.png", "level_01", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_02.png", "level_02", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_03.png", "level_03", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_04.png", "level_04", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_05.png", "level_05", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_06.png", "level_06", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_07.png", "level_07", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_08.png", "level_08", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_09.png", "level_09", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_10.png", "level_10", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/level_11.png", "level_11", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/end.png", "end", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/tiles.png", "tiles", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/icons.png", "icons", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/icons_fon.png", "icons_fon", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/torch.png", "torch", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/lava.png", "lava", m_pRenderer))
					return false;
				
				if(!TheTextureManager.load("files/img/arrow.png", "arrow", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/bomb.png", "bomb", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/dev_tiles.png", "dev_tiles", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/force_meter.png", "force_meter", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/red.png", "red", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/boomerang.png", "boomerang", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/bat.png", "bat", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/ghost.png", "ghost", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/platform.png", "platform", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/spike_ceiling.png", "spike_ceiling", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/ledder.png", "ledder", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/rock.png", "rock", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/boss.png", "boss", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/life_bar.png", "life_bar", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/explosion.png", "explosion", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/font.png", "font", m_pRenderer))
					return false;

				if(!TheTextureManager.load("files/img/pause.png", "pause", m_pRenderer))
					return false;
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; 
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; 
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false;
	}
	
	if( init_music() )
		std::cout << "Music ok! \n";
	else
		std::cout << "Music FAIL! \n";

	if( !set_tiles( tiles, level  ) )
		return false;

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
			if(!DEVELOPER && !ENDING)
			{
				ThePlayer.handle_input( 1, game_event.key.keysym.scancode, map_type );
			}

			switch (game_event.key.keysym.scancode)
			{
				case SDL_SCANCODE_ESCAPE: Running = false; break;
				case SDL_SCANCODE_1: DEVELOPER = !DEVELOPER; break;
			}
		}

		else if ( game_event.type == SDL_KEYUP )
		{
			if (!DEVELOPER && !ENDING)
			{
				ThePlayer.handle_input( 0, game_event.key.keysym.scancode, map_type );
			}
		}
		else if ( game_event.type == SDL_MOUSEBUTTONDOWN && !DEVELOPER && !ENDING && game_event.button.button == SDL_BUTTON_LEFT )
		{
			ThePlayer.handle_input( 3, game_event.key.keysym.scancode, map_type  );
		}

		else if ( game_event.type == SDL_MOUSEBUTTONUP && !DEVELOPER && !ENDING )
		{
			if ( game_event.button.button == SDL_BUTTON_LEFT )
			{
				if ( inside_box( game_event.button.x, game_event.button.y, PAUSE_X, PAUSE_Y, PAUSE_W * MAGNIFY, PAUSE_H * MAGNIFY ) )
				{
					pause = !pause;
					if ( !pause )			Mix_ResumeMusic();
					else					Mix_PauseMusic();
				}

				else if ( inside_box( game_event.button.x, game_event.button.y, SPEAKER_X, SPEAKER_Y, SPEAKER_W * MAGNIFY, SPEAKER_H * MAGNIFY ) )
				{
					if ( Mix_PausedMusic() )		Mix_ResumeMusic();
					else							Mix_PauseMusic();
				}

				else if (!pause && !FINALE)
				{
					TheBoomerang.handle_input( map_type );
					ThePlayer.handle_input( 4, game_event.key.keysym.scancode, map_type );
					clicks++;
				}
				else if (pause && !FINALE)	
				{
					pause = false;
					Mix_ResumeMusic();
				}
			}
		}

		else if( game_event.type == SDL_MOUSEBUTTONUP && DEVELOPER )
		{
			switch (game_event.button.button)
			{
				case SDL_BUTTON_RIGHT: change_tiles( tiles, game_event.button.x, game_event.button.y, DEV_TYPE, DELETE); break;
				case SDL_BUTTON_LEFT: change_tiles( tiles, game_event.button.x, game_event.button.y, DEV_TYPE, PLACE); break;
			}
		}

		else if( game_event.type == SDL_MOUSEWHEEL )
		{
			if ( game_event.wheel.y > 0 )
			{
				if ( DEV_TYPE != TILE_TYPES )
				{
					DEV_TYPE++; 
				}
			}
			else if ( game_event.wheel.y < 0 )
			{
				if ( DEV_TYPE != 0 )
				{
					DEV_TYPE--; 
				}
			}
		}
    }
}

void Game::update()
{
	if (!DEVELOPER && !pause)
	{
		ThePlayer.update( tiles, map_type );

		if (!FINALE)
			TheBoomerang.update( tiles, ThePlayer.box.x, ThePlayer.dead, map_type );

		if (map_type != CLICK_BOSS)
			Fmeter.update( ThePlayer.box.x, ThePlayer.box.y, (int)ThePlayer.force, map_type );
		else
			Fmeter.update( ThePlayer.box.x, ThePlayer.box.y, boss_hp, map_type );
	
		if (map_type == CLICK_BOSS)
		{
			for( int n = 0; n < EXPLOSIONS_NUM; n++)
				explosions[ n ].update();
		}
	}

	myScore.update( map_type, clicks );


	
	SDL_RenderClear( m_pRenderer ); // Delete everything from screen

	TheTextureManager.draw( level_name, ThePlayer.level_x, ThePlayer.level_y, SCREEN_WIDTH, SCREEN_HEIGHT, m_pRenderer );

	if (map_type == END)
		TheTextureManager.just_draw( "end", 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT, m_pRenderer );
	
	for( unsigned int n = 0; n < tiles.size(); n++ )
	{
		if ( ThePlayer.restart )
			tiles[ n ].restart();

		if ( !pause && !DEVELOPER )
			tiles[ n ].update( ThePlayer.box.x, ThePlayer.dead );

		// draw collide boxes if developer mode active
		if ( DEVELOPER )
			TheTextureManager.draw_tile( names[ 0 ], tiles[ n ].start_x, tiles[ n ].start_y, 1, 1, tiles[ n ].box.w, tiles[ n ].box.h, m_pRenderer);


		else if ( tiles[ n ].type == BAT )
			TheTextureManager.drawFrame( names[ tiles[ n ].type ], tiles[ n ].box.x + ThePlayer.level_x, tiles[ n ].box.y - ThePlayer.frame * 3 + ThePlayer.level_y, tiles[ n ].box.w, tiles[ n ].box.h, tiles[ n ].frame_line, tiles[ n ].frame, m_pRenderer);

		else if ( tiles[ n ].type != WALL )
			TheTextureManager.drawFrame( names[ tiles[ n ].type ], tiles[ n ].box.x + ThePlayer.level_x, tiles[ n ].box.y + ThePlayer.level_y, tiles[ n ].box.w, tiles[ n ].box.h, tiles[ n ].frame_line, tiles[ n ].frame, m_pRenderer);

		if ( tiles[ n ].shake )
		{
			ThePlayer.shake = 25;
			tiles[ n ].shake = false;
		}
		if ( tiles[ n ].type == BOSS )
		{
			boss_hp = tiles[ n ].hp;

			if ( boss_hp <= 0 )		
			{
				ENDING = true;
				FINALE = true;
				ThePlayer.shake = 20;

				Mix_PauseMusic();
			}

			if ( tiles[ n ].dead )			
				ENDING = false;
		}
	}

	TheTextureManager.draw( "icons_fon", 0, 0, SCREEN_WIDTH, 12 * MAGNIFY, m_pRenderer );

	if ( map_type != END )
	{
		if ( map_type == CLICK_BOSS )
		{
			TheTextureManager.draw( "life_bar", Fmeter.x + ThePlayer.level_x, Fmeter.y + ThePlayer.level_y, LIFE_METER_W * MAGNIFY, LIFE_METER_H * MAGNIFY, m_pRenderer);
			TheTextureManager.draw( "red", Fmeter.r_x + ThePlayer.level_x, Fmeter.r_y + ThePlayer.level_y, Fmeter.width * MAGNIFY, ( LIFE_METER_H - 4 ) * MAGNIFY, m_pRenderer);
		}
		else if (map_type == CLICK_JUMP || map_type == CLICK_JUMP_STOP)
		{
			TheTextureManager.draw( "force_meter", Fmeter.x + ThePlayer.level_x, Fmeter.y + ThePlayer.level_y, FORCE_METER_W * MAGNIFY, FORCE_METER_H * MAGNIFY, m_pRenderer);
			TheTextureManager.draw( "red", Fmeter.r_x + ThePlayer.level_x, Fmeter.r_y + ThePlayer.level_y, Fmeter.width * MAGNIFY, ( FORCE_METER_H - 2 ) * MAGNIFY, m_pRenderer);
		}

		for( int n = 0; n < EXPLOSIONS_NUM; n++)
			TheTextureManager.draw_explosionFrame( "explosion", explosions[ n ].box.x + ThePlayer.level_x, explosions[ n ].box.y + ThePlayer.level_y, explosions[ n ].box.w, explosions[ n ].box.h,
				explosions[ n ].frame_line, explosions[ n ].frame, m_pRenderer );
	
		TheTextureManager.drawFrame( "hero", ThePlayer.box.x + ThePlayer.level_x, ThePlayer.box.y - ThePlayer.frame + ThePlayer.level_y, ThePlayer.box.w, ThePlayer.box.h,
			ThePlayer.frame_line, ThePlayer.frame, m_pRenderer );

		if ( boss_hp > 0 && map_type == CLICK_BOSS )
			TheTextureManager.draw_rotate( "boomerang", TheBoomerang.box.x + ThePlayer.level_x, TheBoomerang.box.y + ThePlayer.level_y, 2 * MAGNIFY, 5 * MAGNIFY, m_pRenderer, TheBoomerang.angle );
		else if ( map_type != CLICK_BOSS )
			TheTextureManager.draw_rotate( "boomerang", TheBoomerang.box.x + ThePlayer.level_x, TheBoomerang.box.y + ThePlayer.level_y, 2 * MAGNIFY, 5 * MAGNIFY, m_pRenderer, TheBoomerang.angle );
	}
	
	if (DEVELOPER)
		TheTextureManager.drawFrame( "dev_tiles", 300, 10, 10 * MAGNIFY, 10 * MAGNIFY, 1, DEV_TYPE, m_pRenderer);

	TheTextureManager.draw( "icons", SPEAKER_X, SPEAKER_Y, 22 * MAGNIFY, SPEAKER_H * MAGNIFY, m_pRenderer);

	// SCORE CLICKS
	TheTextureManager.draw_justFrame( "font", myScore.x1 + ThePlayer.level_x, myScore.y + ThePlayer.level_y, myScore.w, myScore.h,
			1, myScore.first, m_pRenderer );
	if (clicks >= 10)
		TheTextureManager.draw_justFrame( "font", myScore.x2 + ThePlayer.level_x, myScore.y + ThePlayer.level_y, myScore.w, myScore.h,
				1, myScore.second, m_pRenderer );
	if (clicks >= 100)
		TheTextureManager.draw_justFrame( "font", myScore.x3 + ThePlayer.level_x, myScore.y + ThePlayer.level_y, myScore.w, myScore.h,
				1, myScore.third, m_pRenderer );
	if (clicks >= 1000)
		TheTextureManager.draw_justFrame( "font", myScore.x4 + ThePlayer.level_x, myScore.y + ThePlayer.level_y, myScore.w, myScore.h,
				1, myScore.fourth, m_pRenderer );

	if (pause)
		TheTextureManager.just_draw( "pause", 0, 0, 640, 480, m_pRenderer);

	SDL_RenderPresent(m_pRenderer); // Draw everything

	//If level restarted every tile restarted in cycle, so we can just change bool
	ThePlayer.restart = false;

	if ( ThePlayer.box.x >= SCREEN_WIDTH - ThePlayer.box.w )
	{
		save_tiles( tiles, level );
		level++;

		ThePlayer.restart = true;
		
		if( !set_tiles( tiles, level  ) )
			printf( "Problem loading map number: %i\n", level );

		level_name[ 6 ] = (char)(level / 10 + 48); // ASCII table numbers start from 48 position
		level_name[ 7 ] = (char)(level % 10 + 48);

		map_type = map_types[ level ];

		if (map_type == END)
		{			
			Mix_VolumeMusic( MIX_MAX_VOLUME ); 
			Mix_PlayMusic( victory_music, -1 );    
		}
	}

}

void Game::clean()
{
	std::cout << "cleaning game\n";

	save_tiles( tiles, level );

	close_music();
		
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	//Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
	SDL_Quit();
}