#include "mkpch.h"

#include "ebo.h"

namespace Murky
{
	EBO::EBO(std::vector<GLuint>& indices)
	{
		glGenBuffers(1, &ID);

		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}
	void EBO::Bind(void)   const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }
	void EBO::Unbind(void) const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  }
	void EBO::Delete(void) const { glDeleteBuffers(1, &ID); }
}