#ifndef MK_SHADER_H
#define MK_SHADER_H

#include "../core/core.h"

#include <glm.hpp>

namespace Murky
{
    class Model;
    class Camera;
    struct Light;
    typedef unsigned int GLuint;

    class MURKY_API Shader
    {
    public:
        // the program ID
        unsigned int ID = UINT_MAX;

        // constructor reads and builds the shader
        Shader() {}
        Shader(char* vertVersion, char* fragVersion);
        ~Shader();
        // use/activate the shader
        void use() const;
        // delete shader
        void destroy();
        // utility uniform functions
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, const glm::vec2 &value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w) const;
        void setMat2(const std::string& name, const glm::mat2& mat) const;
        void setMat3(const std::string& name, const glm::mat3& mat) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;

        static std::string get_file_contents(const char* file);
        static std::string get_file_contents(const std::string& dir, const char* fileName);

        static Shader* generate_suitable_shader(const Model& model, bool isLit);

        void set_shader_files(const std::string& vertexFile, const std::string& fragmentFile); 
        void set_shader_files_abs(const std::string& vertexFile, const std::string& fragmentFile); 

        void set_matching_shader_files(const std::string& sVertOrFragFile); 

        void add_preprocessor_vert(std::string input);
        void add_preprocessor_frag(std::string input);

        void add_light_directional(Light lightConfig, short index);
        void add_light_point(Light lightConfig, short index);

        void Update(const Camera& camera) const;

    private: 

        

        void checkCompileErrors(GLuint shader, std::string type) const;

#ifdef DEBUG
        const char* SHADER_VERTEX_PATH = "../Murky/shaders/vert/";
        const char* SHADER_FRAGMENT_PATH = "../Murky/shaders/frag/";
#else // RELEASE and DIST
        const char* SHADER_VERTEX_PATH = "../../../Murky/shaders/vert/";
        const char* SHADER_FRAGMENT_PATH = "../../../Murky/shaders/frag/";
#endif

        std::string preprocessors_vert = std::string();
        std::string preprocessors_frag = std::string();
    };
}

#endif