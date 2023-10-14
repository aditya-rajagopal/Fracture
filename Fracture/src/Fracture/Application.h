#pragma once


#include "Core.h"


namespace Fracture {

	class FRACTURE_API Application
	{
		public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
} // namespace Fracture

