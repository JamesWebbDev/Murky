#include "mkpch.h"

#include "texture2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Murky
{
	

	Texture2D::Texture2D(const char* texturePath, const char* textureType, GLuint slot) :
		ID(0),
		TexturePath(texturePath),
		Type(textureType),
		Unit(slot)
	{

		// Initialise texture DATA
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);

		unsigned char* bytes = stbi_load(texturePath, &width, &height, &nrChannels, 0);

		// Generates an OpenGL texture object
		glGenTextures(1, &ID);

		// Assigns texture to a Texture Unit
		glActiveTexture(GL_TEXTURE0 + Unit);
		glBindTexture(GL_TEXTURE_2D, ID);

		// Configures the way the texture repeats (if at all)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Configures the type of algorithm that makes the image smaller or bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		if (bytes)
		{
			// GENERATE Texture image
			// (target texture object, mipmap level, format, width, height, legacy stuff, 
			// format for src, datattype for src, the data  ) vvvvvvvvvvvvv
			if (nrChannels == 4)
			{
				// RGBA format
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else if (nrChannels == 3)
			{
				// RGB format
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else if (nrChannels == 1)
			{
				// R format
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				MK_ENG_ERROR("Failed to determine color channel count: {0}", texturePath);
			}

		}
		else
		{
			MK_ENG_ERROR("Failed to load texture from path: {0}", texturePath);
			throw std::invalid_argument("Automatic Texture type recognition failed");
		}
		// Free image from memory after use
		stbi_image_free(bytes);

		// Unbinds the OpenGL texture object so that it can't accidently be modified
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// Binds a texture
	void Texture2D::Bind() const
	{
		glActiveTexture(GL_TEXTURE0 + Unit);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	// Unbinds a texture
	void Texture2D::Unbind() const
	{
		glActiveTexture(GL_TEXTURE0 + Unit);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// Deletes a texture
	void Texture2D::Delete()
	{

	}
}