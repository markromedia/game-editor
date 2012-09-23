	/// Matrix type
#ifndef _TEXTURE_hpp
#define _TEXTURE_hpp

#include "../opengl.h"
#include <string>

namespace Graphics {
	class Texture
	{
	public:
		GLuint				texture_id;
		std::string			filename;
		bool				loaded;
		unsigned int		texture_width;
		unsigned int		texture_height;

		/// Constructor.
		///
		/// @param	filename	(optional) [in,out] If non-null, filename of the file.
		Texture(std::string filename = "");

		/// Copy constructor.
		///
		/// @param	source	Source for the.
		Texture(const Texture &source);

		/// Loads the texture into opengl
		void LoadTexture();
	};
}

#endif  // _TEXTURE_hpp