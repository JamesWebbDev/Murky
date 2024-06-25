#ifndef MK_CAMERA_H
#define MK_CAMERA_H
#include <glm.hpp>

#include "../core/core.h"

struct GLFWwindow;

namespace Murky
{
	class MURKY_API Camera
	{
	public:

		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f), 
				  Forward =  glm::vec3(0.0f, 0.0f, -1.0f),
				  Up =		 glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 View = glm::mat4(1.0f), Projection = glm::mat4(1.0f);

		void SetNearFar(float zNear, float zFar);
		void SetAspectRatio(float aspectRatio);
		void UpdateView();
		void SetViewportSize(int width, int height);

	protected:
		float n_fov = 45.0f, n_aspect_ratio = 16 / 9, n_z_near = 0.1f, n_z_far = 100;

	private:
		
		void SetPerspectiveProjection();

		Camera* m_ptr = this; // Used to guide where callbacks should be received from
	};
}

#endif