#include "shader_manager.hpp"

unsigned long getFileLength(std::ifstream& file)
{
	if(!file.good()) return 0;

	unsigned long pos = file.tellg();
	file.seekg(0,std::ios::end);
	unsigned long len = file.tellg();
	file.seekg(std::ios::beg);

	return len;
}

GLubyte* loadFile(const char* filename)
{
	std::ifstream file;
	file.open(filename, std::ios::in);
	unsigned long len = getFileLength(file);

	GLubyte* shaderSrc = (GLubyte*) new char[len+1];
	shaderSrc[len] = 0;  // len isn't always strlen cause some characters are stripped in ascii read...
						 // it is important to 0-terminate the real length later, len is just max possible value...

	unsigned int i=0;
	while (file.good())
	{
		shaderSrc[i++] = file.get();       // get character from file
		if (i>len) i=len;				   // coding guidelines...
	}

	shaderSrc[i] = 0;  // 0 terminate it.
	file.close();

	return shaderSrc;
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

ShaderObject* ShaderManager::_createShader( GLenum type, const char* filename )
{
	//get the file contents
	GLubyte* file_contents = loadFile(filename);

	//create and compile our shader
	ShaderObject* shader = new ShaderObject(type);
	shader->Create();
	shader->Compile(file_contents);

	//add to managed list and return
	shaders.push_back(shader);

	//clean up file contents
	delete file_contents;

	return shader;
}

ShaderObject* ShaderManager::CreateShader( GLenum type, const char* filename )
{
	ShaderManager::_checkCreateInstance();
	return ShaderManager::instance->_createShader(type, filename);
}


