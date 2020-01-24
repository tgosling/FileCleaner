#pragma once
/*!   /file: file_reporting.hpp
*   /author: Tyler Gosling
*	  /date: 23/01/2020
*/
#include <set>
#include <string>
#include <filesystem>
#include <iostream>
#include <iomanip>
using namespace std;
using namespace filesystem;

void dirCheck(std::set<std::string>& s, filesystem::path& p);

void printRes(std::set<std::string>& s);