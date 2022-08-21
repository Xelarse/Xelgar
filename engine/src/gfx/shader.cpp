#include "gfx/shader.hpp"

#include <fstream>
#include <iostream>

namespace Xelgar { 
    Shader::Shader(SourceType srcType, const char* str, ShaderType shdType) {
        std::string source;
        const char* content_cstr = str;

        if (srcType == SourceType::FILE) {
            source = loadShaderFromSource(str);
            content_cstr = source.c_str();
        }

        shader_id = glCreateShader(shaderTypeToGLenum(shdType));
        glShaderSource(shader_id, 1, &content_cstr, NULL);
        glCompileShader(shader_id);

        //Check for shader correct compilation
        int success;
        char infoLog[512];
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
            std::cout << "Error - Shader Compilation Failed: " << infoLog << std::endl;
        }
    }

    Shader::~Shader() {
        glDeleteShader(shader_id);
    }

    std::string Shader::loadShaderFromSource(const char* path) {
        //You can read into a string giving the beginning and an end iterator
        std::ifstream ifs(path);
        return std::string(
            (std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>())
        );
    }

    unsigned int Shader::shaderTypeToGLenum(ShaderType type) {
        switch(type){
            case ShaderType::VERTEX: {
                return static_cast<unsigned int>(GL_VERTEX_SHADER);
            }

            case ShaderType::FRAGMENT: {
                return static_cast<unsigned int>(GL_FRAGMENT_SHADER);
            }

            default: {
                std::cout << "ERROR - No mapping found for the given shader type" << std::endl;
            }
        }
    }
}