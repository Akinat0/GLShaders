#ifndef TextureExample_h
#define TextureExample_h
#endif /* TextureExample_h */

#include <iostream>

#include "SOIL2/SOIL2.h"

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"

class TextureExample{
    
    private :
    const GLint WIDTH=800, HEIGHT = 600;

    public:
    int Start() {
    
        glfwInit();
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Texture", nullptr, nullptr);
        
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
        
        //Get ready for alpha
        glEnable(GL_BLEND);
        
        //TODO research what's it exactly
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        GLfloat vertices[] {
            
            //Vertices              //Color
            0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,    1.0f, 1.0f, //top right
            0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f,    1.0f, 0.0f, //top left
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f, //bottom left
            -0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f,    0.0f, 1.0f, //bottom right
        };
        
        GLuint indices[] =
        {
            0, 1, 3, //First triangle
            1, 2, 3  //Second triangle
        };
        
        Shader shader("Resources/Shaders/Texture/texture.vert", "Resources/Shaders/Texture/texture.frag");
        
        GLuint VBO, VAO, EBO;
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        //Position attr
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid * ) 0);
        glEnableVertexAttribArray(0);
        
        //Color attr
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid * ) (3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        
        //Texture attr
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid * ) (6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0); //Unbind VAO
        
        GLuint texture;
        
        int width, height;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        unsigned char *image = SOIL_load_image("Resources/Images/life.png", &width, &height, 0, SOIL_LOAD_RGBA);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        while( !glfwWindowShouldClose(window)){
            
            glfwPollEvents();
            
            glClearColor(0.3f, 0.1f, 0.4f, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            shader.Use();
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glUniform1i( glGetUniformLocation(shader.Program, "mainTexture"), 0);
            
            
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
            
            //swap the screen buffers
            glfwSwapBuffers(window);
        }
        
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        
        glfwTerminate();
        
        std::cout << "\nClose program...\n";
        return 0;
    }
};
