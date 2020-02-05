/*!   /file: file_stats.hpp
*   /author: Tyler Gosling
*	  /date: 23/01/2020
   /purpose: 
*/
#pragma once
#include <string>
#include <set>
#include <filesystem>

struct FileStatStruct {
	std::string extension;
	size_t numFiles;
	//unsigned long long totalByteSize;
	std::set<std::filesystem::path> fileLocations;
};