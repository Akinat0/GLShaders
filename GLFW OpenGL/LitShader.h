#pragma once

#include "Shader.h"

class LitShader : public Shader{
public:
    LitShader() : Shader("Resources/Shaders/Light/lit.vert", "Resources/Shaders/Light/lit.frag"){}
};
