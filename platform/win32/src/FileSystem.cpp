#ifndef __FileSystem_cpp
#define __FileSystem_cpp

#include <windows.h>
#include "FileSystem.hpp"
#include <vector>
#include <set>

#include <algorithm>

std::vector<void (*)(std::string modified_file)> FileSystem::_change_listeners = std::vector<void (*)(std::string modified_file)>();

std::string FileSystem::GetExecutablePath()
{
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

	return executable;
}

std::string getFullFilePath(std::string resource_file) {
	std::string filepath = FileSystem::GetExecutablePath().append(resource_file);
	return filepath;
}

std::string FileSystem::GetResourceFilePath(std::string resource_file) {
	return getFullFilePath(resource_file);			
}

void FileSystem::NotifyOfDirectoryChanges(std::string directory, void(*call_back)(std::string modified_file))
{
	_change_listeners.push_back(call_back);
}

void FileSystem::ListenForDirectoryChanges(std::string directory)
{
	HANDLE h_Directory = ::CreateFile(
		directory.c_str(),					// pointer to the file name
		FILE_LIST_DIRECTORY,                // access (read/write) mode
		FILE_SHARE_READ						// share mode
		 | FILE_SHARE_WRITE
		 | FILE_SHARE_DELETE,
		NULL,                               // security descriptor
		OPEN_EXISTING,                      // how to create
		FILE_FLAG_BACKUP_SEMANTICS			// file attributes
		 | FILE_FLAG_OVERLAPPED,
		NULL);                              // file with attributes to copy

	if (h_Directory == INVALID_HANDLE_VALUE)
	{
		std::cout << "ERROR: Error opening directory to watch: " << directory << std::endl;
	}

	int nCounter = 0;
    FILE_NOTIFY_INFORMATION strFileNotifyInfo[1024];
    DWORD dwBytesReturned = 0;   

    while(TRUE)
    {
        int count = 0;

		if( ReadDirectoryChangesW ( h_Directory, (LPVOID)&strFileNotifyInfo, sizeof(strFileNotifyInfo), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE, &dwBytesReturned, NULL, NULL) == 0)
        {
        }
        else
        {
			wchar_t filename[MAX_PATH];
			if (strFileNotifyInfo[0].FileNameLength)
            {
                wcsncpy_s(filename, MAX_PATH, strFileNotifyInfo[0].FileName, strFileNotifyInfo[0].FileNameLength / 2);
                filename[strFileNotifyInfo[0].FileNameLength / 2] = 0;
                
				std::wstring ws( filename );
				std::string convert_str( ws.begin(), ws.end());
				std::replace(convert_str.begin(), convert_str.end(), '\\', '/' );
				for(std::vector<void (*)(std::string modified_file)>::iterator it = _change_listeners.begin(); it != _change_listeners.end(); ++it) {
					(*it)(directory + "/" + convert_str);
				}
				
            }
        }
		Sleep(2000);
    }
}

std::vector<File> FileSystem::ListDirectoryContents(std::string directory)
{
	std::vector<File> files;
	std::string search_path = directory;

	if (!search_path.empty() && search_path.back() != '/' && search_path.back() != '\\')
	{
		search_path.append("\\");
	}
	search_path.append("*");

	WIN32_FIND_DATAA find_data;
	HANDLE find_handle = FindFirstFileA(search_path.c_str(), &find_data);
	if (find_handle == INVALID_HANDLE_VALUE)
	{
		return files;
	}

	do
	{
		std::string filename(find_data.cFileName);
		if (filename == "." || filename == "..")
		{
			continue;
		}

		bool is_directory = (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		File f = {filename, is_directory};
		files.push_back(f);
	} while (FindNextFileA(find_handle, &find_data) != 0);

	FindClose(find_handle);
	return files;
}


unsigned char* FileSystem::LoadFileContents(std::string filename, bool path_is_absolute) {
	
	std::string filepath = filename;
	if (!path_is_absolute) {
		filepath = getFullFilePath(filename);
	}

	std::ifstream file;
	file.open(filepath, std::ios::in);
	unsigned long len = getFileLength(file);

	unsigned char* shaderSrc = new unsigned char[len + 1];
	file.read(reinterpret_cast<char*>(shaderSrc), len);
	shaderSrc[file.gcount()] = 0;
	file.close();

	return shaderSrc;
}

#endif  // __FileSystem_cpp
