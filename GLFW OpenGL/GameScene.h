#pragma once

#include <string>
#include <vector>
#include "Camera.h"
#include "GameObject.h"

class GameScene{
public:
    GameScene(Camera *camera, glm::mat4 projection){
        this->camera = camera;
        this->projection = projection;
    }
    
    virtual void Update(float deltaTime){
        for (int i = 0; i < gameObjects.size(); i++) {
            this->gameObjects[i]->Update(deltaTime);
        }
    }
    
    void Draw(){
        
        for (int i = 0; i < gameObjects.size(); i++) {
            this->gameObjects[i]->Draw(camera->GetViewMatrix(), projection);
        }
    }

protected:

    vector<GameObject*> gameObjects;
    
private:
    
    Camera *camera;
    glm::mat4 projection;
};
