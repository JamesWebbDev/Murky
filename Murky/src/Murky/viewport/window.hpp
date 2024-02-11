#ifndef MK_WINDOW_H
#define MK_WINDOW_H

#include "../core/core.h"

#include "../math/vec2Int.h"

// Forward declare GLFWwindow to avoid including glfw3.h
struct GLFWwindow;

namespace Murky
{
	class MURKY_API Window
	{
	public:
		~Window();

		virtual bool Init(int width, int height, const std::string& title);
		virtual void Tick();
		virtual void Render();
		virtual void PollInputs();

		bool ShouldWindowClose(void) const noexcept;
		Vec2Int GetWindowSize(void) const noexcept;
		GLFWwindow* GetGLFWWindow(void) const noexcept { return m_wnd; }

	protected:
		virtual void OnInit() {}
		virtual void OnDestroy() {}

		void setShouldWindowClose(bool shouldClose) const noexcept;
		void setCursorMode(unsigned int newCursorState) const noexcept;
		
		void pollWindowEvents(void);
		void swapBuffers(void) const noexcept;

		double GetTime(void);

		GLFWwindow* m_wnd = NULL;

	};
}
#endif