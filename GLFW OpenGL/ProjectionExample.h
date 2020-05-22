#ifndef ProjectionExample_h
#define ProjectionExample_h
#endif /* ProjectionExample_h */

#include <iostream>

#include "SOIL2/SOIL2.h"

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class ProjectionExample{
    
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
        
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Projection", nullptr, nullptr);
        
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
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        
        //TODO research what's it exactly
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        // Set up vertex data (and buffer(s)) and attribute pointers
        // use with Orthographic Projection
        /*
        GLfloat vertices[] = {
            -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,
            0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 0.0f,
            0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
            0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
            -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
            -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,
            
            -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
            0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
            0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
            0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
            -0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 1.0f,
            -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
            
            -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
            -0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
            -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
            -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
            -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
            -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
            
            0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
            0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
            0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
            0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
            0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
            0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
            
            -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
            0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
            0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
            0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
            -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
            -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
            
            -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
            0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
            0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
            0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
            -0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
            -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f
        };
         */

        // use with Perspective Projection
        GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        
        Shader shader("Resources/Shaders/Projection/projection.vert", "Resources/Shaders/Projection/projection.frag");
        
        GLuint VBO, VAO;
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        //Position attr
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid * ) 0);
        glEnableVertexAttribArray(0);
        
        //Texture attr
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid * ) (3 * sizeof(GLfloat)));
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
        
        glm::mat4 projection(1);
        projection = glm::perspective(45.0f, (GLfloat)(screenWidth / screenHeight), 0.1f, 1000.0f);
//        projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);

        
        
        while( !glfwWindowShouldClose(window)){
            
            glfwPollEvents();
            
            glClearColor(0.3f, 0.1f, 0.4f, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glUniform1i( glGetUniformLocation(shader.Program, "mainTexture"), 0);
            
            shader.Use();
            
            glm::mat4 model(1);
            glm::mat4 view(1);
            
            float time = glfwGetTime();
            
            model = glm::rotate(model, (GLfloat)time, glm::vec3(0.5f, 1.0f, 0.0f)); //rotation
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f)); //local position
            model = glm::scale(model, glm::vec3( std::fmod(time, 2.0f))); //scale
            
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); //viewport position
            
            GLint modelLoc = glGetUniformLocation(shader.Program, "model");
            GLint viewLoc = glGetUniformLocation(shader.Program, "view");
            GLint projectionLoc = glGetUniformLocation(shader.Program, "projection");
            
//            std::cout<<modelLoc<<" "<<viewLoc<<" "<<projectionLoc<<std::endl;
            
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0); //TODO test without it
            
            //swap the screen buffers
            glfwSwapBuffers(window);
        }
        
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        
        glfwTerminate();
        
        std::cout << "\nClose program...\n";
        return 0;
    }
};
