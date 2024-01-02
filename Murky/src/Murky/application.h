#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

namespace Murky
{
	class MURKY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Declare extern function to be defined by client,
	// basing the entry point in engine
	Application* CreateApplication();
}

#endif