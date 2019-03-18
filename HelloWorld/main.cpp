//
//  main.cpp
//  HelloWorld
//
//  Created by Mike Palarz on 3/14/19.
//  Copyright © 2019 Mike Palarz. All rights reserved.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Screen width and height
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// Source code for shaders
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main(int argc, const char * argv[]) {
    
    // Initializing and configuring GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // Creating the window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Loading the OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    /*
     Building and compiling our shaders
     */
    
    // Vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Checking for vertex shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "SUCCESS::SHADER::VERTEX::COMPILATION_COMPLETED\n" << infoLog << std::endl;
    }
    
    // Fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Again, checking for compile-time errors for the fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "SUCCESS::SHADER::FRAGMENT::COMPILATION_COMPLETED\n" << infoLog << std::endl;
    }
    
    // We now link the shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Checking for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    } else {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "SUCCESS::SHADER::PROGRAM::LINKING_COMPLETED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // Keeping this here for now since it was previously required
//     glViewport(0, 0, 800, 600);
    
    /*
     Setting up vertex data, VBOs, and VAOs
     */
//    float vertices [] = {
//        0.5f, 0.5f, 0.0f,   // Top right corner
//        0.5f, -0.5f, 0.0f,  // Lower right corner
//        -0.5f, -0.5f, 0.0f, // Lower left corner
//        -0.5f, 0.5f, 0.0f    // Top left corner
//
//    };
    float vertices [] = {
        -1.0f, -0.5f, 0.0f, // Triangle 1, lower left
        -0.5f, 0.5f, 0.0f,  // Triangle 1, middle top
        0.0f, -0.5f, 0.0f,  // Triangle 1, lower right
        0.0f, -0.5f, 0.0f,  // Triangle 2, lower left
        0.5f, 0.5f, 0.0f,   // Triangle 2, middle top
        1.0f, -0.5f, 0.0f   // Triangle 2, lower right
    };
    
    unsigned int indices [] ={
        0, 1, 3,    // First triagle
        1, 2, 3     // Second triangle
    };
    
//    unsigned int VBO, VAO, EBO;
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
    
    // We first bind the VAO, then then bind and setup the VBO, and then configure the vertex attributes
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(float)), (void*)0);
    glEnableVertexAttribArray(0);
    
    /*
      Here, we are unbinding VBO from he GL_ARRAY_BUFFER target. We can actually get away with this because
      glVertexAttribPointer() registered VBO as the vertex attribute's bound vertex buffer object, so
      we can safely unbind here.
    */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    /*
       We'll also unbind the VAO here. This is more of a precaution so that additional VAO calls won't
       change the VAO that we've already configured.
     */
    glBindVertexArray(0);
    
    // This can be used to draw our objects in wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // This is our render loop
    while (!glfwWindowShouldClose(window)) {
        // Handling input
        processInput(window);
        
        // Actual rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // Configuring the color buffer for when the screen will be cleared
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Drawing our triangle
        glUseProgram(shaderProgram);
        // Since we only have a single VAO, there's no need to bind it every time, but we're doing this for now to
        // keep things more organized.
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);    // Actually drawing the triangles
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // No need to unbind it every time
        
        // Checks and calls I/O events; swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // De-allocating all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    
    glfwTerminate();
    return 0;
}

// Callback function for reacting to when the window size is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);    // In this case, we simply adjust the size of the view port to the new size of the window
}

// Processes any input by quering GLFW for relevant key presses and reacting accordingly
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
