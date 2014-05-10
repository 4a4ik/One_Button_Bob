#include"TextureManager.h"

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Texture* pTexture = IMG_LoadTexture(pRenderer, fileName.c_str());

	// everything went ok, add the texture to our list
	if(pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}
	// reaching here means something went wrong
	return false;
}

void TextureManager::draw_rotate(std::string id, int x, int y, int width, int height,
	SDL_Renderer* pRenderer, double angle)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.w = width / MAGNIFY;
	srcRect.h = height / MAGNIFY;

	destRect.w = width;
	destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, SDL_FLIP_NONE);
}


void TextureManager::draw(std::string id, int x, int y, int width, int height,
	SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.w = width / MAGNIFY;
	srcRect.h = height / MAGNIFY;

	destRect.w = width;
	destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(pRenderer, m_textureMap[id], &srcRect, &destRect);
}

void TextureManager::just_draw(std::string id, int x, int y, int width, int height,
	SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(pRenderer, m_textureMap[id], &srcRect, &destRect);
}

void TextureManager::draw_tile(std::string id, int x, int y, int img_width, int img_height, int width, int height,
	SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.w = img_width;
	srcRect.h = img_height;

	destRect.w = width;
	destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(pRenderer, m_textureMap[id], &srcRect, &destRect);
}

void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow,
	int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 5 + ( width / MAGNIFY + 5 ) * currentFrame;
	srcRect.y = 5 + ( height / MAGNIFY + 5 ) * (currentRow - 1);
	srcRect.w = width / MAGNIFY;
	srcRect.h = height / MAGNIFY;

	destRect.w = width;
	destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(pRenderer, m_textureMap[id], &srcRect, &destRect);
}

void TextureManager::draw_explosionFrame(std::string id, int x, int y, int width, int height, int currentRow,
	int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height  * (currentRow - 1);
	destRect.w = srcRect.w = width;
	destRect.h = srcRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(pRenderer, m_textureMap[id], &srcRect, &destRect);
}

void TextureManager::draw_justFrame(std::string id, int x, int y, int width, int height, int currentRow,
	int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 5 + ( width + 5 ) * currentFrame;
	srcRect.y = 5 + ( height + 5 ) * (currentRow - 1);
	destRect.w = srcRect.w = width;
	destRect.h = srcRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(pRenderer, m_textureMap[id], &srcRect, &destRect);
}