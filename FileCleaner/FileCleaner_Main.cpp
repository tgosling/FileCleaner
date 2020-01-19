#include <iostream>
#include <Windows.h>
#include <filesystem>

using namespace std;
using namespace filesystem;

string getExePath() {
	char result[MAX_PATH];
	return string(result, GetModuleFileName(NULL, result, MAX_PATH));

}

int main(int argc, char* argv[]) {
	int usrInput;
	string usrPath;
	string fileType;

	//prompt user
	cout << "File Cleaner, 2020 (C)" << endl;
	cout << "What type of file would you like to remove?" << endl;
	cout << "1) .torrent" << endl;
	cout << "2) .rar" << endl;
	//get path and files to delete
	cin >> usrInput;
	usrPath = getExePath();
	fileType = ".torrent";
	cout << "\nYou selected " << usrInput << endl;
	filesystem::path p = "D:\\Torries";
	cout << "Folder: " << p << endl;

	//iterate through directory to find files
	for (const auto& dirEntry : recursive_directory_iterator(p)) {
		//check for files
		//if its a specified file, delete it
		if(dirEntry.path().extension() == ".torrent")
			cout << dirEntry.path().string() << endl;
	}

}