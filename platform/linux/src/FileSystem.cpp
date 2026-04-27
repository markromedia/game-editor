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
    
    unsigned char* shaderSrc = new unsigned char[len + 1];
    file.read(reinterpret_cast<char*>(shaderSrc), len);
    shaderSrc[file.gcount()] = 0;
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

std::string FileSystem::GetExecutablePath() {
    return std::string("");
}
