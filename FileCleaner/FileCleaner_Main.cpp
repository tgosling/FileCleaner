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

void printRes(set<string>& s) {
	int fileSetSize = s.size(), MaxValLngth = s.begin()->size(), count = 0;

	//find maxValLngth
	for (auto it = s.begin(); it != s.end(); ++it) {
		if (it->size() > MaxValLngth)
			MaxValLngth = it->size();
	}

	for (auto it = s.begin(); it != s.end(); ++it) {
		if (fileSetSize % 5 == 0)
			cout << setw(3) << right << ++count << ") " << left << setw(MaxValLngth) << *it << endl;
		else
			cout << setw(3) << right << ++count << ") " << left << setw(MaxValLngth) << *it;
		--fileSetSize;
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
	for (const auto& dirEntry : recursive_directory_iterator(p)) {
			fileSet.insert(dirEntry.path().extension().string());
	}

	//print out directory extensions
	cout << "\nDirectory: " << p << endl;
	cout << "Directory File Types: " << endl;
	
	printRes(fileSet);

	cout << "\n\nFolder: " << p << endl;

	int delCount = 0;
	while (usrInput != "x") {
		cout << "\nWhat type of file would you like to remove?" << endl;
		cout << "\tEnter 'x' to end program, 'p' to print files again." << endl;
		//get path and files to delete
		cin >> usrInput;
		cout << "\nYou selected " << usrInput << endl;
		//printRes or find files and remove
		if (usrInput == "p") {
			printRes(fileSet);
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

}