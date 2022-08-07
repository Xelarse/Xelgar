#include "gfx/renderer.hpp"

namespace Xelgar {
    Renderer::Renderer(GLFWwindow* wnd) : currentSettings(RendererSettings{}), pWnd(wnd) {
        // Renderer::shouldViewportRefresh = false;
        initGlew(wnd);
    }

    Renderer::Renderer(GLFWwindow* wnd, RendererSettings settings) : currentSettings(settings), pWnd(wnd) {
        // Renderer::shouldViewportRefresh = false;
        initGlew(wnd);
    }

    Renderer::~Renderer() {

    }

    void Renderer::refreshViewport() {
        //Get the current framebuffer size
        int width, height;
        glfwGetFramebufferSize(pWnd, &width, &height);

        //Cache it in the local settings for ref
        currentSettings.frameBufferWidth = width;
        currentSettings.frameBufferHeight = height;

        //Update the viewport
        updateViewportFromConfig();
    }

    void Renderer::refreshViewport(int new_width, int new_height) {
        //Cache it in the local settings for ref
        currentSettings.frameBufferWidth = new_width;
        currentSettings.frameBufferHeight = new_height;

        //Update the viewport
        updateViewportFromConfig();
    }

    void Renderer::initGlew(GLFWwindow* wnd) {
        //Set up a GL context in the newly created window
        glfwMakeContextCurrent(wnd);
        if (glewInit() != GLEW_OK) {
            std::cout << "Failed to init GLEW" << std::endl;
            return;
        }

        //Setup GL viewport
        refreshViewport();

        //monitor changes in framebuffer size
        glfwSetFramebufferSizeCallback(wnd, framebufferSizeChangeCallback);

        //Set VSync
        glfwSwapInterval(static_cast<int>(currentSettings.vsync));
    }

    void Renderer::updateViewportFromConfig() {
        glViewport(
            currentSettings.vp.x, 
            currentSettings.vp.y, 
            currentSettings.frameBufferWidth, 
            currentSettings.frameBufferHeight
        );
    }

    void Renderer::framebufferSizeChangeCallback(GLFWwindow* wnd, int new_width, int new_height) {
        std::cout<< "Framebuffer size changed to width: " << new_width << ", height: " << new_height << "; updating viewport" << std::endl;
        // Renderer::shouldViewportRefresh.store(true);
    }

}