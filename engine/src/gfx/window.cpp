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
    }

    void Window::errorHandlerCallback(int error, const char* desc) {
        std::cout << "An glfw error has occured: " << desc << std::endl;
    }
}