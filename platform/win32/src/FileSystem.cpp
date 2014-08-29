#ifndef __FileSystem_cpp
#define __FileSystem_cpp

#include <windows.h>
#include "FileSystem.hpp"
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>

std::string getFullFilePath(std::string resource_file) {
	char ownPth[MAX_PATH]; 
	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL)
	{
		// When passing NULL to GetModuleHandle, it returns handle of exe itself
		GetModuleFileName(hModule,ownPth, (sizeof(ownPth))); 
	}
	std::string executable(ownPth); 
	std::replace(executable.begin(), executable.end(), '\\', '/' );
	unsigned found = executable.find_last_of("/\\");
	executable = executable.substr(0, found).append("/");
	std::string filepath = executable.append(resource_file);

	return filepath;
}

unsigned long getFileLength(std::ifstream& file)
{
	if(!file.good()) return 0;

	file.seekg(0,std::ios::end);
	unsigned long len = file.tellg();
	file.seekg(std::ios::beg);

	return len;
}

std::string FileSystem::GetResourceFilePath(std::string resource_file) {
	return getFullFilePath(resource_file);			
}

unsigned char* FileSystem::LoadFileContents(std::string filename) {
	std::string filepath = getFullFilePath(filename);

	std::ifstream file;
	file.open(filepath, std::ios::in);
	unsigned long len = getFileLength(file);

	unsigned char* shaderSrc = (unsigned char*) new char[len+1];
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

#endif  // __FileSystem_cpp