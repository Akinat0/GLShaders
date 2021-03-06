#pragma once

#include "ToonShader.h"
#include "LightData.h"

class CellShadedModelObject : public ModelObject{

public:
    CellShadedModelObject(Model *geometry, Camera *camera) : ModelObject(geometry, new ToonShader()){
        this->camera = camera;
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

protected:
    Camera *camera;
    vector<LightData> lightsData;
};