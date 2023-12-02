#pragma once
/*!
* @file frpch.h
* 
* @brief Precompiled header file for Fracture engine.
* 
* @see https://docs.microsoft.com/en-us/cpp/build/reference/creating-precompiled-header-files?view=vs-2019
* 
* @author Aditya Rajagopal
*/

#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <thread>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>


#ifdef FR_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include "Fracture\Utils\Log.h"
#include "Fracture\Utils\Instrumentation.h"
#include "Fracture\Utils\Helpers.h"