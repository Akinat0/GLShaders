#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"

const GLint WIDTH=800, HEIGHT = 600;

int main() {
    
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "AbuGames", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if(window == nullptr){
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    if(glewInit() == !GLEW_OK){
        std::cout << "Failed to initialize glew" << std::endl;
        return -1;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    GLfloat vertices[] {
        
        //Vertices           //Color
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, //bottom left
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, //bottom right
        0.0f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f  //top middle
    };
    
    Shader shader("Resources/Shaders/core.vert", "Resources/Shaders/core.frag");
    
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid * ) 0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid * ) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
//    glBindBuffer( GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    while( !glfwWindowShouldClose(window)){
        
        glfwPollEvents();
        
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        //swap the screen buffers
        glfwSwapBuffers(window);
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    
    std::cout << "\nClose program...\n";
    return 0;
}
