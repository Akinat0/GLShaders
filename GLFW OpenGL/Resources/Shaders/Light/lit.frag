#version 330 core


uniform vec3 Color;
uniform vec3 Light;

out vec4 color;


void main(){
    color = vec4(Color * Light, 1.0f);
}
