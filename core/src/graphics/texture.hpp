	/// Matrix type
#ifndef _TEXTURE_hpp
#define _TEXTURE_hpp

#include "../opengl.h"
#include <string>

namespace Graphics {
	class Texture
	{
	private:
	public:
		GLuint				texture_id;
		std::string			filename;
		bool				loaded;
		unsigned int		texture_width;
		unsigned int		texture_height;
		GLenum				texture_format;

		/// Constructor which create texture-as-buffer. Immediately creates opengl
		/// handle for mapping
		/// @param	width 	The width.
		/// @param	height	The height.
		Texture(GLenum texture_format, int width, int height);

		/// Constructor.
		///
		/// @param	filename	(optional) [in,out] If non-null, filename of the file.
		Texture(std::string filename);

		/// Copy constructor.
		///
		/// @param	source	Source for the.
		Texture(const Texture &source);

		/// Loads the texture into opengl
		void LoadTexture();

		/// Wraps a call to glTexImage2D, using the internal handle
		/// @param [in,out]	data   	If non-null, the data.
		/// @param	data_type	   	Type of the data.
		/// @param	internal_format	The internal format.
		void SetTextureData(void* data, GLenum data_type, GLint internal_format);

		/// Wraps a call to glTexSubImage2D, using the internal handle
		/// @param [in,out]	data   	If non-null, the data.
		/// @param	offset_x	   	The offset x coordinate.
		/// @param	offset_y	   	The offset y coordinate.
		/// @param	width		   	The width.
		/// @param	height		   	The height.
		/// @param	data_type	   	Type of the data.
		/// @param	internal_format	The internal format.
		void SetTextureSubData(void* data, int offset_x, int offset_y, int width, int height, GLenum data_type, GLint internal_format);
	};
}

#endif  // _TEXTURE_hpp