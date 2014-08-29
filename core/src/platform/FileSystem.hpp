/// Declares simple logging class
#ifndef __FILESYSTEM__hpp
#define __FILESYSTEM__hpp

#include <iostream>

class FileSystem {
private:
public:
	/// Loads the file contents into a char array
	/// @param	filename	Filename of the file.
	/// @return	null if it fails, else the file.
	static unsigned char* LoadFileContents(std::string filename);

	/// Returns the path of the provided resource file 
	/// @param	resource_file	Filename of the file.
	/// @return	The file path.
	static std::string GetResourceFilePath(std::string resource_file);
};


#endif  // __FILESYSTEM__hpp