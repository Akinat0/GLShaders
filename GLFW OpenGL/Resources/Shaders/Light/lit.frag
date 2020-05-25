#version 330 core

out vec4 color;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 Color;
uniform vec3 Light;

void main(){
//    color = vec4(Color * Light, 1.0f);
    //ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * Light;
    
    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * Light;
    
    //specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * Light;
    
    vec3 result = (ambient + diffuse + specular) * Color;
    color = vec4(result, 1.0f);
}
