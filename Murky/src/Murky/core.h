#ifndef CORE_H
#define CORE_H

#ifdef MK_PLATFORM_WINDOWS
	#ifdef MK_BUILD_DLL
		#define MURKY_API __declspec(dllexport)
	#else
		#define MURKY_API __declspec(dllimport)
	#endif
#else 
	#error Murky only suports Windows!
#endif

#endif