#ifndef MK_WINDOW_H
#define MK_WINDOW_H

#include "../core/core.h"

#include "../events/ApplicationEvent.h"
#include "../math/vec2Int.h"

// Forward declare GLFWwindow to avoid including glfw3.h
struct GLFWwindow;

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

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

		using EventCallbackFn = std::function<void(Event&)>;

		bool ShouldWindowClose(void) const noexcept;
		GLFWwindow* GetGLFWWindow(void) const noexcept { return m_wnd; }

		inline unsigned int GetWidth() const { return m_data.Width; }
		inline unsigned int GetHeight() const { return m_data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) { m_data.EventCallback = callback; }
		virtual void OnEvent(Event& e);
		
		bool OnWindowClose(WindowCloseEvent& e);

	protected:
		virtual void OnInit() {}
		virtual void OnDestroy() {}

		void setShouldWindowClose(bool shouldClose) const noexcept;
		void setCursorMode(unsigned int newCursorState) const noexcept;
		
		void pollWindowEvents(void);
		void swapBuffers(void) const noexcept;

		double GetTime(void);

		GLFWwindow* m_wnd = NULL;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			EventCallbackFn EventCallback;
		};

		WindowData m_data;

	};
}
#endif