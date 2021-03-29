#pragma once

#include <string>
#include <vector>
#include "Shader.h"
#include "GameObject.h"
#include "GoliathGameObject.h"
#include "GameScene.h"
#include "LightObject.h"
#include "CellShadedModelObject.h"


class GoliathGameScene : public GameScene{
public:
    GoliathGameScene(Camera *camera, glm::mat4 projection) : GameScene(camera, projection){

        for(int i=0; i<10; i++){
            GoliathGameObject* goliath = new GoliathGameObject(camera);
            goliath->Translate(glm::vec3(i*5, 0, 0));
            goliaths.push_back(goliath);
            gameObjects.push_back(goliath);
        }
        

//        toonGoliath = new CellShadedModelObject(new Model("Resources/Models/nano_suit/nanosuit.obj"), camera);
//        toonGoliath->Scale(glm::vec3(0.2f, 0.2f, 0.2f));

        light1 = new LightObject(glm::vec3(0.2f, 0.5f, 1.0f));
        light1->Translate(glm::vec3(30, 12.5f, 20));
        light1->Scale(glm::vec3(0.1f, 0.1f, 0.1f));


//        this->gameObjects.push_back(goliath);
//        this->gameObjects.push_back(goliath1);
//        this->gameObjects.push_back(toonGoliath);
        this->gameObjects.push_back(light1);
     
    }
    
    void Update(float deltaTime) override{
        GameScene :: Update(deltaTime);

//        goliath->Rotate(0.2f*deltaTime, glm::vec3(0, 1, 0));
//        sphere1->Rotate(1*deltaTime, glm::vec3(0, 1, 0));

        for(int i=0; i<goliaths.size(); i++){
        
            goliaths[i]->ClearLightData();
            goliaths[i]->AddLightData(light1->GetLightData());
            
        }
        
//        goliath->ClearLightData();
//        goliath->AddLightData(light1->GetLightData());
//        goliath->AddLightData(light3->GetLightData());
//
//        goliath1->ClearLightData();
//        goliath1->AddLightData(light1->GetLightData());
//        goliath1->AddLightData(light3->GetLightData());
//        goliath->AddLightData(light4->GetLightData());
//        goliath->AddLightData(light5->GetLightData());

//        toonGoliath->ClearLightData();
//        toonGoliath->AddLightData(light1->GetLightData());
//        toonGoliath->AddLightData(light2->GetLightData());
//        toonGoliath->AddLightData(light3->GetLightData());
//        toonGoliath->AddLightData(light4->GetLightData());
//        toonGoliath->AddLightData(light5->GetLightData());
    }

private:

    vector<GoliathGameObject*> goliaths;
//    GoliathGameObject* goliath;
//    GoliathGameObject* goliath1;
    LightObject* light1;

};
