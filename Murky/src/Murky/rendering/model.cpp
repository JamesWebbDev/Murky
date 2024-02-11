#include "mkpch.h"

#include "model.h"
#include "shader.h"
#include "texture2d.h"

#include <gtc/type_ptr.hpp>
#include <base64.h>

namespace Murky
{
	Model::Model(const char* file)
	{
		MK_TRACE("Before get_file_contents");
		std::string text = Shader::get_file_contents(file);
		MK_TRACE("Before json::parse");
		JSON = json::parse(text);

		m_file = file;
		MK_TRACE("Before get_file");
		m_data = get_data();

		MK_TRACE("Before traverseNode");
		// Load all meshes in model
		traverseNode(0); // TODO: change back to 0
	}

	void Model::Draw(Shader& shader, glm::mat4 objMatrix)
	{
		for (unsigned int i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i].Draw(shader, matricesMeshes[i] * objMatrix, translationsMeshes[i], rotationsMeshes[i], scalesMeshes[i]);
		}
	}

	void Model::SetMaterial(const Material& mat, bool keepTextures)
	{
		for (unsigned int i = 0; i < m_meshes.size(); i++)
		{
			std::vector<Texture2D> textures = m_meshes[i].Mat.Textures;
			m_meshes[i].Mat = mat;
			m_meshes[i].Mat.Textures = textures;
		}
	}

	const std::bitset<4> Model::GetPropertyFlags() const
	{
		MK_ENG_INFO("Trying to get first 'Mesh' at path {0}", m_file);
		std::bitset<4> flags = Mesh::GetVarFlags(m_meshes[0].Vertices[0]);
		return flags;
	}

	void Model::loadMesh(unsigned int indMesh)
	{
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec4> tangents;
		std::vector<glm::vec2> texUVs;

		json attributes = JSON["meshes"][indMesh]["primitives"][0]["attributes"];

		positions = assembleVec3Attribute(attributes, "POSITION");
		normals = assembleVec3Attribute(attributes, "NORMAL");
		tangents = assembleVec4Attribute(attributes, "TANGENT");
		texUVs = assembleVec2Attribute(attributes, "TEXCOORD_0");

		std::vector<Vertex> vertices = assembleVertices(positions, normals, tangents, texUVs);
		
		unsigned int indAccIndex = JSON["meshes"][indMesh]["primitives"][0]["indices"];
		
		std::vector<GLuint> indices = getIndices(JSON["accessors"][indAccIndex]);
		Material material = generateMaterial();

		m_meshes.push_back(Mesh(vertices, indices, material));
	}

	void Model::traverseNode(unsigned int nextNode, glm::mat4 matrix)
	{
		json node = JSON["nodes"][nextNode];

		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
		if (node.find("translation") != node.end())
		{
			float transValues[3];
			for (unsigned int i = 0; i < node["translation"].size(); i++)
			{
				transValues[i] = (node["translation"][i]);
			}
			translation = glm::make_vec3(transValues);
		}
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		if (node.find("rotation") != node.end())
		{
			float rotValues[4] =
			{
				node["rotation"][3],
				node["rotation"][0],
				node["rotation"][1],
				node["rotation"][2]
			};
			rotation = glm::make_quat(rotValues);
		}
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		if (node.find("scale") != node.end())
		{
			float scaleValues[3];
			for (unsigned int i = 0; i < node["scale"].size(); i++)
			{
				scaleValues[i] = (node["scale"][i]);
			}
			scale = glm::make_vec3(scaleValues);
		}
		glm::mat4 matNode = glm::mat4(1.0f);
		if (node.find("matrix") != node.end())
		{
			float matValues[16];
			for (unsigned int i = 0; i < node["matrix"].size(); i++)
			{
				matValues[i] = (node["matrix"][i]);
			}
			matNode = glm::make_mat4(matValues);
		}

		glm::mat4 trans = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 sca = glm::mat4(1.0f);

		trans = glm::translate(trans, translation);
		rot = glm::mat4_cast(rotation);
		sca = glm::scale(sca, scale);

		glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

		if (node.find("mesh") != node.end())
		{
			translationsMeshes.push_back(translation);
			rotationsMeshes.push_back(rotation);
			scalesMeshes.push_back(scale);
			matricesMeshes.push_back(matNextNode);

			loadMesh(node["mesh"]);
		}

		if (node.find("children") != node.end())
		{
			for (unsigned int i = 0; i < node["children"].size(); i++)
				traverseNode(node["children"][i], matNextNode);
		}
	}

	std::vector<unsigned char> Model::get_data()
	{
		std::string bytesText; // holds raw text
		std::string uri = JSON["buffers"][0]["uri"]; // key which points to a .bin file with the binary data

		if (uri.find(".bin") != std::string::npos)
		{
			// RAW data is in a bin file
			std::string fileStr = std::string(m_file);
			std::string fileDirectory;
			if (fileStr.find('\\') != std::string::npos)
			{
				fileDirectory = fileStr.substr(0, fileStr.find_last_of('\\') + 1);
			}
			else
			{
				fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
			}

			bytesText = Shader::get_file_contents((fileDirectory + uri).c_str());

			std::vector<unsigned char> data(bytesText.begin(), bytesText.end());

			return data;
		}
		else
		{
			// RAW data is encoded into the .gltf file
			// E.g. "data:application/octet-stream;base64,AAABAAIAAAAAAAAAAAAAAAAAAAAAAIA/AAAAAAAAAAAAAAAAAACAPwAAAAA="

			bytesText = uri.substr(uri.find_last_of(',') + 1, uri.find_first_of('=') + 1);

			std::vector<unsigned char> data = Base_64::base64_decode(bytesText);

			//std::vector<unsigned char> data(bytesText.begin(), bytesText.end());

			return data;
		}

	}
	std::vector<glm::vec2> Model::assembleVec2Attribute(json attributes, const char* attribKey)
	{
		std::vector<glm::vec2> vec;

		unsigned int accIndex = attributes.value(attribKey, UINT_MAX);
		if (accIndex != UINT_MAX)
		{
			// Found this attribute in .gltf file
			std::vector<float> floatVec = getFloats(JSON["accessors"][accIndex]);
			vec = groupFloatsVec2(floatVec);
		}

		return vec;
	}
	std::vector<glm::vec3> Model::assembleVec3Attribute(json attributes, const char* attribKey)
	{
		std::vector<glm::vec3> vec;

		unsigned int accIndex = attributes.value(attribKey, UINT_MAX);
		if (accIndex != UINT_MAX)
		{
			// Found this attribute in .gltf file
			std::vector<float> floatVec = getFloats(JSON["accessors"][accIndex]);
			vec = groupFloatsVec3(floatVec);
		}

		return vec;
	}
	std::vector<glm::vec4> Model::assembleVec4Attribute(json attributes, const char* attribKey)
	{
		std::vector<glm::vec4> vec;

		unsigned int accIndex = attributes.value(attribKey, UINT_MAX);
		if (accIndex != UINT_MAX)
		{
			// Found this attribute in .gltf file
			std::vector<float> floatVec = getFloats(JSON["accessors"][accIndex]);
			vec = groupFloatsVec4(floatVec);
		}

		return vec;
	}
	std::vector<float> Model::getFloats(json accessor)
	{
		std::vector<float> floatVec;

		// Get relevant Data from ACCESSOR
		unsigned int buffViewIndex = accessor.value("bufferView", 1);
		unsigned int count = accessor["count"]; // how many float we have to get 
		unsigned int accByteOffset = accessor.value("byteOffset", 0); // Tells us from what index to look at the data with respect to the beginning of the buffer view
		std::string type = accessor["type"]; // how to group the floats (scalar, vec2, vec3, vec4)

		// Get the number of bytes per vertex
		unsigned int numPerVert;
		if (type == "SCALAR") numPerVert = 1;
		else if (type == "VEC2") numPerVert = 2;
		else if (type == "VEC3") numPerVert = 3;
		else if (type == "VEC4") numPerVert = 4;
		else throw std::invalid_argument("type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

		// GET DATA in BUFFER VIEW
		json bufferView = JSON["bufferViews"][buffViewIndex];
		unsigned int byteOffset = bufferView["byteOffset"]; // tells us where the buffer view starts
		unsigned int beginningOfData = byteOffset + accByteOffset;
		unsigned int byteLength = count * 4 * numPerVert; // Find masnually in case of values sharing buffer

		for (unsigned int i = beginningOfData; i < beginningOfData + byteLength; i)
		{
			unsigned char bytes[] = { m_data[i++], m_data[i++], m_data[i++], m_data[i++] };
			// Transform the bytes into a float using memcpy
			float value;
			std::memcpy(&value, &bytes, sizeof(value));
			floatVec.push_back(value);
		}

		return floatVec;
	}

	std::vector<GLuint> Model::getIndices(json accessor)
	{
		std::vector<GLuint> indices;

		// Get relevant Data from Json
		unsigned int buffViewIndex = accessor.value("bufferView", 0);
		unsigned int count = accessor["count"]; // how many float we have to get 
		unsigned int accByteOffset = accessor.value("bufferOffset", 0); // Tells us from what index to look at the data with respect to the beginning of the buffer view
		unsigned int componentType = accessor["componentType"]; // type of component
		
		json bufferView = JSON["bufferViews"][buffViewIndex];
		unsigned int byteOffset = bufferView["byteOffset"]; // tells us where the buffer view starts
		unsigned int beginningOfData = byteOffset + accByteOffset;
		unsigned int byteLength = componentType == 5125 ? count * 4 : count * 2;
		// 5125 -> uint, 5123 -> ushort, 5122 -> short

		if (componentType == 5125) // unsigned integer
		{
			for (unsigned int i = beginningOfData; i < beginningOfData + byteLength; i)
			{
				unsigned char bytes[] = { m_data[i++], m_data[i++], m_data[i++], m_data[i++] };
				// Transform the bytes into a float using memcpy
				unsigned int value;
				std::memcpy(&value, bytes, sizeof(unsigned int));
				indices.push_back((GLuint)value);
			}
		}
		else if (componentType == 5123) // unsigned short
		{
			for (unsigned int i = beginningOfData; i < beginningOfData + byteLength; i)
			{
				unsigned char bytes[] = { m_data[i++], m_data[i++] };
				// Transform the bytes into a float using memcpy
				unsigned short value;
				std::memcpy(&value, bytes, sizeof(unsigned short));
				indices.push_back((GLuint)value);
			}
		}
		else if (componentType == 5122) // short
		{
			for (unsigned int i = beginningOfData; i < beginningOfData + byteLength; i)
			{
				unsigned char bytes[] = { m_data[i++], m_data[i++] };
				// Transform the bytes into a float using memcpy
				short value;
				std::memcpy(&value, bytes, sizeof(short));
				indices.push_back((GLuint)value);
			}
		}

		return indices;
	}

	Material Model::generateMaterial()
	{
		Material material;

		std::string fileStr = std::string(m_file);
		std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('\\') + 1);

		unsigned int iterator;

		for (iterator = 0; iterator < JSON["images"].size(); iterator++)
		{
			std::string texPath = JSON["images"][iterator]["uri"];

			bool skip = false;
			for (unsigned int j = 0; j < m_loadedTexName.size(); j++)
			{
				if (m_loadedTexName[j] == texPath)
				{
					material.Textures.push_back(m_loadedTex[j]);
					skip = true;
					break;
				}
			}

			if (!skip)
			{
				// If 'baseColor' is found, this is most likely a diffuse texture
				if (texPath.find("base") != std::string::npos || texPath.find("Base") != std::string::npos)
				{
					Texture2D diffuse = Texture2D((fileDirectory + texPath).c_str(), "diffuse", m_loadedTex.size());
					material.Textures.push_back(diffuse);
					m_loadedTex.push_back(diffuse);
					m_loadedTexName.push_back(texPath);
				}
				// probably a specular map
				else if (texPath.find("metallic") != std::string::npos || texPath.find("Metallic") != std::string::npos)
				{
					Texture2D specular = Texture2D((fileDirectory + texPath).c_str(), "specular", m_loadedTex.size());
					material.Textures.push_back(specular);
					m_loadedTex.push_back(specular);
					m_loadedTexName.push_back(texPath);
				}
			}

		}

		if (iterator == 0)
		{
			Texture2D diffuse = Texture2D::GetStaticTextureID("diffuse", 0, true);
			material.Textures.push_back(diffuse);
			iterator++;
		}
		if (iterator == 1)
		{
			Texture2D specular = Texture2D::GetStaticTextureID("specular", 1, false);
			material.Textures.push_back(specular);
			iterator++;
		}

		return material;
	}

	std::vector<Vertex> Model::assembleVertices
	(
		std::vector<glm::vec3> positions = std::vector<glm::vec3>(),
		std::vector<glm::vec3> normals = std::vector<glm::vec3>(),
		std::vector<glm::vec4> tangents = std::vector<glm::vec4>(),
		std::vector<glm::vec2> texUVs = std::vector<glm::vec2>()
	)
	{
		std::vector<Vertex> vertices;

		if (positions.size() <= 0)
		{
			// EXIT OUT BECAUSE THERE ARE NO VERTS
			throw std::invalid_argument("positions vector for model is EMPTY!");
			return vertices;
		}

		if (normals.size() <= 0)
		{
			normals.reserve(positions.size());
			normals.resize(positions.size());
			for (size_t i = 0; i < positions.size(); i++)
			{
				normals[i] = glm::vec3(FLT_MAX);
			}
		}

		if (tangents.size() <= 0)
		{
			tangents.reserve(positions.size());
			tangents.resize(positions.size());
			for (size_t i = 0; i < positions.size(); i++)
			{
				tangents[i] = glm::vec4(FLT_MAX);
			}
		}

		if (texUVs.size() <= 0)
		{
			texUVs.reserve(positions.size());
			texUVs.resize(positions.size());
			for (size_t i = 0; i < positions.size(); i++)
			{
				texUVs[i] = glm::vec2(FLT_MAX);
			}
		}

		
		for (unsigned int i = 0; i < positions.size(); i++) 
		{
			vertices.push_back
			(
				Vertex 
				{
					positions[i],
					normals[i],
					tangents[i],
					texUVs[i]
				}
			);
		}
		return vertices;
	}


	std::vector<glm::vec2> Model::groupFloatsVec2(std::vector<float> floatVec)
	{
		std::vector<glm::vec2> vectors;
		for (unsigned int i = 0; i < floatVec.size(); i)
		{
			vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
		}
		return vectors;
	}
	std::vector<glm::vec3> Model::groupFloatsVec3(std::vector<float> floatVec)
	{
		std::vector<glm::vec3> vectors;
		for (unsigned int i = 0; i < floatVec.size(); i)
		{
			vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
		}
		return vectors;
	}
	std::vector<glm::vec4> Model::groupFloatsVec4(std::vector<float> floatVec)
	{
		std::vector<glm::vec4> vectors;
		for (unsigned int i = 0; i < floatVec.size(); i)
		{
			vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
		}
		return vectors;
	}
}