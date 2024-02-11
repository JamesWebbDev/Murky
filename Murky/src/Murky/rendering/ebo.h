#ifndef MK_EBO_H
#define MK_EBO_H

#include "../core/core.h"

#include <glad/glad.h>

namespace Murky
{
	class MURKY_API EBO
	{
	public:

		// Element Buffer Object ID
		GLuint ID = 0;

		EBO(std::vector<GLuint>& indices);

		void Bind(void) const;
		void Unbind(void) const;
		void Delete(void) const;
	};
}

#endif