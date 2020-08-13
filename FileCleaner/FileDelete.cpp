/*!   /file: FileDelete.cpp
*   /author: Tyler Gosling
*	  /date: 8/13/2020
*/
#include "file_report.hpp"

using namespace std;
using namespace filesystem;

int fileDelete(std::string usrInput, filesystem::path p) {
	int hold = 0;
	//iterate through directory to find files
	for (const auto& dirEntry : recursive_directory_iterator(p)) {
		//check for files
		//if its a specified file, delete it
		if (dirEntry.path().extension() == usrInput) {
			std::cout << dirEntry.path().string() << endl;
			remove(dirEntry);
			++hold;
			if (remove(dirEntry) != 0)
				std::cout << "Error deleting file" << endl;
		}
	}
	return hold;
}

