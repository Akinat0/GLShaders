#pragma once

#include "GameObject.h"

class GoliathGameObject : public ModelObject{
public:
    
    GoliathGameObject() : ModelObject(new Model("Resources/Models/nano_suit/nanosuit.obj"), new Shader( "Resources/Shaders/Model/modelLoading.vert", "Resources/Shaders/Model/modelLoading.frag")){
        
        this->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
    };
    
    
    void Update(float deltaTime) override {
        ModelObject::Update(deltaTime);
        
        this->Translate(glm::vec3(1*deltaTime, 1*deltaTime, 1*deltaTime));
    }
};
