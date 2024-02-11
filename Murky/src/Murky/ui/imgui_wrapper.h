#ifndef IMGUI_WRAPPER_H
#define IMGUI_WRAPPER_H

#include "../core/core.h"
#include "imgui.h"

struct GLFWwindow;

namespace Murky::MurkyGui
{
	MURKY_API void InitGui(GLFWwindow* window);
	MURKY_API void Shutdown(void);

	MURKY_API void PreRender();
	MURKY_API void PostRender();

	MURKY_API ImVec2 GetContentRegionAvail();
}

#endif