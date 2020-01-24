/*!   /file: FileReport.cpp
*   /author: Tyler Gosling
*	  /date: 23/01/2020
*/
#include "file_report.hpp"

using namespace std;
using namespace filesystem;


void dirCheck(std::set<std::string>& s, filesystem::path& p){
	for (const auto& dirEntry : recursive_directory_iterator(p)) {
		s.insert(dirEntry.path().extension().string());
	}
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