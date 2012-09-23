#ifndef __TEXTURE_MANAGER_hpp
#define __TEXTURE_MANAGER_hpp

#include <string>
#include <vector>

namespace Graphics {
	//forward declarations
	class Texture;

	class TextureManager
	{
	private:
		/// @summary	The instance.
		static TextureManager* instance;

		/// Check create instance.
		static void checkCreateInstance();

		/// Default constructor.
		TextureManager(void);

		/// @summary	The list of managed textures.
		std::vector<Texture> textures;
	public:
		static Texture* GetTexture(std::string file);

		static void LoadTextures();
	};
}

#endif  // __TEXTURE_MANAGER_hpp