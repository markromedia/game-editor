/// @file	src\graphics\shader_manager.hpp
///
/// Declares the shader manager class.
#ifndef __SHADER__MANAGER_hpp
#define __SHADER__MANAGER_hpp

#include "../opengl.h"
#include <vector>
#include <set>
#include <fstream>
#include "gllogger.hpp"
#include "shader_object.hpp"

class ShaderManager 
{
private:
	/// @summary	The instance.
	static ShaderManager* instance;

	/// Checks to see if instance is not created. creates it then
	static void _checkCreateInstance();

	/// @summary	The shaders currently managed.
	std::vector<ShaderObject*> shaders;

	/// Default constructor.
	ShaderManager(void);

	/// internal version of CreateShader
	ShaderObject* _createShader(GLenum type, std::string filename);
public:
	/// Creates a shader from the provided file handle
	///
	/// @param	type		The type.
	/// @param	filename	Filename of the file.
	///
	/// @return	The new shader.
	static ShaderObject* CreateShader(GLenum type, std::string filename);
};

#endif  // __SHADER__MANAGER_hpp