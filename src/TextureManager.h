#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED
#include"includes.h"


class TextureManager
{
public:

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	// draw
	void draw(std::string id, int x, int y, int width, 
		int height, SDL_Renderer* pRenderer, bool horiz_flip);

	// drawframe
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer* pRenderer, bool horiz_flip);

	void clearFromTextureMap(std::string id);

	SDL_RendererFlip flip; // If need horizontal flip

	std::map<std::string, SDL_Texture*> m_textureMap; // крч это Массив m_textureMap[NAMENAMENAME] = текстура

};


#endif // TEXTUREMANAGER_H_INCLUDED