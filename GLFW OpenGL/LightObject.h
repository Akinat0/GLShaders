#pragma once

#include "ModelObject.h"
#include "LightData.h"

class LightObject : public ModelObject{
public:
    LightObject(glm::vec3 color) : ModelObject(new Model("Resources/Models/sphere/sphere.obj"), new Shader("Resources/Shaders/Light/light.vert", "Resources/Shaders/Light/light.frag"))
    {
        Color = color;
        this->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
    }
    
    void Draw(glm::mat4 view, glm::mat4 projection) override{
        
        ModelObject::Draw(view, projection);
        
        shader->Use();
        
        glUniform3fv( glGetUniformLocation( shader->Program, "lightColor" ), 1, glm::value_ptr(Color));
    }
    
    LightData GetLightData(){
        LightData lightData(GetPosition(), GetForward());
        return lightData;
    }
    
    glm::vec3 Color;
};
