#pragma once
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    
    virtual void Draw(glm::mat4 view, glm::mat4 projection){
        cout<<endl<<"Draw game object";
    }
    
    virtual void Update(float deltaTime){}
    
protected:
    glm::mat4 model;
    
};
