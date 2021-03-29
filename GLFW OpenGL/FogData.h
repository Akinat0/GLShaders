#pragma once

struct FogData{

    FogData(){
        Color = glm::vec3(0.3,0.3,0.3);
        MinDist = 5;
        MaxDist = 12;
    }

    FogData(glm::vec3 color, float minDist, float maxDist){
        Color = color;
        MinDist = minDist;
        MaxDist = maxDist;
    }

    glm::vec3 Color;
    float MaxDist;
    float MinDist;
};
