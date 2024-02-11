#include "mkpch.h"

#include "material.h"
#include "texture2d.h"
#include "shader.h"

namespace Murky
{
    void Material::BindTextures()
    {
        for (size_t i = 0; i < Textures.size(); i++)
        {
            Textures[i].Bind();
        }
    }
    void Material::ApplyAttributesToShader(const Shader& shader)
    {
        // Update with new values in the future
        shader.setFloat("material.shininess", shininess);
        shader.setVec3("material.color", colour);
    }
}