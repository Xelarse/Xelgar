#include "gfx/window.hpp"

namespace Xelgar {
    Window::Window() : currentSettings(WindowSettings{}) {
        createWindow();
    }

    Window::Window(WindowSettings settings) : currentSettings(settings) {
        createWindow();
    }

    Window::~Window() {
        
    }

    void Window::setKeyCallback(std::function<void(GLFWwindow*, int, int, int ,int)> callback) {
        // glfwSetKeyCallback(pWnd, callback);
    }

    void Window::createWindow() {
        //Link up an error callback func so that we can see any errors with setting up and using glfw
        glfwSetErrorCallback(errorHandlerCallback);

        if (!glfwInit()) {
            std::cout << "GLFW failed to initialize, exiting..." << std::endl;
            return;
        }
        //Hint for OpenGL version to use
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        //Setup a window to hold our context within
        pWnd = glfwCreateWindow(
            currentSettings.width,
            currentSettings.height,
            currentSettings.windowTitle,
            NULL,
            NULL
        );
        if (!pWnd) {
            std::cout << "GLFW failed to create window, exiting..." << std::endl;
            glfwTerminate();
            return;
        }

        //monitor changes in framebuffer size
        glfwSetFramebufferSizeCallback(pWnd, framebufferSizeChangeCallback);
    }

    void Window::errorHandlerCallback(int error, const char* desc) {
        std::cout << "An glfw error has occured: " << desc << std::endl;
    }

    void Window::framebufferSizeChangeCallback(GLFWwindow* wnd, int new_width, int new_height) {
        std::cout<< "Framebuffer size changed to width: " << new_width << ", height: " << new_height << "; updating viewport" << std::endl;
        // currentViewport = Vec2<int> {.x = new_width, .y = new_height};
        // glViewport(0, 0, new_width, new_height);
    }
}