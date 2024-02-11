#ifndef MK_ENTRY_POINT_H
#define MK_ENTRY_POINT_H

	#ifdef MK_PLATFORM_WINDOWS

	// To be implemented by user
	extern Murky::Application* Murky::CreateApplication();

	void main(int argc, char** argv)
	{
		Murky::Log::Init();
		MK_ENG_WARN("Initialised Engine Log!");
		int a = 5;

		auto app = Murky::CreateApplication();
		app->Run();
		delete(app);

		MK_ENG_WARN("Closing Engine Log!");
	}

	#endif

#endif

