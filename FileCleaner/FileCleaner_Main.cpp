/*!   /file: FileCleaner_Main.cpp
*   /author: Tyler Gosling
*	  /date: 23/01/2020
   /purpose: 
*/

#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <set>
#include <stdio.h>

#include "file_report.hpp"

using namespace std;
using namespace filesystem;

string getExePath() {
	char result[MAX_PATH];
	return string(result, GetModuleFileName(NULL, result, MAX_PATH));
}

int main(int argc, char* argv[]) {
	string usrPath, usrInput, usrConf;
	string fileType;
	set<string> fileSet;

	//prompt user for directory path
	cout << "File Cleaner, 2020 (c)" << endl;
	cout << "Which directory would you like to check? ";
	cin >> usrPath;

	//check directory for file types
	filesystem::path p = usrPath;
	dirCheck(fileSet, p);
	int count = dirCheckCount(fileSet, p);
	//print out directory extensions
	cout << "\nDirectory: " << p << endl;
	cout << "Directory File Types: " << endl;
	printRes(fileSet);
	cout << "\n\nTotal files found: " << count << endl;
	cout << "Folder: " << p << endl;

	int delCount = 0;
	bool usrFlag = false;
	while (usrFlag != true) {
		cout << "\nFile Cleaner options" << endl;
		cout << "--------------------" << endl;
		cout << "1) Enter File Type to delete" << endl;
		cout << "2) Enter 'reset' to reprint remaining files" << endl;
		cout << "3) Enter 'x' to end program" << endl;
		//get path and files to delete
		cout << "Input: ";
		cin >> usrInput;
		cout << "\nYou selected " << usrInput << endl;
		//printRes or find files and remove
		if (usrInput == "reset") {
			fileSet.clear();
			dirCheck(fileSet, p);
			printRes(fileSet);
			cout << "\n";
		}
		else if (usrInput == "x"){
			cout << "\nAre you sure you want to close File Cleaner? (Y/N)" << endl;
			cout << "Input: ";
			cin >> usrConf;
			if (usrConf == "y") {
				cout << "Thanks for using File Cleaner, 2020 (c)" << endl;
				usrFlag = true;
			}
		}
		else {
			cout << "File type selected: " << usrInput << endl;
			cout << "Are you sure you want to delete all files of that type?" << endl;
			cout << "Input: ";
			cin >> usrConf;
			if (usrConf == "y") {
				//iterate through directory to find files
				for (const auto& dirEntry : recursive_directory_iterator(p)) {
					//check for files
					//if its a specified file, delete it
					if (dirEntry.path().extension() == usrInput) {
						cout << dirEntry.path().string() << endl;
						remove(dirEntry);
						++delCount;
						if (remove(dirEntry) != 0)
							cout << "Error deleting file" << endl;
					}
				}
			}
			cout << "Files deleted: " << delCount << endl;
		}
		delCount = 0;
	}
}//end main