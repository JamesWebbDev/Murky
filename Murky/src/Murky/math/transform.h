#ifndef MK_TRANSFORM_H
#define MK_TRANSFORM_H

#include "../core/core.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Murky
{
	class MURKY_API Transform
	{
	public:

		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
									// YAW, PITCH, ROLL
		glm::vec4 Rotation = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

		inline glm::mat4 GetModelMatrix() const
		{
			glm::mat4 modelMat = glm::mat4(1.0f);
			// Translate
			modelMat = glm::translate(modelMat, Position);
			// Roll
			modelMat = glm::rotate(modelMat, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			// Pitch
			modelMat = glm::rotate(modelMat, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			// Yaw
			modelMat = glm::rotate(modelMat, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			
			// Scale
			modelMat = glm::scale(modelMat, Scale);

			return modelMat;
		}


	private:
		
	};
}

#endif