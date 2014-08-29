#include "shader_manager.hpp"
#include "../platform/FileSystem.hpp"

GLubyte* loadFile(std::string filename)
{
	return (GLubyte*) FileSystem::LoadFileContents(filename);
}

ShaderManager* ShaderManager::instance = NULL;

ShaderManager::ShaderManager(void)
{
}

void ShaderManager::_checkCreateInstance()
{
	if (ShaderManager::instance == NULL) 
	{
		ShaderManager::instance = new ShaderManager();
	}
}

ShaderObject* ShaderManager::_createShader( GLenum type, std::string filename )
{
	//get the file contents
	GLubyte* file_contents = loadFile(filename);

	//create and compile our shader
	ShaderObject* shader = new ShaderObject(type);
	shader->Create();
	bool compiled = shader->Compile(filename, file_contents);
    if (!compiled) {
    }

	//add to managed list and return
	shaders.push_back(shader);

	//clean up file contents
	delete file_contents;

	return shader;
}

ShaderObject* ShaderManager::CreateShader( GLenum type, std::string filename )
{
	ShaderManager::_checkCreateInstance();
	return ShaderManager::instance->_createShader(type, filename);
}


