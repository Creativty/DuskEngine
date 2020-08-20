#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>


std::string getFileContents(std::string file_location) {
	std::ifstream input(file_location);
	std::string str((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
	return str;
}