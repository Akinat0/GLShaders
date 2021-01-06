#pragma once

#include "Shader.h"
#include "Model.h"
#include "GameObject.h"

using namespace std;

class ModelObject : public GameObject {

public:
    ModelObject(Model *geometry, Shader *shader) : GameObject(){
        this->geometry = geometry;
        this->shader = shader;
    }
    
    void Draw(glm::mat4 view, glm::mat4 projection) override {
        
        GameObject::Draw(view, projection);
        
        shader->Use();
        
        //Pass mvp to gl
        glUniformMatrix4fv( glGetUniformLocation( shader->Program, "model" ), 1, GL_FALSE, glm::value_ptr( model ) );
        glUniformMatrix4fv( glGetUniformLocation( shader->Program, "view" ), 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( glGetUniformLocation( shader->Program, "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );
        
        geometry->Draw(shader);
    }
    
protected:
    Model *geometry;
    Shader *shader;
};
