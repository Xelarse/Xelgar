#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <atomic>

namespace Xelgar {
    enum class VSyncMode {
        OFF = 0,
        ON = 1
    };

    struct Viewport {
        int x = 0;
        int y = 0;
    };

    struct RendererSettings
    {
        VSyncMode vsync = VSyncMode::ON;
        int frameBufferWidth = 1280;
        int frameBufferHeight = 720;
        Viewport vp {};
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

            void refreshViewport();
            void refreshViewport(int new_width, int new_height);

            //TODO check this in the main renderer loop to trigger based off the callback needs fixing in constructors and callback
            static std::atomic<bool> shouldViewportRefresh;

        private:
            void initGlew(GLFWwindow* wnd);
            void updateViewportFromConfig();

            static void framebufferSizeChangeCallback(GLFWwindow* wnd, int new_width, int new_height);

            GLFWwindow* pWnd = nullptr;
            RendererSettings currentSettings;
    };
}