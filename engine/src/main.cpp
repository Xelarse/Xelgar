#ifdef __linux__
    #include <GL/glew.h>
#elif _WIN32
    #include <glew.h>
#else
#endif

#include <GLFW/glfw3.h>

#include <iostream>
#include <tuple>


/*
Exercises

To really get a good grasp of the concepts discussed a few exercises were set up. It is advised to work through them before continuing to the next subject to make sure you get a good grasp of what's going on.
    Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data: solution.
    Now create the same 2 triangles using two different VAOs and VBOs for their data: solution.
    Create two shader programs where the second program uses a different fragment shader that outputs the color yellow; draw both triangles again where one outputs the color yellow: solution.
*/


bool rect_active = false;
bool key_pressed = false;
GLuint fill_type = GL_FILL;

void error_callback(int err, const char* desc) {
    std::cout << "An glfw error has occured: " << desc << std::endl;
}

void framebuffer_size_callback(GLFWwindow* wnd, int new_width, int new_height) {
    std::cout<< "Framebuffer size changed to width: " << new_width << ", height: " << new_height << "; updating viewport" << std::endl;
    glViewport(0, 0, new_width, new_height);
}

static void key_callback(GLFWwindow* wnd, int key, int scancode, int action, int mods) {
    if (!key_pressed){
        if (key == GLFW_KEY_ESCAPE && !key_pressed) {
            glfwSetWindowShouldClose(wnd, GLFW_TRUE);
        }
        else if (key == GLFW_KEY_W) { 
            fill_type = fill_type == GL_FILL ? GL_LINE : GL_FILL;
            glPolygonMode(GL_FRONT_AND_BACK, fill_type);
        }
        else if (key == GLFW_KEY_SPACE) { 
            rect_active = !rect_active;
        }
    }

    if (action == GLFW_PRESS) {
        key_pressed = true;
    }
    else if (action == GLFW_RELEASE) {
        key_pressed = false;
    }
}

void processInput(GLFWwindow* wnd) { 
    // if (glfwGetKey(wnd, GLFW_KEY_SPACE) == GLFW_PRESS && !key_pressed) {
    //     rect_active = !rect_active;
    // }
    // else if (glfwGetKey(wnd, GLFW_KEY_W) == GLFW_PRESS && !key_pressed) {
    //     fill_type = fill_type == GL_FILL ? GL_LINE : GL_FILL;
    //     glPolygonMode(GL_FRONT_AND_BACK, fill_type);
    // }
}

// These are normalized device coords (NDC) but typically screen coords are 0,0 top left
float tri_verts[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f,
};

//Drawing a rect using the element buffer object (basically an index buffer)
float rect_verts[] = {
    0.5f, 0.5f, 0.0f,       //TR
    0.5f, -0.5f, 0.0f,      //BR
    -0.5f, -0.5f, 0.0f,     //BL
    -0.5f, 0.5f, 0.0f       //TL
};

unsigned int rect_inds[] = {
    0, 1, 3,
    1, 2, 3
};

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColour;\n"
    "void main()\n"
    "{\n"
    "   FragColour = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

    ////Vertex buffer + Array Single tri
    //Set up a Vertex Array Object to store this configuration info into
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    
    //Generate the unique id this buffer will have
    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);

    //bind the VAO for the upcoming configuration
    glBindVertexArray(vao_id);

    //Only 1 buffer of the same type can be bound at once
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);  //State setting function, any buffer calls to GL_ARRAY_BUFFER will be specifically to out vbo_id
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_verts), tri_verts, GL_STATIC_DRAW); //GL_STATIC == set once used many, STREAM == set once used a few, DYNAMIC == set many used many

    ////Time to tell OpenGl how to interpret our vertex input data
    glVertexAttribPointer(
        0,                      //This matches up to the layout in our vertex shader AKA layout (location = 0)
        3,                      //How many elements are contained in each pass, this builds up the vec3 we use in the shader
        GL_FLOAT,               //That vec3 consists of floating point values
        GL_FALSE,               //Manages whether or not inputted data should be normalized when casting to float
        3 * sizeof(float),      //How far the stride is to the next 3 elements
        static_cast<void*>(0)   //Offset to where we should begin in the buffer
    );
    glEnableVertexAttribArray(0);   //Since our previously made VBO is still bound this vertex attrib pointer refers to the data stored within that VBO

    ////Vertex buffer + VAO + EBO for rect
    GLuint rect_vao_io;
    glGenVertexArrays(1, &rect_vao_io);

    GLuint rect_vbo_id;
    glGenBuffers(1, &rect_vbo_id);

    GLuint rect_ebo_id;
    glGenBuffers(1, &rect_ebo_id);

    //bind the VAO for the upcoming configuration
    glBindVertexArray(rect_vao_io);

    glBindBuffer(GL_ARRAY_BUFFER, rect_vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_verts), rect_verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);   //This binds this specific Vertex Attrib Array to the layout in the vertex shader, redudant here due to the previous one but done for clarity sake

    //Bind the EBO config to the VAO; VAO pays attention to both binds and unbinds so ensure the VAO is unbound before unbinding EBO or VBO otherwise it wont be bound on the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect_ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect_inds), rect_inds, GL_STATIC_DRAW);

    ////Compilation of vertex shader
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

    ////Compilation of fragment shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Check if fragment shader compiled successfully
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation failed: " << infoLog << std::endl;
    }

    ////Next we link these compiled shaders to a specific shader program. Which ever program is currently active will be used for subsequent render calls. Specifcally the outputs of one shader must match the inputs of the next
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    //Attach our compiled shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //Check for errors in this process
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader linking failed: " << infoLog << std::endl;
    }

    //Set the program to be used, this means that all following render calls will use this program
    glUseProgram(shaderProgram); //State setting function

    ////After shader objects are linked into a program object they can be freed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Render loop
    while (!glfwWindowShouldClose(window)) {
        //// Input Processing
        double time_since_creation = glfwGetTime();
        //Alternative to processing Input, instead of using keypress callback, use a glfw specific func. I guess this specifically gets inputs at the start of a frame instead of processing them at the end
        // processInput(window);

        //// Rendering commands
        //Set a clear colour before using GL clear to flush the existing colour buffer with the new col
        glClearColor(0.2f, 0.55f, 0.83f, 1.0f); //State setting function
        glClear(GL_COLOR_BUFFER_BIT);           //State using function

        //DRAW THE TRIANGLE. Always ensure you set the state desired for the rendering as to not inhert a previous state
        glUseProgram(shaderProgram);

        if (rect_active){
            glBindVertexArray(rect_vao_io);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); //Indices ptr has 2 uses, a ptr to indicies if an ebo isnt bound, or an offset if an ebo is; null here as we want to being at 0
        }
        else{
            glBindVertexArray(vao_id);
            glDrawArrays(GL_TRIANGLES, 0, 3);   //Args: GL_TRIANGES defines we wanna draw tris with the vert data, 0 for start index, 3 for the total length
        }

        //// Check events and swap buffers with new renders
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    //glfw cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
}