#ifndef MK_CAMERA_FLYING_H
#define MK_CAMERA_FLYING_H

#include "camera.h"

struct GLFWwindow;

namespace Murky
{

	class MURKY_API FlyingCamera : public Camera
	{
	public: 
		
		void set_speed(const float newSpeed);

		void register_input_callbacks(GLFWwindow* window) const;

		void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

		void poll_move_inputs(GLFWwindow* window, const float deltaTime);

		inline bool get_is_frozen() { return m_is_frozen; }
		void set_is_frozen(GLFWwindow* window, bool newState);

	private:

		float m_yaw = -90.0f;
		float m_pitch = 0.0f;
		float m_speed = 20.0f;

		float m_x_last = 400, m_y_last = 300;

		bool m_first_mouse = true;

		bool m_is_frozen = false;

		FlyingCamera* m_ptr = this; // Used to guide where callbacks should be received from

	};
}

#endif