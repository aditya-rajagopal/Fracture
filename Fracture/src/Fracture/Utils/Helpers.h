#pragma once

#include <fstream>
#include <string>

namespace  Fracture {

	namespace Utils {
		
		/*
		* Reads a file and returns the contents as a string
		* 
		* @param filePath: The path to the file to read
		*/
		std::string ReadFile(const std::string& filePath);

	}

}