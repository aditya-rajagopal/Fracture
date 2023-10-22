#pragma once

#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <thread>

#include <iostream>
#include <fstream>
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