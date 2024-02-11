#ifndef MK_INPUT_KEY_H
#define MK_INPUT_KEY_H

#include "../core/core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Murky
{
	class InputKey
	{
		GLuint m_key = 0;
		GLFWwindow* m_wnd;

		bool m_is_pressed = false;
		bool m_is_down_this_frame = false;
		bool m_is_up_this_frame = false;

	public:

		InputKey() { SetKey(GLFW_KEY_0); m_wnd = NULL; };
		InputKey(GLFWwindow& window, GLuint targetKey)
		{
			SetKey(targetKey);
			SetWindow(window);
		}

		inline GLuint GetKey() const { return m_key; }
		inline void SetKey(GLuint targetKey) { m_key = targetKey; }
		inline void SetWindow(GLFWwindow& window) { m_wnd = &window; }

		inline bool GetKeyPressed() const { return m_is_pressed; }
		inline bool GetKeyDown() const { return m_is_down_this_frame; }
		inline bool GetKeyUp() const { return m_is_up_this_frame; }

		MURKY_API void PollKeyInput();
	};
}

#endif