#include "mkpch.h"

#include "input_key.h"

namespace Murky
{
	void InputKey::PollKeyInput()
	{
		if (glfwGetKey(m_wnd, m_key) == GLFW_PRESS) // IF key is currently down
		{
			m_is_up_this_frame = false;
			// Set Down to true ONLY if not currently pressed
			m_is_down_this_frame = !m_is_pressed;
			m_is_pressed = true;
		}
		else // ELSE key is currently up
		{
			m_is_down_this_frame = false;
			// Set Up to true ONLY if currently pressed
			m_is_up_this_frame = m_is_pressed;
			m_is_pressed = false;
		}
	}
}