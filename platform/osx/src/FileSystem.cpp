#ifndef __FileSystem_cpp
#define __FileSystem_cpp

#include "FileSystem.hpp"
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

unsigned long getFileLength(std::ifstream& file)
{
	if(!file.good()) return 0;

	file.seekg(0,std::ios::end);
	unsigned long len = file.tellg();
	file.seekg(std::ios::beg);

	return len;
}

std::string FileSystem::GetResourceFilePath(std::string resource_file) {
	return resource_file;
}

unsigned char* FileSystem::LoadFileContents(std::string filename) {
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

std::vector<File> FileSystem::ListDirectoryContents(std::string directory) {
    std::vector<File> files;
    
    if (!boost::filesystem::exists(directory)) return files;
    
    if (boost::filesystem::is_directory(directory))
    {
        boost::filesystem::directory_iterator it(directory);
        boost::filesystem::directory_iterator endit;
        while(it != endit)
        {
            if (boost::filesystem::is_regular_file(*it))
            {
                std::string filename = it->path().filename().string();
                File f = {filename, false};
                files.push_back(f);
            }
            if (boost::filesystem::is_directory(*it))
            {
                std::string filename = it->path().filename().string();
                File f = {filename, true};
                files.push_back(f);
            }

            ++it;
        }
    }
    
    return files;
}

void FileSystem::NotifyOfDirectoryChanges(std::string directory, void (*call_back)(std::string modified_file)) {
    
}

void FileSystem::ListenForDirectoryChanges(std::string directory) {
    
}


#endif  // __FileSystem_cpp