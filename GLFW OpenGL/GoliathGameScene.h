#pragma once

#include <string>
#include <vector>
#include "Shader.h"
#include "GameObject.h"
#include "GameScene.h"

class GoliathGameScene : public GameScene{
public:
    GoliathGameScene(Camera *camera, glm::mat4 projection) : GameScene(camera, projection){
        Shader *shader = new Shader( "Resources/Shaders/Model/modelLoading.vert", "Resources/Shaders/Model/modelLoading.frag" );
        Model *ourModel = new Model("Resources/Models/nano_suit/nanosuit.obj" );
    
        goliath = new ModelObject(ourModel, shader);
        
        this->gameObjects.push_back(goliath);
    }

private:
    ModelObject* goliath;
};
