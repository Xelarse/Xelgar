#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>


namespace Xelgar {
    class Shader final {

        public:
            enum class SourceType {
                FILE,
                CSTR,
            };

            enum class ShaderType {
                VERTEX,
                FRAGMENT
            };

            //Standard constructors
            Shader() = delete;
            Shader(SourceType srcType, const char* str, ShaderType shdType);

            //Copy constructors
            Shader(const Shader& rhs) = delete;
            Shader& operator=(const Shader& rhs) = delete;

            //Move constructors
            Shader(Shader&& rhs) = delete;
            Shader& operator=(Shader&& rhs) = delete;

            //Destructor
            ~Shader();

            inline unsigned int id() { return shader_id; }
        private:
            std::string loadShaderFromSource(const char* path);
            unsigned int shaderTypeToGLenum(ShaderType type);

            unsigned int shader_id;
    };
}