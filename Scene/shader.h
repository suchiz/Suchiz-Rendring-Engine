#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>

enum ShaderType {
    LIGHT,
    BLINNPHONG,
    DEPTH
};

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(ShaderType type)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::string vertexPath;
        std::string fragmentPath;
        char buffer[256];
        char *val = getcwd(buffer, sizeof(buffer));
        std::string path(val);
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            if (type == BLINNPHONG){
                vertexPath = "/home/suchiz/Documents/Suchiz-Rendring-Engine/Shaders/blinnphong.vs";
                fragmentPath = "/home/suchiz/Documents/Suchiz-Rendring-Engine/Shaders/blinnphong.fs";
            } else if (type == LIGHT){
                vertexPath = "/home/suchiz/Documents/Suchiz-Rendring-Engine/Shaders/lightshader.vs";
                fragmentPath = "/home/suchiz/Documents/Suchiz-Rendring-Engine/Shaders/lightshader.fs";
            } else if (type == DEPTH){
                vertexPath = "/home/suchiz/Documents/Suchiz-Rendring-Engine/Shaders/depthmapshader.vs";
                fragmentPath = "/home/suchiz/Documents/Suchiz-Rendring-Engine/Shaders/depthmapshader.fs";
            }
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
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"<< vertexPath << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glad_glCreateShader(GL_VERTEX_SHADER);
        glad_glShaderSource(vertex, 1, &vShaderCode, NULL);
        glad_glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glad_glCreateShader(GL_FRAGMENT_SHADER);
        glad_glShaderSource(fragment, 1, &fShaderCode, NULL);
        glad_glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glad_glCreateProgram();
        glad_glAttachShader(ID, vertex);
        glad_glAttachShader(ID, fragment);
        glad_glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glad_glDeleteShader(vertex);
        glad_glDeleteShader(fragment);
    }
    // activate the shader
    // ------------------------------------------------------------------------
    void use()
    {
        glad_glUseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {
        glad_glUniform1i(glad_glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    {
        glad_glUniform1i(glad_glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    {
        glad_glUniform1f(glad_glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glad_glUniform2fv(glad_glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
        glad_glUniform2f(glad_glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glad_glUniform3fv(glad_glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glad_glUniform3f(glad_glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glad_glUniform4fv(glad_glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) const
    {
        glad_glUniform4f(glad_glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glad_glUniformMatrix2fv(glad_glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glad_glUniformMatrix3fv(glad_glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glad_glUniformMatrix4fv(glad_glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4Array(const std::string &name, const std::vector<glm::mat4> mat, const int size){
        glad_glUniformMatrix4fv(glad_glGetUniformLocation(ID, name.c_str()), size, GL_FALSE, glm::value_ptr(mat[0][0]));
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glad_glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glad_glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glad_glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif // SHADER

