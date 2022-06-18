#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <tuple>


void error_callback(int err, const char* desc) {
    std::cout << "An glfw error has occured: " << desc << std::endl;
}

void framebuffer_size_callback(GLFWwindow* wnd, int new_width, int new_height) {
    std::cout<< "Framebuffer size changed to width: " << new_width << ", height: " << new_height << "; updating viewport" << std::endl;
    glViewport(0, 0, new_width, new_height);
}

static void key_callback(GLFWwindow* wnd, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(wnd, GLFW_TRUE);
    }
}

void processInput(GLFWwindow* wnd) { 
    if (glfwGetKey(wnd, GLFW_KEY_SPACE) == GLFW_PRESS) { 
        //Do some rendering shite or something idk
    }
}

// These are normalized device coords (NDC) but typically screen coords are 0,0 top left
float tri_verts[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f,
};

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

int main(int, char**) {
    //Link up an error callback func so that we can see any errors with setting up and using glfw
    glfwSetErrorCallback(error_callback);


    if (!glfwInit()) {
        std::cout << "GLFW failed to initialize, exiting..." << std::endl;
        return 0;
    }

    //Setup a window to hold our context within
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Xelgar Engine", NULL, NULL);
    if (!window) {
        std::cout << "GLFW failed to create window, exiting..." << std::endl;
        glfwTerminate();
        return 0;
    }

    //Set up a GL context in the newly created window
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to init GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }

    //Set window callbacks
    glfwSetKeyCallback(window, key_callback);

    //Setup GL viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    //monitor changes in framebuffer size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int vsync = 1; //1 is on 0 is off
    glfwSwapInterval(vsync);

    ////Vertex buffer
    //Generate the unique id this buffer will have
    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);

    //Only 1 buffer of the same type can be bound at once
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);  //State setting function, any buffer calls to GL_ARRAY_BUFFER will be specifically to out vbo_id
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_verts), tri_verts, GL_STATIC_DRAW); //GL_STATIC == set once used many, STREAM == set once used a few, DYNAMIC == set many used many

    //Compilation of vertex shader
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Check if vertex shader compiled successfully
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation failed: " << infoLog << std::endl;
    }


    //Render loop
    while (!glfwWindowShouldClose(window)) {
        //// Input Processing
        double time_since_creation = glfwGetTime();
        //Alternative to processing Input, instead of using keypress callback, use a glfw specific func. I guess this specifically gets inputs at the start of a frame instead of processing them at the end
        processInput(window);

        //// Rendering commands
        //Set a clear colour before using GL clear to flush the existing colour buffer with the new col
        glClearColor(0.2f, 0.55f, 0.83f, 1.0f); //State setting function
        glClear(GL_COLOR_BUFFER_BIT);           //State using function


        //// Check events and swap buffers with new renders
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    //glfw cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
}