#include "graphics/texture_manager.hpp"

#include "graphics/texture.hpp"
#include "logger.hpp"

using namespace graphics;

TextureManager* TextureManager::instance = NULL;

TextureManager::TextureManager()
{
	textures = std::vector<Texture*>();
	textures.reserve(1024);
}

void TextureManager::checkCreateInstance()
{
	if (TextureManager::instance == NULL) 
	{
		TextureManager::instance = new TextureManager();
	}
}

Texture* TextureManager::GetTexture(std::string file)
{
	checkCreateInstance();

	if (instance->textures.size() >= 1024)
	{
		LOG_ERROR("Cannot create anymore textures. At the 1024 max");
		return NULL;
	}

	//create texture and add it to managed list
	Texture* t = new Texture(file);
	instance->textures.push_back(t);
	return instance->textures.back();
}

Texture* TextureManager::CreateTexture(GLenum texture_format, int width, int height)
{
	checkCreateInstance();

	if (instance->textures.size() >= 1024)
	{
		LOG_ERROR("Cannot create anymore textures. At the 1024 max");
		return NULL;
	}

	//create texture and add it to managed list
	Texture* t = new Texture(texture_format, width, height);
	instance->textures.push_back(t);
	return instance->textures.back();
}

void TextureManager::LoadTextures()
{
	checkCreateInstance();
	//load all the textures
	for(std::vector<Texture*>::iterator it = instance->textures.begin(); it != instance->textures.end(); ++it) {
		(*it)->LoadTexture();
	}
}

