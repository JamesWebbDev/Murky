#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

	#ifdef MK_PLATFORM_WINDOWS

	extern Murky::Application* Murky::CreateApplication();

	void main(int argc, char** argv)
	{
		auto app = Murky::CreateApplication();
		app->Run();
		delete(app);
	}

	#endif

#endif

