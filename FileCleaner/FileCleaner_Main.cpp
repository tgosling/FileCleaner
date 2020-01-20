#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <set>
#include <map>
#include <stdio.h>

using namespace std;
using namespace filesystem;

string getExePath() {
	char result[MAX_PATH];
	return string(result, GetModuleFileName(NULL, result, MAX_PATH));

}

int main(int argc, char* argv[]) {
	string usrPath, usrFile;
	string fileType;
	map<string, int> fileMap;
	set<string> fileSet;

	//prompt user
	cout << "File Cleaner, 2020 (C)" << endl;
	cout << "Which directory would you like to check? ";
	cin >> usrPath;

	//check directory for file types
	filesystem::path p = usrPath;
	int count = 0, torCount = 0;
	for (const auto& dirEntry : recursive_directory_iterator(p)) {
		++count;
			fileSet.insert(dirEntry.path().extension().string());
			fileMap.insert(pair<string,int>(dirEntry.path().extension().string(), count));
	}

	//print out directory extensions
	count = 0;
	cout << "\nDirectory: " << p << endl;
	cout << "Directory File Types: " << endl;
	for (auto it = fileSet.begin(); it != fileSet.end(); ++it) {
		cout << ++count << ") " << *it << "\t" << ++count << ") " << *++it << "\t" << ++count << ") " << *++it << endl;
	}

	cout << "\nFolder: " << p << endl;
	cout << "What type of file would you like to remove?" << endl;

	//get path and files to delete
	cin >> usrFile;
	fileType = ".torrent";
	cout << "\nYou selected " << usrFile << endl;
	
	
	int delCount = 0;
	//iterate through directory to find files
	for (const auto& dirEntry : recursive_directory_iterator(p)) {
		//check for files
		//if its a specified file, delete it
		if (dirEntry.path().extension() == usrFile) {
			cout << dirEntry.path().string() << endl;
			remove(dirEntry);
			++delCount;
			if (remove(dirEntry) != 0)
				cout << "Error deleting file" << endl;
		}
	}

	cout << "Files deleted: " << delCount << endl;

}