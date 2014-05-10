#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include"includes.h"


class TextureManager
{
public:

	// img.png , ID to find it, where to render pRenderer == screen
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer); // load image

	// draw
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer);

	void just_draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer);

	void draw_rotate(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, double angle);

	void draw_tile(std::string id, int x, int y, int img_width, int img_height, int width, int height,
	SDL_Renderer* pRenderer);

	// drawframe
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer* pRenderer);

	void draw_explosionFrame(std::string id, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer* pRenderer);

	void draw_justFrame(std::string id, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer* pRenderer);

	void clearFromTextureMap(std::string id);

	std::map<std::string, SDL_Texture*> m_textureMap; // крч это Массив m_textureMap[NAMENAMENAME] = текстура

};



#endif // TEXTUREMANAGER_H_INCLUDED