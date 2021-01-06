#pragma once
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

class GameObject {
public:
    
    GameObject(){
        model = glm::mat4(1);
    }
    
    void Scale(glm::vec3 vector){
        model = glm::scale( model, vector );
    }
    
    void Translate(glm::vec3 vector){
        model = glm::translate( model, vector );
    }
    
    void Rotate(float angle, glm::vec3 axis){
        model = glm::rotate(model, angle, axis);
    }

    glm::mat4 GetModel(){
        return model;
    }
    
    glm::vec3 GetPosition(){
        return glm::vec3(model[3]);
    }
    
    glm::quat GetRotation(){
        glm::mat4 transformation; // your transformation matrix.
        glm::vec3 scale;
        glm::quat rotation;
        glm::vec3 translation;
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(transformation, scale, rotation, translation, skew, perspective);
        return rotation;
    }
    
    glm::vec3 GetForward(){
        return GetRotation() * glm::vec3(0, 0, 1);
    }
    
    virtual void Draw(glm::mat4 view, glm::mat4 projection){
//        cout<<"Draw game object ";
    }
    
    virtual void Update(float deltaTime){}
    
protected:
    glm::mat4 model;
    
};
