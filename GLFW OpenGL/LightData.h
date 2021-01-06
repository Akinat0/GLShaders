#pragma once

struct LightData{
    
    LightData(){
        Position = glm::vec3(0, 0, 0);
        Direction = glm::vec3(0, 0, 0);
        
        AmbientColor = glm::vec3(0, 0, 0);
        DiffuseColor = glm::vec3(0, 0, 0);
        SpecularColor = glm::vec3(0, 0, 0);
        
        Constant = 0;
        Linear = 0;
        Quadratic = 0;

        Intensity = 0;
    }
    
    LightData(glm::vec3 position, glm::vec3 direction){
        
        Position = position;
        Direction = direction;
        
        AmbientColor = glm::vec3(0.1f, 0.1f, 0.1f);
        DiffuseColor = glm::vec3(0.9f, 0.9f, 0.9f);
        SpecularColor = glm::vec3(1.1f, 1.1f, 1.1f);
        
        Constant = 1;
        Linear = 0.9f;
        Quadratic = 0.032f;

        Intensity = 1.2f;
    }
    
    glm::vec3 Position;
    glm::vec3 Direction;
    
    glm::vec3 AmbientColor;
    glm::vec3 DiffuseColor;
    glm::vec3 SpecularColor;

    float Intensity;

    float Constant;
    float Linear;
    float Quadratic;
};
