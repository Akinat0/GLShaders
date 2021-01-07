#pragma once

#include "LitShader.h"
#include "LightObject.h"
#include "LightData.h"
#include "FogData.h"

class LitModelObject : public ModelObject{
public:
    LitModelObject(Model *geometry, Camera *camera) : ModelObject(geometry, new LitShader()){
        this->camera = camera;
        fogData = FogData();
    }
    
    void Draw(glm::mat4 view, glm::mat4 projection) override {
        
        shader->Use();

        for(int i=0; i<lightsData.size(); i++){
            glUniform3f(glGetUniformLocation(shader->Program, ("lights[" + to_string(i) + "].ambient").c_str()), 0.3f, 0.3f, 0.3f);
            glUniform3f(glGetUniformLocation(shader->Program, ("lights[" + to_string(i) + "].diffuse").c_str()), 0.9f, 0.9f, 0.9f);
            glUniform3f(glGetUniformLocation(shader->Program, ("lights[" + to_string(i) + "].specular").c_str()), 1.1f, 1.1f, 1.1f);

            glUniform1f(glGetUniformLocation(shader->Program, ("lights[" + to_string(i) + "].constant").c_str()), lightsData[i].Constant);
            glUniform1f(glGetUniformLocation(shader->Program, ("lights[" + to_string(i) + "].linear").c_str()), lightsData[i].Linear);
            glUniform1f(glGetUniformLocation(shader->Program, ("lights[" + to_string(i) + "].quadratic").c_str()), lightsData[i].Quadratic);


            glUniform3fv(glGetUniformLocation(shader->Program, ("lights[" + to_string(i) + "].position").c_str()), 1, glm::value_ptr(lightsData[i].Position));
            glUniform3fv(glGetUniformLocation(shader->Program, ("lights[" + to_string(i) + "].direction").c_str()), 1, glm::value_ptr(lightsData[i].Direction));

            glUniform1f(glGetUniformLocation(shader->Program, ("lights[" + to_string(i) + "].intensity").c_str()), lightsData[i].Intensity);
        }

        glUniform1f(glGetUniformLocation(shader->Program, "fog.minDist"), fogData.MinDist);
        glUniform1f(glGetUniformLocation(shader->Program, "fog.maxDist"), fogData.MaxDist);
        glUniform3fv(glGetUniformLocation(shader->Program, "fog.color"), 1, glm::value_ptr(fogData.Color));

        glUniform3fv(glGetUniformLocation(shader->Program, "viewPos"), 1, glm::value_ptr(camera->GetPosition()));
        glUniform1f(glGetUniformLocation(shader->Program, "material.shininess"), 60.0f);
        
        ModelObject::Draw(view, projection);
    }
    
    void ClearLightData(){
        lightsData.clear();
    }
    
    void AddLightData(LightData lightData){
        lightsData.push_back(lightData);
    }

    FogData GetFogData(){
        return fogData;
    }

    void SetFogData(FogData fogData){
        this->fogData = fogData;
    }
    
protected:
    Camera *camera;
    vector<LightData> lightsData;
    FogData fogData;
};
