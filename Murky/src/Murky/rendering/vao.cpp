#include "mkpch.h"

#include "vao.h"

namespace Murky
{
	VAO::VAO(void)
	{
		glGenVertexArrays(1, &ID);
	}
	void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
	{
		VBO.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}
	void VAO::Bind(void)   const { glBindVertexArray(ID); }
	void VAO::Unbind(void) const { glBindVertexArray(0); }
	void VAO::Delete(void) const { glDeleteVertexArrays(1, &ID); }
}