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
	void Camera::SetViewportSize(int width, int height)
	{
		glViewport(0, 0, width, height);
		SetAspectRatio((float)width / (float)height);
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
