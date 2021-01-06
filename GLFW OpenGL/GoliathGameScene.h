#pragma once

#include <string>
#include <vector>
#include "Shader.h"
#include "GameObject.h"
#include "GoliathGameObject.h"
#include "GameScene.h"
#include "LightObject.h"


class GoliathGameScene : public GameScene{
public:
    GoliathGameScene(Camera *camera, glm::mat4 projection) : GameScene(camera, projection){

        goliath = new GoliathGameObject(camera);
        
        light1 = new LightObject(glm::vec3(0.2f, 0.5f, 1.0f));
        light1->Translate(glm::vec3(-15, 5, 0));
        light1->Scale(glm::vec3(0.1f, 0.1f, 0.1f));

        light2 = new LightObject(glm::vec3(0.2f, 0.5f, 1.0f));
        light2->Translate(glm::vec3(15, 10, 0));
        light2->Scale(glm::vec3(0.1f, 0.1f, 0.1f));

        light3 = new LightObject(glm::vec3(0.2f, 0.5f, 1.0f));
        light3->Translate(glm::vec3(0, 15, 15));
        light3->Scale(glm::vec3(0.1f, 0.1f, 0.1f));

        light4 = new LightObject(glm::vec3(0.2f, 0.5f, 1.0f));
        light4->Translate(glm::vec3(0, 20, -15));
        light4->Scale(glm::vec3(0.1f, 0.1f, 0.1f));

        light5 = new LightObject(glm::vec3(0.2f, 0.5f, 1.0f));
        light5->Translate(glm::vec3(0, 35, 0));
        light5->Scale(glm::vec3(0.1f, 0.1f, 0.1f));

        this->gameObjects.push_back(goliath);
        this->gameObjects.push_back(light1);
        this->gameObjects.push_back(light2);
        this->gameObjects.push_back(light3);
        this->gameObjects.push_back(light4);
        this->gameObjects.push_back(light5);
    }
    
    void Update(float deltaTime) override{
        GameScene :: Update(deltaTime);

        goliath->Rotate(1*deltaTime, glm::vec3(0, 1, 0));
//        sphere1->Rotate(1*deltaTime, glm::vec3(0, 1, 0));

        goliath->ClearLightData();
        goliath->AddLightData(light1->GetLightData());
        goliath->AddLightData(light2->GetLightData());
        goliath->AddLightData(light3->GetLightData());
        goliath->AddLightData(light4->GetLightData());
        goliath->AddLightData(light5->GetLightData());
    }

private:
    GoliathGameObject* goliath;
    LightObject* light1;
    LightObject* light2;
    LightObject* light3;
    LightObject* light4;
    LightObject* light5;
};
