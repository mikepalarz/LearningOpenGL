//
//  main.cpp
//  HelloWorld
//
//  Created by Mike Palarz on 3/14/19.
//  Copyright © 2019 Mike Palarz. All rights reserved.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
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
    Shader myShader("shader.vs", "shader.fs");
    
    /*
     Setting up vertex data, VBOs, and VAOs
     */
    float vertices[] = {
         // Positions         // Colors           // Texture coordinates
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top right corner
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom right corner
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom left corner
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top left corner
    };
    
    unsigned int indices[] = {
        0, 1, 3,    // First triangle
        1, 2, 3     // Second triangle
    };
    
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Binding the VAO, then binding and filling the VBO and enabling our attribute(s)
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // This can be used to draw our objects in wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // Generating our texture
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // Setting the texture wrapping and filtering options for the currently bound texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // Telling stbi_image.h to flip images on the y-axis
    
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture #1" << std::endl;
    }
    stbi_image_free(data);
    
    // Moving onto texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        // Note that we need to specify a data type of GL_RGBA since the image has transparency and hence, an alpha channel
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture #2" << std::endl;
    }
    stbi_image_free(data);
    
    // We also need to inform each sampler which texture unit it belongs to
    myShader.use();    // We need to activate/use the shader before we can set any of the uniforms
    myShader.setInt("texture1", 0);
    myShader.setInt("texture2", 1);
    
    // This is our render loop
    while (!glfwWindowShouldClose(window)) {
        // Handling input
        processInput(window);
        
        // Actual rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // Configuring the color buffer for when the screen will be cleared
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Binding the texture
        glActiveTexture(GL_TEXTURE0);   // Making sure to activate the first texture unit
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);   // Likewise for the second
        glBindTexture(GL_TEXTURE_2D, texture2);
        // Render the container
        myShader.use();
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);    // Actually drawing the triangles
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        
        // Checks and calls I/O events; swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // De-allocating all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
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
