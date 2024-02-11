#ifndef MK_APPLICATION_H
#define MK_APPLICATION_H

#include "core.h"

namespace Murky
{
	class MURKY_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
	};

	// Declare extern function to be defined by client,
	// basing the entry point in engine
	Application* CreateApplication();
}

#endif