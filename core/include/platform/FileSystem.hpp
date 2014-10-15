/// Declares simple logging class
#ifndef __FILESYSTEM__hpp
#define __FILESYSTEM__hpp

#include <iostream>
#include <vector>
#include <fstream>

class FileSystem {
private:
	static std::vector<void (*)(std::string modified_file)> _change_listeners;
public:
	/// Loads the file contents into a char array
	/// @param	filename	Filename of the file.
	/// @return	null if it fails, else the file.
	static unsigned char* LoadFileContents(std::string filename);

	/// Returns the path of the provided resource file 
	/// @param	resource_file	Filename of the file.
	/// @return	The file path.
	static std::string GetResourceFilePath(std::string resource_file);

	/// Notifies an of directory changes.
	/// @param	directory		 	Pathname of the directory.
	/// @param [in,out]	call_back	If non-null, the call back.
	static void NotifyOfDirectoryChanges(std::string directory, void (*call_back)(std::string modified_file));

	/// Listen for directory changes.
	static void ListenForDirectoryChanges(std::string directory);

	/// Gets a file length.
	/// @param [in,out]	file	The file.
	/// @return	The file length.
	static inline unsigned long getFileLength(std::ifstream& file) {
		if(!file.good()) return 0;

		file.seekg(0,std::ios::end);
		unsigned long len = file.tellg();
		file.seekg(std::ios::beg);

		return len;
	}
};


#endif  // __FILESYSTEM__hpp