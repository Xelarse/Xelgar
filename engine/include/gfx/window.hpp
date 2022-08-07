#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <functional>

#include "utils/math.hpp"

namespace Xelgar {
    enum class WindowMode 
    {
        FULL_SCREEN,
        WINDOWED,
        BORDERLESS
    };

    struct WindowSettings
    {
        unsigned int width = 1280;
        unsigned int height = 720;
        const char* windowTitle = "Xelgar Engine";
        WindowMode wndMode = WindowMode::WINDOWED;
        unsigned int glfwContextHintMajor = 3;
        unsigned int glfwContextHintMinor = 3;
    };

    class Window final
    { 
        public:
            //Standard constructors
            Window();
            Window(WindowSettings settings);

            //Copy constructors
            Window(const Window& rhs) = delete;
            Window& operator=(const Window& rhs) = delete;

            //Move constructors
            Window(Window&& rhs) = delete;
            Window& operator=(Window&& rhs) = delete;

            //Destructor
            ~Window();

            GLFWwindow* getWindowPtr() { return pWnd; }
            void setKeyCallback(std::function<void(GLFWwindow*, int, int, int ,int)> callback);
        private:
            void createWindow();
            static void errorHandlerCallback(int err, const char* desc);

            GLFWwindow* pWnd = nullptr;
            WindowSettings currentSettings;
    };
}