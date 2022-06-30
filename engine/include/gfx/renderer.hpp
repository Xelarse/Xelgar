#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Xelgar {
    enum class VSyncMode {
        OFF = 0,
        ON = 1
    };

    struct RendererSettings
    {
        VSyncMode vsync = VSyncMode::ON;
    };

    class Renderer final {
        public:
            //Standard constructors
            Renderer() = delete;
            Renderer(GLFWwindow* wnd);
            Renderer(GLFWwindow* wnd, RendererSettings settings);

            //Copy constructors
            Renderer(const Renderer& rhs) = delete;
            Renderer& operator=(const Renderer& rhs) = delete;

            //Move constructors
            Renderer(Renderer&& rhs) = delete;
            Renderer& operator=(Renderer&& rhs) = delete;

            //Destructor
            ~Renderer();


        private:
            void initGlew(GLFWwindow* wnd);

            RendererSettings currentSettings;
    };
}