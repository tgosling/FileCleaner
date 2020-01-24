#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <set>
#include <map>
#include <stdio.h>

#include "file_report.hpp"

using namespace std;
using namespace filesystem;

string getExePath() {
	char result[MAX_PATH];
	return string(result, GetModuleFileName(NULL, result, MAX_PATH));
}

void dirCheck(set<string>& s, filesystem::path p) {
	for (const auto& dirEntry : recursive_directory_iterator(p)) {
		s.insert(dirEntry.path().extension().string());
	}
}

int main(int argc, char* argv[]) {
	string usrPath, usrInput;
	string fileType;
	set<string> fileSet;

	//prompt user
	cout << "File Cleaner, 2020 (C)" << endl;
	cout << "Which directory would you like to check? ";
	cin >> usrPath;

	//check directory for file types
	filesystem::path p = usrPath;
	dirCheck(fileSet, p);

	//print out directory extensions
	cout << "\nDirectory: " << p << endl;
	cout << "Directory File Types: " << endl;
	printRes(fileSet);

	cout << "\n\nFolder: " << p << endl;

	int delCount = 0;
	while (usrInput != "x") {
		cout << "\nWhat type of file would you like to remove?" << endl;
		cout << "Enter 'x' to end program, 'p' to print files again." << endl;
		//get path and files to delete
		cin >> usrInput;
		cout << "\nYou selected " << usrInput << endl;
		//printRes or find files and remove
		if (usrInput == "p") {
			printRes(fileSet);
			cout << "\n";
		}
		else {
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
			cout << "Files deleted: " << delCount << endl;
		}
		delCount = 0;
	}
}//end main