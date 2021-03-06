#include <string>
#include <random>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 800;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );

// Camera
Camera  camera(glm::vec3( 0.0f, 0.0f, 3.0f ) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

class CameraExample
{
public:
    int Start(){
        // Init GLFW
        glfwInit( );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
        
        GLFWwindow* window = glfwCreateWindow( WIDTH, HEIGHT, "Camera", nullptr, nullptr ); // Windowed
        
        if ( nullptr == window )
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate( );
            
            return EXIT_FAILURE;
        }
        
        glfwMakeContextCurrent( window );
        
        glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
        
        // Set the required callback functions
        glfwSetKeyCallback( window, KeyCallback );
        glfwSetCursorPosCallback( window, MouseCallback );
        glfwSetScrollCallback( window, ScrollCallback );
        
        // Options, removes the mouse cursor for a more immersive experience
        glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
        
        // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
        glewExperimental = GL_TRUE;
        // Initialize GLEW to setup the OpenGL Function pointers
        if ( GLEW_OK != glewInit( ) )
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return EXIT_FAILURE;
        }
        
        // Define the viewport dimensions
        glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
        
        // Setup some OpenGL options
        glEnable( GL_DEPTH_TEST );
        
        // enable alpha support
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        
        // Setup and compile our shaders
        Shader lightShader( "Resources/Shaders/Light/light.vert", "Resources/Shaders/Light/light.frag" );
        Shader litShader( "Resources/Shaders/Light/lit.vert", "Resources/Shaders/Light/lit.frag" );
        
        // Set up our vertex data (and buffer(s)) and attribute pointers
        GLfloat vertices[] =
        {
           // Positions            // Normals              // Texture Coords
           -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
           0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
           0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
           0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
           -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
           -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
           
           -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
           0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
           0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
           0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,      1.0f,  1.0f,
           -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
           -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
           
           -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
           -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
           -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
           -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
           -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
           -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
           
           0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
           0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
           0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
           0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
           0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
           0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
           
           -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
           0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
           0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
           0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
           -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
           -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
           
           -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
           0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
           0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
           0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
           -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
           -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
        };
        
        // Positions all containers
        glm::vec3 cubePositions[] = {
            glm::vec3(  0.0f,   0.0f,   0.0f),
            glm::vec3(  2.0f,   5.0f,   -15.0f),
            glm::vec3(  -1.5f,  -2.2f,  -2.5f),
            glm::vec3(  -3.8f,  -2.0f,  -12.3f),
            glm::vec3(  2.4f,   -0.4f,  -3.5f),
            glm::vec3(  -1.7f,  3.0f,   -7.5f),
            glm::vec3(  1.3f,   -2.0f,  -2.5f),
            glm::vec3(  1.5f,   2.0f,   -2.5f),
            glm::vec3(  1.5f,   0.2f,   -1.5f),
            glm::vec3(  -1.3f,  1.0f,   -1.5f)
        };
        
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    
        GLuint VBO, boxVAO;
        glGenVertexArrays( 1, &boxVAO );
        glGenBuffers( 1, &VBO );
        // Bind our Vertex Array Object first, then bind and set our buffers and pointers.
        glBindVertexArray( boxVAO );
        
        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
        
        // Position attribute
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )0 );
        glEnableVertexAttribArray( 0 );
        
        // Position attribute
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )(3 * sizeof(GLfloat)) );
        glEnableVertexAttribArray( 1 );
        
        // Texture attribute
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )(6 * sizeof(GLfloat)) );
        glEnableVertexAttribArray( 2 );
    
        
//        GLuint lightVAO;
//        glGenVertexArrays( 1, &lightVAO );
//        glGenBuffers( 1, &VBO );
//
//        // Bind our Vertex Array Object first, then bind and set our buffers and pointers.
//        glBindVertexArray( lightVAO );
//
//        glBindBuffer( GL_ARRAY_BUFFER, VBO );
//        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
//

//         Position attribute
//        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )0 );
//        glEnableVertexAttribArray( 0 );
//        glBindVertexArray(0);
        
        GLuint diffuseMap, specularMap;
        glGenTextures( 1, &diffuseMap );
        glGenTextures( 1, &specularMap );
        
        int textureWidth, textureHeight;
        unsigned char *image;
        
        // Diffuse map
        image = SOIL_load_image( "Resources/Images/container2.png", &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB );
        glBindTexture( GL_TEXTURE_2D, diffuseMap );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
        glGenerateMipmap( GL_TEXTURE_2D );
        SOIL_free_image_data( image );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST );
        
        // Specular map
        image = SOIL_load_image( "Resources/Images/container2_specular.png", &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB );
        glBindTexture( GL_TEXTURE_2D, specularMap );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
        glGenerateMipmap( GL_TEXTURE_2D );
        SOIL_free_image_data( image );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST );
        glBindTexture( GL_TEXTURE_2D, 0 );
        
        // Set texture units
        litShader.Use( );
        glUniform1i( glGetUniformLocation( litShader.Program, "material.diffuse" ),  0 );
        glUniform1i( glGetUniformLocation( litShader.Program, "material.specular" ), 1 );
        
        glBindVertexArray( 0 ); // Unbind VAO
                
        glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)(SCREEN_WIDTH/SCREEN_HEIGHT), 0.1f, 1000.0f);
        
        // Game loop
        while( !glfwWindowShouldClose( window ) )
        {
            
            // Set frame time
            GLfloat currentFrame = glfwGetTime( );
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

//            if(currentFrame > 15.0f){
////                lightPos.x -= 0.0025f;
//                lightPos.z -= 0.025f;
//            }
            
            // Check and call events
            glfwPollEvents( );
            DoMovement( );
            
            // Clear the colorbuffer
            glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            
            litShader.Use();
            GLint lightPosLoc = glGetUniformLocation(litShader.Program, "light.position");
            GLint lightSpotDirLoc = glGetUniformLocation(litShader.Program, "light.direction");
            GLint viewPosLoc = glGetUniformLocation(litShader.Program, "viewPos");
            
            glUniform3f(glGetUniformLocation(litShader.Program, "light.ambient"), 0.1f, 0.1f, 0.1f);
            glUniform3f(glGetUniformLocation(litShader.Program, "light.diffuse"), 0.9f, 0.9f, 0.9f);
            glUniform3f(glGetUniformLocation(litShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
            
            glUniform1f(glGetUniformLocation(litShader.Program, "light.cutOff"), glm::cos(glm::radians(12.5f)));
            glUniform1f(glGetUniformLocation(litShader.Program, "light.outerCutOff"), glm::cos(glm::radians(17.5f)));
            
            glUniform1f(glGetUniformLocation(litShader.Program, "light.constant"), 1.0f);
            glUniform1f(glGetUniformLocation(litShader.Program, "light.linear"), 0.09f);
            glUniform1f(glGetUniformLocation(litShader.Program, "light.quadratic"), 0.032f);
            
            glUniform1f(glGetUniformLocation(litShader.Program, "material.shininess"), 32.0f);

            glUniform3f(lightPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
            glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
            glUniform3f(lightSpotDirLoc, camera.GetForward().x, camera.GetForward().y, camera.GetForward().z);

            glm::mat4 view = camera.GetViewMatrix();
            
            GLint modelLoc = glGetUniformLocation(litShader.Program, "model");
            GLint viewLoc = glGetUniformLocation(litShader.Program, "view");
            GLint projectionLoc = glGetUniformLocation(litShader.Program, "projection");
            
            // Bind diffuse map
            glActiveTexture( GL_TEXTURE0 );
            glBindTexture( GL_TEXTURE_2D, diffuseMap );
            
            // Bind specular map
            glActiveTexture( GL_TEXTURE1 );
            glBindTexture( GL_TEXTURE_2D, specularMap );
            
            glBindVertexArray(boxVAO);
            
            glm::mat4 model;
            
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            
            for (GLint i=0; i < 10; i++){
                model = glm::mat4(1);
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, 20.0f * i, glm::vec3(1.0f, 0.5f, 0.3f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            
//            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
            
//            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);

//            lightShader.Use();
//
//            modelLoc = glGetUniformLocation(lightShader.Program, "model");
//            viewLoc = glGetUniformLocation(lightShader.Program, "view");
//            projectionLoc = glGetUniformLocation(lightShader.Program, "projection");
//
//            glBindVertexArray(boxVAO);
//
//            model = glm::mat4(1);
//            model = glm::translate(model, lightPos);
//            model = glm::scale(model, glm::vec3(0.2f));
//
//            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//            glBindVertexArray(0);
            
            // Swap the buffers
            glfwSwapBuffers( window );
        }
        
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays( 1, &boxVAO );
        glDeleteBuffers( 1, &VBO );
        glfwTerminate( );
        
        return EXIT_SUCCESS;
    }

    // Moves/alters the camera positions based on user input
    void DoMovement( )
    {
        // Camera controls
        if( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
        {
            camera.ProcessKeyboard( FORWARD, deltaTime );
        }
        
        if( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
        {
            camera.ProcessKeyboard( BACKWARD, deltaTime );
        }
        
        if( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
        {
            camera.ProcessKeyboard( LEFT, deltaTime );
        }
        
        if( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
        {
            camera.ProcessKeyboard( RIGHT, deltaTime );
        }
    }
};

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}


void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset )
{
    camera.ProcessMouseScroll( yOffset );
}
