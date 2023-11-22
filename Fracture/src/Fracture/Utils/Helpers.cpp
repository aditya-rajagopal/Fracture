#include "frpch.h"
#include "Helpers.h"

namespace Fracture {
	namespace Utils {

		std::string ReadFile(const std::string& filePath)
		{
			std::ifstream stream(filePath, std::ios::in, std::ios::binary);
			std::string result;

			if (stream)
			{
				// Read the shader file into the string
				stream.seekg(0, std::ios::end); // go to the end of the file
				result.resize(stream.tellg()); // get length of the file
				stream.seekg(0, std::ios::beg); // go to beginning of the file

				stream.read(&result[0], result.size()); // read into string
				stream.close();
			}
			else
			{
				FR_CORE_ERROR("Could not open file {0}", filePath);
			}

			return result;
		}
	}
}