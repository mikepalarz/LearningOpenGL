//
//  main.cpp
//  HelloWorld
//
//  Created by Mike Palarz on 3/14/19.
//  Copyright © 2019 Mike Palarz. All rights reserved.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "myShader.h"
#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Screen width and height
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// Source code for shaders
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "\n"
    "out vec3 ourColor;\n"
    "\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main() {\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
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
//    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//    // Checking for vertex shader compile errors
//    int success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    } else {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "SUCCESS::SHADER::VERTEX::COMPILATION_COMPLETED\n" << infoLog << std::endl;
//    }
//
//    // Fragment shader for the color orange
//    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//    // Again, checking for compile-time errors for the fragment shader
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//    } else {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "SUCCESS::SHADER::FRAGMENT::COMPILATION_COMPLETED\n" << infoLog << std::endl;
//    }
//
//    // We now link the shaders for our first program
//    int shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    // Checking for linking errors
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//    } else {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        std::cout << "SUCCESS::SHADER::PROGRAM::LINKING_COMPLETED\n" << infoLog << std::endl;
//    }
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
    
    Shader myShader("shader.vs", "shader.fs");
    
    /*
     Setting up vertex data, VBOs, and VAOs
     */
    float vertices [] = {
        // Positions        // Colors
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Lower left, red
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Middle top, green
        0.0f,   0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Lower right, blue
    };
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Binding the VAO, then binding and filling the VBO and enabling our attribute(s)
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * (sizeof(float)), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * (sizeof(float)), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // This can be used to draw our objects in wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // This is our render loop
    while (!glfwWindowShouldClose(window)) {
        // Handling input
        processInput(window);
        
        // Actual rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // Configuring the color buffer for when the screen will be cleared
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Drawing our first triangle
        myShader.use();
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);    // Actually drawing the triangles
        
        // Checks and calls I/O events; swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // De-allocating all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
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
