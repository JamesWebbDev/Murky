#include "mkpch.h"

#include "vbo.h"

namespace Murky
{
	VBO::VBO()
	{
		glGenBuffers(1, &ID);
	}
	VBO::VBO(std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &ID);
		SetVBO_Vertex(vertices);
	}
	VBO::VBO(std::vector<Vertex_PNC>& vertices)
	{
		glGenBuffers(1, &ID);
		SetVBO_Vertex_PSC(vertices);
	}
	void VBO::Bind(void)   const { glBindBuffer(GL_ARRAY_BUFFER, ID); }
	void VBO::Unbind(void) const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	void VBO::Delete(void) const { glDeleteBuffers(1, &ID); }
	void VBO::SetVBO_Vertex(std::vector<Vertex>& vertices)
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
	}
	void VBO::SetVBO_Vertex_PSC(std::vector<Vertex_PNC>& vertices)
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_PNC) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
	}
}