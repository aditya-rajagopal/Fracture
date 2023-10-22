#include "frpch.h"

#include "Application.h"


namespace Fracture {


	#define PROFILE_TESTING 0

	#if PROFILE_TESTING ==	1
	namespace benchmarks {

		static void Trace()
		{
			FR_PROFILE_FUNCTION();

			for (int i = 0; i < 100; i++)
				FR_CORE_TRACE("Function1 {0}", i);
		}

		static void stdcout()
		{
			FR_PROFILE_FUNCTION();

			for (int i = 0; i < 100; i++)
				std::cout << "Function2 " << i << std::endl;
		}

		static void stdcoutnoendl()
		{
			FR_PROFILE_FUNCTION();

			for (int i = 0; i < 100; i++)
				std::cout << "Function2 " << i << "\n";
		}

		static void RunBenchmarks()
		{
			FR_PROFILE_FUNCTION();
			FR_CORE_TRACE("Running Benchmarks");

			std::thread a([]() { Trace(); });
			std::thread b([]() { stdcout(); });
			stdcoutnoendl();

			a.join();
			b.join();
		}
	}
	#endif

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{

		FR_BEGIN_PROFILE_SESSION("Startup", "../Logs/FractureProfile-Startup.json");
		#if PROFILE_TESTING == 1
		benchmarks::RunBenchmarks();
		#endif
		FR_END_PROFILE_SESSION();
		while (true);
	}

}