#pragma once

#include "Shader.h"

class ToonShader : public Shader{
public:
    ToonShader() : Shader("Resources/Shaders/Toon/Toon.vert", "Resources/Shaders/Toon/Toon.frag"){}
};