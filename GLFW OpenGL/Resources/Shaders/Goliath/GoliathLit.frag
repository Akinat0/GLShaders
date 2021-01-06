#version 330 core

out vec4 color;

in vec2 TexCoords;

uniform sampler2D texture_diffuse;

void main()
{
    color = vec4(texture(texture_diffuse, TexCoords));
}
