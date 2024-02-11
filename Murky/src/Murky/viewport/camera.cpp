#include "mkpch.h"

#include "camera.h"
#include <gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Murky
{
	void Camera::UpdateView()
	{
		//lookAt( vec3 eye, vec3 center/direction, vec3 camera UP )
		View = glm::lookAt(Position, Position + Forward, Up);
	}
	void Camera::window_resize_callback(GLFWwindow* w, int width, int height)
	{
		glViewport(0, 0, width, height);
		SetAspectRatio((float)width / (float)height);
		
	}
	void Camera::register_window_callbacks(GLFWwindow* window) const
	{
		// Register callbacks to THIS instance of Flying Camera
		glfwSetWindowUserPointer(window, m_ptr);
		auto aspectRatioFunc = [](GLFWwindow* w, int width, int height)
		{
			static_cast<Camera*>(glfwGetWindowUserPointer(w))->window_resize_callback(w, width, height);
		};
		glfwSetFramebufferSizeCallback(window, aspectRatioFunc);
	}
	void Camera::SetNearFar(float zNear, float zFar)
	{
		n_z_far = zFar;
		n_z_near = zNear;
		SetPerspectiveProjection();
	}
	void Camera::SetAspectRatio(float aspectRatio)
	{
		n_aspect_ratio = aspectRatio;
		SetPerspectiveProjection();
	}
	void Camera::SetPerspectiveProjection()
	{
		Projection = glm::perspective(glm::radians(n_fov), n_aspect_ratio, n_z_near, n_z_far);
	}
	
}


