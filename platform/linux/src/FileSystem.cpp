#include "FileSystem.hpp"
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>

std::string FileSystem::GetResourceFilePath(std::string resource_file) {
	return resource_file;
}

unsigned char* FileSystem::LoadFileContents(std::string filename, bool path_is_absolute) {
    std::ifstream file;
    file.open(filename, std::ios::in);
    unsigned long len = getFileLength(file);
    
    unsigned char* shaderSrc = (unsigned char*) new char[len+1];
    shaderSrc[len] = 0;  // len isn't always strlen cause some characters are stripped in ascii read...
    // it is important to 0-terminate the real length later, len is just max possible value...
    
    unsigned int i=0;
    while (file.good())
    {
        shaderSrc[i++] = file.get();       // get character from file
        if (i>len) i=len;                   // coding guidelines...
    }
    
    shaderSrc[i] = 0;  // 0 terminate it.
    file.close();
    
    return shaderSrc;
}

void FileSystem::ListenForDirectoryChanges(std::string directory) {

}

void FileSystem::NotifyOfDirectoryChanges(std::string directory, void (*call_back)(std::string)) {

}

std::vector<File> FileSystem::ListDirectoryContents(std::string directory) {
    return std::vector<File>();
}
