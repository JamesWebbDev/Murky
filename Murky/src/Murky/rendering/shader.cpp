#include "mkpch.h"

#include "shader.h"
#include "model.h"
#include "../lighting/light.h"
#include "../viewport/camera.h"
#include <glad/glad.h>

#include <limits>


namespace Murky 
{
    Shader::Shader(char* vertVersion, char* fragVersion)
    {
        ID = UINT_MAX;

        add_preprocessor_vert(vertVersion);
        add_preprocessor_frag(fragVersion);
    }
    Shader::~Shader()
    {
        destroy();
    }
    void Shader::use() const
    {
        if (ID != UINT_MAX)
        {
            glUseProgram(ID);
        }
        else
        {
            std::cout << "Tried to use un-set shader!" << std::endl;
        }
    }

    void Shader::destroy()
    {
        if (ID != UINT_MAX)
        {
            glDeleteProgram(ID);
            ID = UINT_MAX;
        }
    }


    std::string Shader::get_file_contents(const char* file)
    {
        MK_ENG_TRACE("Before ifstream in");
        std::ifstream in(file, std::ios::binary);
        MK_ENG_TRACE("Before if (in)");
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }
        

        if (in.fail()) { //failbit is always set but not badbit
            MK_ENG_ERROR("Passed in file '{0}'\n", file);
            MK_ENG_ERROR("Logical error on i/o operation. failbit was set\n");
            if (in.bad())
                MK_ENG_ERROR("Read/writing error on i/o operation. badbit was set");

            throw(errno);
        }
        if (!in.is_open()) { //and of course this return true
            MK_ENG_ERROR("File was not opened\n");
            exit(1);
            throw(errno);
        }
    }

    std::string Shader::get_file_contents(const std::string& dir, const char* fileName)
    {
        std::string fullFilePath = dir + fileName;
        return Shader::get_file_contents(fullFilePath.c_str());
    }

    Shader* Shader::generate_suitable_shader(const Model& model, bool isLit)
    {
        std::string vertShaderName;
        std::string fragShaderName;

        std::bitset<4> propertyFlags = model.GetPropertyFlags();
        
        for (int i = 0; i < 4; i++)
        {
            char* bitChar = propertyFlags.test(i) ? "1" : "0";
            
            vertShaderName.append(bitChar);
            fragShaderName.append(bitChar);
        }

        Shader* newShader = new Shader("#version 460 core", "#version 460 core");

        if (isLit)
        {
            fragShaderName.append("_lit");
            newShader->add_preprocessor_frag("#define NR_DIR_LIGHTS " + std::to_string(1));
        }

        vertShaderName.append(".vs");
        fragShaderName.append(".fs");

        MK_ENG_INFO("Generating new shader based on mesh at {0}", model.GetFile());

        newShader->set_shader_files(vertShaderName, fragShaderName);

        return newShader;
    }

    void Shader::set_shader_files(const std::string& vertexFile, const std::string& fragmentFile)
    {
        // Destroy previous shader combo if present
        if (ID != UINT_MAX)
        {
            destroy();
        }

        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        std::string vertexPath = SHADER_VERTEX_PATH + vertexFile;
        std::string fragmentPath = SHADER_FRAGMENT_PATH + fragmentFile;

        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            MK_ENG_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ_AT_PATH \n {0} or {1}", vertexPath, fragmentPath);
        }

        std::string vertString = std::string(preprocessors_vert);
        vertString.append(vertexCode);

        std::string fragString = std::string(preprocessors_frag);
        fragString.append(fragmentCode);

        const char* vShaderCode = vertString.c_str();
        const char* fShaderCode = fragString.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
        // 1. retrieve the vertex/fragment source code from filePath
        
    }

    void Shader::set_shader_files_abs(const std::string& vertexFile, const std::string& fragmentFile)
    {
        // Destroy previous shader combo if present
        if (ID != UINT_MAX)
        {
            destroy();
        }

        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        std::string vertexPath = vertexFile;
        std::string fragmentPath = fragmentFile;

        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            MK_ENG_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ_AT_PATH \n {0} or {1}", vertexPath, fragmentPath);
        }

        std::string vertString = std::string(preprocessors_vert);
        vertString.append(vertexCode);

        std::string fragString = std::string(preprocessors_frag);
        fragString.append(fragmentCode);

        const char* vShaderCode = vertString.c_str();
        const char* fShaderCode = fragString.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        // 1. retrieve the vertex/fragment source code from filePath
    }

    void Shader::set_matching_shader_files(const std::string& sVertOrFragFile)
    {
        MK_ENG_TRACE("Entered set_matching_shader_files: {0}", sVertOrFragFile.c_str());

        std::string otherFile = sVertOrFragFile;
        

        size_t pathSize = sVertOrFragFile.size();
        size_t nameIndex = sVertOrFragFile.find_last_of('\\') + 1;
        // E.g. shaders\vert\model_1101.vs -> model_1101
        std::string fileName = sVertOrFragFile.substr(nameIndex, pathSize - nameIndex - 3);

        MK_ENG_TRACE("Trimmed file name: {0}", fileName.c_str());

        if (sVertOrFragFile[pathSize - 2] != 'v' && sVertOrFragFile[pathSize - 2] != 'f')
        {
            MK_ENG_ERROR("Passed invalid shader path to set_matching_shader_files! {0}", sVertOrFragFile.c_str());
            throw(errno);
        }
        else if (sVertOrFragFile[pathSize - 2] == 'v')
        {
            std::string trimmedFile = sVertOrFragFile.substr(0, sVertOrFragFile.find("vert\\"));
            MK_ENG_TRACE("Initial trim: {0}", trimmedFile.c_str());
            trimmedFile.append("frag\\");
            trimmedFile.append(fileName);
            trimmedFile.append(".fs");
            MK_ENG_TRACE("Post append: {0}", trimmedFile.c_str());
            otherFile = trimmedFile;

            MK_ENG_TRACE("Entering set_shader_files_abs");
            set_shader_files_abs(sVertOrFragFile, otherFile);
        }
        else // sVertOrFragFile[pathSize - 2] MUST == 'f'
        {
            std::string trimmedFile = sVertOrFragFile.substr(0, sVertOrFragFile.find("frag\\"));
            MK_ENG_TRACE("Initial trim: {0}", trimmedFile.c_str());
            trimmedFile.append("vert\\");
            trimmedFile.append(fileName);
            trimmedFile.append(".vs");
            MK_ENG_TRACE("Post append: {0}", trimmedFile.c_str());
            otherFile = trimmedFile;

            MK_ENG_TRACE("Entering set_shader_files_abs");
            set_shader_files_abs(otherFile, sVertOrFragFile);
        }


        MK_ENG_TRACE("Exiting set_matching_shader_files");
    }

    void Shader::add_preprocessor_vert(std::string input)
    {
        preprocessors_vert.append("\n" + input + "\n");
    }

    void Shader::add_preprocessor_frag(std::string input)
    {
        preprocessors_frag.append("\n" + input + "\n");
    }

    void Shader::add_light_directional(Light lightConfig, short index)
    {
        // E.g. dirLights[1].constant
        std::string baseStr = std::string("dirLights[" + std::to_string(index));

        setVec3(baseStr + "].colour", lightConfig.colour);

        setVec3(baseStr + "].direction", lightConfig.direction);

        setVec3(baseStr + "].ambient", lightConfig.ambient);
        setVec3(baseStr + "].diffuse", lightConfig.diffuse);
        setVec3(baseStr + "].specular", lightConfig.specular);
    }

    void Shader::add_light_point(Light lightConfig, short index)
    {
        // E.g. dirLights[1].constant
        std::string baseStr = std::string("pointLights[" + std::to_string(index));

        setVec3(baseStr + "].colour", lightConfig.colour);

        setVec3(baseStr + "].position", lightConfig.position);

        setFloat(baseStr + "].constant", lightConfig.constant);
        setFloat(baseStr + "].linear", lightConfig.linear);
        setFloat(baseStr + "].quadratic", lightConfig.quadratic);

        setVec3(baseStr + "].ambient", lightConfig.ambient);
        setVec3(baseStr + "].diffuse", lightConfig.diffuse);
        setVec3(baseStr + "].specular", lightConfig.specular);
    }

    void Shader::Update(const Camera& camera) const
    {
        setVec3("viewPos", camera.Position);
        setMat4("view", camera.View);
        setMat4("projection", camera.Projection);
    }

    void Shader::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void Shader::setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void Shader::setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    void Shader::setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    void Shader::setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void Shader::checkCompileErrors(GLuint shader, std::string type) const
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                MK_ENG_ERROR("ERROR::SHADER_COMPILTION_ERROR of type: {0} \n {1} ", type, infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                MK_ENG_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {0} \n {1} ", type, infoLog);
            }
        }
    }
}

