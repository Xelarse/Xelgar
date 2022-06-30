#include "gfx/renderer.hpp"

namespace Xelgar {
    Renderer::Renderer(GLFWwindow* wnd) : currentSettings(RendererSettings{}) {
        initGlew(wnd);
    }

    Renderer::Renderer(GLFWwindow* wnd, RendererSettings settings) : currentSettings(settings) {
        initGlew(wnd);
    }

    Renderer::~Renderer() {

    }

    void Renderer::initGlew(GLFWwindow* wnd) {
        //Set up a GL context in the newly created window
        glfwMakeContextCurrent(wnd);
        if (glewInit() != GLEW_OK) {
            std::cout << "Failed to init GLEW" << std::endl;
            return;
        }

        //Setup GL viewport
        // glfwGetFramebufferSize(wnd, &currentViewport.x, &currentViewport.y);
        // glViewport(0, 0, currentViewport.x, currentViewport.y);
        int width, height;
        glfwGetFramebufferSize(wnd, &width, &height);
        glViewport(0, 0, width, height);

        //Set VSync
        glfwSwapInterval(static_cast<int>(currentSettings.vsync));
    }

}