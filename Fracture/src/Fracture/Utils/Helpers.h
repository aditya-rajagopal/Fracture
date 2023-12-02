#pragma once
/*!
* @file Helpers.h
* 
* @brief Contains helper functions for the engine to be used internally and by the client application. 
* 
* @author Aditya Rajagaopl
*/


#include <fstream>
#include <string>

namespace  Fracture {

	namespace Utils {
		
		/*!
		* @brief Reads a file and returns the contents as a string
		* 
		* @param const std::string& filePath: The path to the file to read
		* 
		* @return std::string: The contents of the file as a string
		*/
		std::string ReadFile(const std::string& filePath);


		/*!
		* @brief data structure used to store time in seconds
		*/
		struct Timestep
		{
			/*!
			* @brief Constructor for the Timestep struct
			* 
			* @param[in] float time: The time to be stored in the timestep in seconds
			*/
			Timestep(float time = 0)
				:m_Time(time)
			{
			}

			/*!
			* @brief overload for the float operator to the stored time
			* 
			* @return float: The stored time
			*/
			operator float() const { return m_Time; }

			/*!
			* @brief Get the time in seconds
			* 
			* @return float: The time in seconds
			*/
			float GetSeconds() const { return m_Time; }

			/*!
			* @brief Get the time in milliseconds
			* 
			* @return float: The time in milliseconds
			*/
			float GetMilliseconds() const { return m_Time * 1000.0f; }

			/*!
			* @brief Get the time in microseconds
			* 
			* @return float: The time in microseconds
			*/
			float GetMicroseconds() const { return m_Time * 1000.0f * 1000.0f; }
		private:
			float m_Time; /// The time in seconds
		};

	}

}