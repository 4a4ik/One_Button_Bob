#include"includes.h"
#include"Tiles.h"

// music sounds
Mix_Music *music = NULL;
Mix_Music *victory_music = NULL;

// sound effects
Mix_Chunk *jump_sound = NULL;
Mix_Chunk *dead_sound = NULL;
Mix_Chunk *boomerang_sound = NULL;
Mix_Chunk *explosion_sound = NULL;
Mix_Chunk *boss_dead_sound = NULL;
Mix_Chunk *boss_dead_sound2 = NULL;
Mix_Chunk *boss_jump_sound = NULL;
Mix_Chunk *ghost_sound = NULL;
Mix_Chunk *hurt_sound = NULL;

bool inside_box( int x1, int y1, int x2, int y2, int w2, int h2 )
{
	// If point inside box
	if( x1 >= x2 && x1 <= x2 + w2 && y1 >= y2 && y1 <= y2 + h2 )
		return true;

	return false;
}

bool check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

	//If any of the sides from A are outside of B
    if( bottomA <= topB )
        return false;
    
    if( topA >= bottomB )
        return false;
    
    if( rightA <= leftB )
        return false;
    
    if( leftA >= rightB )
        return false;
    
    //If none of the sides from A are outside B
    return true;
}

bool init_music()
{
	// load music that will be played
	music = Mix_LoadMUS( "files/audio/theme.wav" );
	victory_music = Mix_LoadMUS( "files/audio/victory.wav" );

	// load sound effects
	jump_sound = Mix_LoadWAV( "files/audio/jump.wav" );
	dead_sound = Mix_LoadWAV( "files/audio/dead.wav" );
	explosion_sound = Mix_LoadWAV( "files/audio/explosion.wav" );
	boomerang_sound = Mix_LoadWAV( "files/audio/boomerang.wav" );
	boss_dead_sound = Mix_LoadWAV( "files/audio/boss_dead.wav" );
	boss_dead_sound2 = Mix_LoadWAV( "files/audio/boss_dead2.wav" );
	boss_jump_sound = Mix_LoadWAV( "files/audio/boss_jump.wav" );
	ghost_sound = Mix_LoadWAV( "files/audio/ghost.wav" );
	hurt_sound = Mix_LoadWAV( "files/audio/hurt.wav" );

	if( !music || !hurt_sound || !jump_sound || !dead_sound || !boomerang_sound || !explosion_sound || !boss_dead_sound || !boss_jump_sound || !boss_dead_sound2 || !ghost_sound || !victory_music  )
	{
		printf("Unable to play wav file: %s\n", Mix_GetError());
		return false;
	}

	Mix_PlayMusic( music, -1 );		// Loop forever
	Mix_VolumeMusic(60);			// Volume maximum = MIX_MAX_VOLUME
	Mix_PauseMusic();				// Start with pause so pause music

	return true;
}

void close_music()
{
	 //Free the sound effects
    Mix_FreeChunk( jump_sound );
    Mix_FreeChunk( dead_sound );
    Mix_FreeChunk( explosion_sound );
	Mix_FreeChunk( boss_dead_sound );
    Mix_FreeChunk( ghost_sound );
	Mix_FreeChunk( boomerang_sound );
	Mix_FreeChunk( hurt_sound );
    
    //Free the music
    Mix_FreeMusic( music );
	Mix_FreeMusic( victory_music );
}

bool touches_wall( SDL_Rect &box, std::vector<Tile> &tiles, int &col_box )
{
    //Go through the tiles
	for( int t = 0; t < (int)tiles.size(); t++ )
    {
        //If the collision box touches the wall tile
		if( check_collision( box, tiles[ t ].get_box() ) == true  && ( tiles[ t ].type == WALL || tiles[ t ].type == PLATFORM ))
        {
			// tell what tile it is
			col_box = t;
            return true;
        }
    }
    //If no wall tiles were touched
    return false;
}

bool touches_ledder( SDL_Rect &box, std::vector<Tile> &tiles )
{
    // Go through the tiles
	for( int t = 0; t < (int)tiles.size(); t++ )
    {
        // If the collision box touches the ledder tile
		if( check_collision( box, tiles[ t ].get_box() ) == true  && ( tiles[ t ].type == LEDDER ))
        {
            return true;
        }
    }
    // If no wall tiles were touched
    return false;
}

bool touches_enemy( SDL_Rect &box, std::vector<Tile> &tiles, int &col_box )
{
    // Go through the tiles
	for( int t = 0; t < (int)tiles.size(); t++ )
    {
        // If the collision box touches the enemy tile
		if( check_collision( box, tiles[ t ].get_box() ) == true  && tiles[ t ].type >= ARROW  )
        {
			// tell what tile it is
			col_box = t;
            return true;
        }
    }
    // If no wall tiles were touched
    return false;
}

bool set_tiles( std::vector<Tile> &tiles, int level_num )
{
	// clear all existing tiles before creating new
	tiles.clear();

	// level to load
	std::string level_name = "files/levels/level_00.map";

	level_name[ 19 ] = (char)(level_num / 10 + 48); // ASCII table, numbers start from 48 position
	level_name[ 20 ] = (char)(level_num % 10 + 48); // change string according to level_num

    // The tile offsets
    int x = 0, y = 0, w = 0, h = 0;

	//Open the map
    std::ifstream map( level_name );

	//If the map couldn't be loaded
    if( map == NULL )
    {
		map.close(); // close map
		std::ofstream map2( level_name ); // create map

		map2.close();

		map.open( level_name );
    }

	//Determines what kind of tile will be made
    int tileType = -1;

	//Initialize the tiles
	while( !map.eof() ) // while not end of file
	{
		// read map file 
		map >> x >> y >> w >> h >> tileType;

		//If there was a problem in reading the map
        if( map.bad() == true )
        {
            //Stop loading map
            map.close();
            return false;
        }

		//create new tile
		tiles.push_back( Tile( x, y, w , h, tileType ) );
	}

	tiles.pop_back(); // deletes copy of last tile

    //Close the file
    map.close();

    //If the map was loaded fine
    return true;
}

void save_tiles( std::vector<Tile> &tiles, int level_num  )
{
	std::string level_name = "files/levels/level_00.map";

	level_name[ 19 ] = (char)(level_num / 10 + 48); // ASCII table numbers start from 48 position
	level_name[ 20 ] = (char)(level_num % 10 + 48);

    //The tile offsets
    int x = 0, y = 0, w = 0, h = 0;

	//Open the map
    std::ofstream map( level_name );

	//save the tiles
	for( unsigned int n = 0; n < tiles.size(); n++ ) 
	{
		// save map
		map << tiles[ n ].start_x << " " << tiles[ n ].start_y << " " << tiles[ n ].box.w << " " << tiles[ n ].box.h << " " << tiles[ n ].type << std::endl;
	} 

    //Close the file
    map.close();
}

void change_tiles( std::vector<Tile> &tiles, int x, int y, int type, int action )
{
	// -1 to check it's 1 click or second
	static int start_x = -1;

	// if developer mode and right click pressed
	if ( action == DELETE )
	{
		// go through the tiles
		for( unsigned int n = 0; n < tiles.size(); n++ )
		{
			// if cursor is inside tile
			if( inside_box( x, y, tiles[ n ].start_x, tiles[ n ].start_y, tiles[ n ].box.w, tiles[ n ].box.h ) )
			{
				// delete tile
				tiles.erase( tiles.begin() + n );
				break;
			}
		}
	}
	// Create new tile
	else
	{
		if ( type == WALL )
		{
			if ( start_x == -1 )
			{
				// Floor from here to x
				start_x = x;
			}
			else
			{
				// check if start_x is to the left of x
				if ( start_x > x )
				{
					start_x += x;
					x = start_x - x;
					start_x -= x;
				}

				// 2 floor in LEDDER levels
				if ( y  > 300 )
					y = 340;

				// basic floor
				else
					y = 240;

				// if it's not a point
				if ( start_x - x )
				{
					tiles.push_back( Tile( start_x, y, x - start_x, 5, type ) );
				}
				// restart
				start_x = -1;
			}
		}

		// Just create tiles where player clicks
		else if ( type == TORCH )
			tiles.push_back( Tile( x, y, TORCH_WIDTH * MAGNIFY, TORCH_HEIGHT * MAGNIFY, type ) );

		else if ( type == LAVA )
			tiles.push_back( Tile( x, 412, LAVA_WIDTH * MAGNIFY, LAVA_HEIGHT * MAGNIFY, type ) );

		else if ( type == ARROW )
			tiles.push_back( Tile( x, 140, ARROW_WIDTH * MAGNIFY, ARROW_HEIGHT * MAGNIFY, type ) );

		else if ( type == BOMB )
		{
			if ( y  > 300 )
				y = 300;

			else
				y = 200;

			tiles.push_back( Tile( x, y, BOMB_WIDTH * MAGNIFY, BOMB_HEIGHT * MAGNIFY, type ) );
		}
		else if ( type == BAT )
			tiles.push_back( Tile( x, y, BAT_WIDTH * MAGNIFY, BAT_HEIGHT * MAGNIFY, type ) );

		else if ( type == GHOST )
			tiles.push_back( Tile( x, 285, GHOST_WIDTH * MAGNIFY, GHOST_HEIGHT * MAGNIFY, type ) );

		else if ( type == PLATFORM )
			tiles.push_back( Tile( x, 340, PLATFORM_WIDTH * MAGNIFY, PLATFORM_HEIGHT * MAGNIFY, type ) );

		else if ( type == SPIKE_CEILING )
			tiles.push_back( Tile( 0, 100 -SPIKE_CEILING_HEIGHT * MAGNIFY, SPIKE_CEILING_WIDTH * MAGNIFY, SPIKE_CEILING_HEIGHT * MAGNIFY, type ) );

		else if ( type == LEDDER )
			tiles.push_back( Tile( x, 180, LEDDER_WIDTH * MAGNIFY, LEDDER_HEIGHT * MAGNIFY, type ) );

		else if ( type == ROCK )
			tiles.push_back( Tile( x, 40, ROCK_WIDTH * MAGNIFY, ROCK_HEIGHT * MAGNIFY, type ) );

		else if ( type == BOSS )
			tiles.push_back( Tile( x, 232, BOSS_WIDTH * MAGNIFY, BOSS_HEIGHT * MAGNIFY, type ) );
	}
}

