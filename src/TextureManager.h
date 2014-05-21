#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include"includes.h"


class TextureManager
{
public:

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer);

	void just_draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer);

	void draw_rotate(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, double angle);

	void draw_tile(std::string id, int x, int y, int img_width, int img_height, int width, int height,
	SDL_Renderer* pRenderer);

	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer* pRenderer);

	void draw_explosionFrame(std::string id, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer* pRenderer);

	void draw_justFrame(std::string id, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer* pRenderer);

	std::map<std::string, SDL_Texture*> m_textureMap; // In basic it's an array m_textureMap[NAMENAMENAME] = texture

};




#endif 