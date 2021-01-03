#pragma once

#include <string>
#include <vector>
#include "Shader.h"
#include "GameObject.h"
#include "GoliathGameObject.h"
#include "GameScene.h"


class GoliathGameScene : public GameScene{
public:
    GoliathGameScene(Camera *camera, glm::mat4 projection) : GameScene(camera, projection){

        goliath = new GoliathGameObject();
        
        this->gameObjects.push_back(goliath);
    }
    
    void Update(float deltaTime) override{
        GameScene :: Update(deltaTime);
    }

private:
    GoliathGameObject* goliath;
};
