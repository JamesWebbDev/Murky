#include "mkpch.h"

#include "camera_flying.h"


#include <GLFW/glfw3.h>

namespace Murky
{
	void FlyingCamera::set_speed(const float newSpeed)
	{
		m_speed = newSpeed;
	}

	void FlyingCamera::RotateCamera(MouseMovedEvent& e)
	{
		MK_ENG_TRACE("Rotating!");
		if (m_is_frozen)
			return;

		if (m_first_mouse)
		{
			m_x_last = e.GetX();
			m_y_last = e.GetY();
			m_first_mouse = false;
		}

		float xoffset = e.GetX() - m_x_last;
		float yoffset = m_y_last - e.GetY(); // reversed since y-coordinates range from bottom to top
		m_x_last = e.GetX();
		m_y_last = e.GetY();
		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_yaw += xoffset;
		m_pitch += yoffset;

		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		direction.y = sin(glm::radians(m_pitch));
		direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		Forward = glm::normalize(direction);
	}

	void FlyingCamera::ZoomCamera(MouseScrolledEvent& e)
	{
		MK_ENG_TRACE("Zooming!");
		if (m_is_frozen)
			return;

		n_fov -= e.GetYOffset();
		if (n_fov < 1.0f)
			n_fov = 1.0f;
		if (n_fov > 45.0f)
			n_fov = 45.0f;
	}

	void FlyingCamera::poll_move_inputs(GLFWwindow* window, const float deltaTime)
	{
		if (m_is_frozen)
			return;

		// Camera Movement
		float cameraSpeed = m_speed * deltaTime; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Position += cameraSpeed * Forward;
		}
			
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Position -= cameraSpeed * Forward;
		}
			
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Position -= glm::normalize(glm::cross(Forward, Up)) * cameraSpeed;
		}
			
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Position += glm::normalize(glm::cross(Forward, Up)) * cameraSpeed;
		}
			
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			Position += cameraSpeed * Up;
		}
			
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			Position -= cameraSpeed * Up;
		}
			
	}
	void FlyingCamera::set_is_frozen(GLFWwindow* window, bool newState)
	{
		m_is_frozen = newState;

		if (!m_is_frozen)
		{
			// Prevent camera from SNAPPING away its existing look direction
			double xPos, yPos;
			glfwGetCursorPos(window, &xPos, &yPos);
			m_x_last = xPos;
			m_y_last = yPos;
		}
	}
	
}