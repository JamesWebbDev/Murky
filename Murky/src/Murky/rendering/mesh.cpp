#include "mkpch.h"

#include "mesh.h"
#include "ebo.h"
#include "shader.h"
#include "texture2d.h"

namespace Murky
{
	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Material& material)
	{
		Vertices = vertices;
		Indices = indices;
		Mat = material;

		
		std::bitset<4> flags = GetVarFlags(vertices[0]);


		//*
		std::vector<Vertex_PNC> compactVerts;

		// 1101
		if (flags.test(0) && flags.test(1) && !flags.test(2) && flags.test(3))
		{
			compactVerts.reserve(vertices.size());
			compactVerts.resize(vertices.size());
			for (GLuint i = 0; i < vertices.size(); i++)
			{
				compactVerts[i] = Vertex_PNC
				{
					vertices[i].Position,
					vertices[i].Normal,
					vertices[i].TexCoords
				};
			}
		}

		
		// Generate vertex buffer object
		VAO.Bind();
		VBO VBO;

		if (compactVerts.size() > 0)
		{
			VBO.SetVBO_Vertex_PSC(compactVerts);
		}
		else
		{
			VBO.SetVBO_Vertex(vertices);
		}
		
		//VBO VBO(vertices);
		EBO EBO(indices);

		GLsizeiptr strideLength = sizeof(float) * ((flags.test(0) * 3) + 
												  (flags.test(1) * 3) + 
												  (flags.test(2) * 4) + 
												  (flags.test(3) * 2));
		GLuint layoutIndex = 0; // 0 -> 1 -> 2 -> 3
		GLuint offsetStride = 0; // 0 -> 3 -> 6 -> 10

		
		// Postion
		if (flags.test(0))
		{
			VAO.LinkAttrib(VBO, layoutIndex, 3, GL_FLOAT, strideLength, (void*)(offsetStride * sizeof(float)));
			layoutIndex++;
			offsetStride += 3;
		}

		// Normal
		if (flags.test(1))
		{
			VAO.LinkAttrib(VBO, layoutIndex, 3, GL_FLOAT, strideLength, (void*)(offsetStride * sizeof(float)));
			layoutIndex++;
			offsetStride += 3;
		}

		// Tangents
		if (flags.test(2))
		{
			VAO.LinkAttrib(VBO, layoutIndex, 4, GL_FLOAT, strideLength, (void*)(offsetStride * sizeof(float)));
			layoutIndex++;
			offsetStride += 4;
		}

		// Tex Coords
		if (flags.test(3))
		{
			VAO.LinkAttrib(VBO, layoutIndex, 2, GL_FLOAT, strideLength, (void*)(offsetStride * sizeof(float)));
			layoutIndex++;
			offsetStride += 2;
		}
		
		VAO.Unbind();
		VBO.Unbind();
		EBO.Unbind();
	}
	void Mesh::Draw
	(
		const Shader& shader, 
		glm::mat4 matrix, 
		glm::vec3 translation, 
		glm::quat rotation, 
		glm::vec3 scale)
	{
		
		Mesh::Static_Draw(*this, shader, matrix, translation, rotation, scale);
	}

	void Mesh::Static_Draw(
		Mesh& mesh, 
		const Shader& shader, 
		glm::mat4 matrix, 
		glm::vec3 translation, 
		glm::quat rotation, 
		glm::vec3 scale)
	{
		mesh.Mat.BindTextures();
		mesh.Mat.ApplyAttributesToShader(shader);

		glm::mat4 trans = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 sca = glm::mat4(1.0f);

		trans = glm::translate(trans, translation);
		rot = glm::mat4_cast(rotation);
		sca = glm::scale(sca, scale);

		shader.setMat4("translation", trans);
		shader.setMat4("rotation", rot);
		shader.setMat4("scale", sca);
		shader.setMat4("model", matrix);

		mesh.VAO.Bind();
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh.Indices.size(), GL_UNSIGNED_INT, 0);
		mesh.VAO.Unbind();
	}
	Mesh::~Mesh()
	{
		
	}
}