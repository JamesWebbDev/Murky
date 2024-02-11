#ifndef MK_LIGHT_H
#define MK_LIGHT_H

#include "../core/core.h"

#include <glm.hpp>

namespace Murky
{
	// A class for storing light related data in GameObjects
	struct MURKY_API Light
	{
		// Lighting effect intensity
		glm::vec3 ambient = glm::vec3(0.2f), 
				  diffuse = glm::vec3(0.5f), 
				  specular = glm::vec3(1.0f);

		glm::vec3 colour = glm::vec3(1.0f);

		// Relevant Transform data
		glm::vec3 position = glm::vec3(0.0f),
				  direction = glm::vec3(0.0f, 0.0f, 1.0f);

		// Point Light data
		float constant = 1.0f, linear = 0.09f, quadratic = 0.032f;

		// Spot light data
		float innerCutOff = glm::cos(glm::radians(12.5f)), 
			  outerCutOff = glm::cos(glm::radians(17.5f));
	};
}

#endif