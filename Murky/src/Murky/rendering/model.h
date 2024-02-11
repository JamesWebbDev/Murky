#ifndef MK_MODEL_H
#define MK_MODEL_H

#include "mesh.h"

#include <json.hpp>

namespace Murky
{
	using json = nlohmann::json;

	class Shader;

	class MURKY_API Model
	{
	public:

		Model() {};
		Model(const char* file);

		void Draw(Shader& shader, glm::mat4 objMatrix);

		void SetMaterial(const Material& mat, bool keepTextures);

		inline bool IsFileSet() const
		{
			return m_file != "";
		}

		const std::bitset<4> GetPropertyFlags() const;

		inline const char* GetFile() const { return m_file; }

	private: 
		const char* m_file = ""; // name of the file
		std::vector<unsigned char> m_data; // points of all data in the model
		json JSON; // Json object

		std::vector<Mesh> m_meshes;
		std::vector<glm::vec3> translationsMeshes;
		std::vector<glm::quat> rotationsMeshes;
		std::vector<glm::vec3> scalesMeshes;
		std::vector<glm::mat4> matricesMeshes;

		std::vector<std::string> m_loadedTexName;
		std::vector<Texture2D> m_loadedTex;

		void loadMesh(unsigned int indMesh);

		void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

		std::vector<unsigned char> get_data();

		std::vector<glm::vec2> assembleVec2Attribute(json attributes, const char* attribKey);
		std::vector<glm::vec3> assembleVec3Attribute(json attributes, const char* attribKey);
		std::vector<glm::vec4> assembleVec4Attribute(json attributes, const char* attribKey);

		std::vector<float> getFloats(json accessor);
		std::vector<GLuint> getIndices(json accessor);
		Material generateMaterial();

		std::vector<Vertex> assembleVertices
		(
			std::vector<glm::vec3> positions,
			std::vector<glm::vec3> normals,
			std::vector<glm::vec4> tangents,
			std::vector<glm::vec2> texUVs
		);

		std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
		std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
		std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
	};
}

#endif