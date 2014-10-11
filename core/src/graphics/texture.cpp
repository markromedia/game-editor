#include "graphics/texture.hpp"

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "graphics/gllogger.hpp"
#include "logger.hpp"
#include "platform/FileSystem.hpp"

using namespace Graphics;

Texture::Texture(GLenum texture_format, int width, int height)
{
	this->texture_format = texture_format;
	this->texture_width = width;
	this->texture_height = height;
	this->loaded = true; //incase someone tried to call LoadTexture()
	glGenTextures( 1, &texture_id );
}

Texture::Texture(std::string filename) {
	this->filename = filename;	
	this->loaded = false;
}

Texture::Texture(const Texture &source)
{
	this->filename = source.filename;
	this->loaded = source.loaded;
}

void Texture::LoadTexture()
{
	if (this->loaded)
	{
		return;
	}

	SDL_Surface *surface;	// This surface will tell us the details of the image
	GLint  nOfColors;

	bool success = false;
	if (filename.find(".bmp", 0) == std::string::npos)
	{
		success = (surface = IMG_Load(FileSystem::GetResourceFilePath(filename).c_str())) ;	
	} else {
		success = (surface = SDL_LoadBMP(FileSystem::GetResourceFilePath(filename).c_str())) ;	
	}
	
	if (success) { 

		// Check that the image's width is a power of 2
		if ( (surface->w & (surface->w - 1)) != 0 ) {
			LOG_ERROR("warning: texture width is not a power of 2\n");
		}

		// Also check if the height is a power of 2
		if ( (surface->h & (surface->h - 1)) != 0 ) {
			LOG_ERROR("warning: texture height is not a power of 2\n");
		}

		// save the width and the height
		texture_width = surface->w;
		texture_height = surface->h;

		// get the number of channels in the SDL surface
		nOfColors = surface->format->BytesPerPixel;
		if (nOfColors == 4)     // contains an alpha channel
		{
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA;
		} else if (nOfColors == 3)     // no alpha channel
		{
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
			else
				texture_format = GL_BGR;
		} else {
            texture_format = 0;
			LOG_ERROR("warning: the image is not truecolor..  this will probably break\n");
			// this error should not go unhandled
		}

		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture_id );

		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture_id );

		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0,
			texture_format, GL_UNSIGNED_BYTE, surface->pixels );
		CHECK_GL_ERROR();
	} 
	else {
		std::string s = "SDL could not load " + filename;
		LOG_ERROR(s.c_str());
		CHECK_GL_ERROR();

		SDL_Quit();
	}    

	// Free the SDL_Surface only if it was successfully created
	if ( surface ) { 
		SDL_FreeSurface( surface );
	}
}

void Texture::SetTextureData(void* data, GLenum data_type, GLint internal_format)
{
	glBindTexture( GL_TEXTURE_2D, texture_id );

	// Set the texture's stretching properties
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, internal_format, this->texture_width, this->texture_height, 0,
		texture_format, data_type, data );
	CHECK_GL_ERROR();
}

void Texture::SetTextureSubData(void* data, int offset_x, int offset_y, int width, int height, GLenum data_type, GLint internal_format)
{
	glBindTexture( GL_TEXTURE_2D, texture_id );

	// Set the texture's stretching properties
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexSubImage2D(GL_TEXTURE_2D, 0, offset_x, offset_y, width, height, internal_format, data_type, data);
}