#pragma once

#include "ModelObject.h"
#include "LitModelObject.h"

class GoliathGameObject : public LitModelObject{
public:
    
    GoliathGameObject(Camera *camera) : LitModelObject(new Model("Resources/Models/nano_suit/nanosuit.obj"), camera){
        
        this->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
    };
    
    void Update(float deltaTime) override {
        LitModelObject::Update(deltaTime);
        
        //this->Translate(glm::vec3(1*deltaTime, 1*deltaTime, 1*deltaTime));
    }
    
//    void Draw(glm::mat4 view, glm::mat4 projection) override {
//        
//        LitModelObject::Draw(view, projection);
//    }
};
