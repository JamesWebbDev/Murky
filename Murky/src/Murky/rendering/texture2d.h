#ifndef MK_TEXTURE_2D_H
#define MK_TEXTURE_2D_H

#include "../core/core.h"

#include <glad/glad.h>

namespace Murky
{
	class MURKY_API Texture2D
	{
	public:
		// the texture ID
		GLuint ID = 0;

		// path to texture
		const char* TexturePath = "";

		// texture type (diffuse, specular)
		const char* Type = "";

		// texture unit slot
		GLuint Unit = 0;

		inline static Texture2D GetStaticTextureID(const char* textureType, GLuint slot, bool isWhite)
		{
			static const char* path = isWhite ? m_DEFAULT_PATH_WHITE : m_DEFAULT_PATH_BLACK;
			const char* fileName = isWhite ? "blank.png" : "black.png";
			// Extract full path
			std::string fileStr = std::string(path);
			std::string fileDir = fileStr.substr(0, fileStr.find_last_of('/') + 1);
			std::string texName = std::string(fileName);

			Texture2D defaultTex = Texture2D((fileDir + texName).c_str(), textureType, slot);

			return defaultTex;
		}
	
		Texture2D(const char* texturePath, const char* textureType, GLuint slot);

		// Binds a texture
		void Bind() const;
		// UnBinds a texture
		void Unbind() const;
		// Deletes a texture
		void Delete();

	public:
		// Default tex variables
		static Texture2D m_static_texture;
#ifdef DEBUG
		inline static const char* m_DEFAULT_PATH_WHITE = "../Murky/shaders/blank.png";
		inline static const char* m_DEFAULT_PATH_BLACK = "../Murky/shaders/black.png";
#else // RELEASE and DIST
		inline static const char* m_DEFAULT_PATH_WHITE = "../../../Murky/shaders/blank.png";
		inline static const char* m_DEFAULT_PATH_BLACK = "../../../Murky/shaders/black.png";
#endif

		
	};
}

#endif