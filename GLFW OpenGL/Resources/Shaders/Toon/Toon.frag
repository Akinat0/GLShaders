#version 330 core

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    
    float shininess;
};

struct Light{
    
    float intensity;
    
    vec3 position;
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
};

out vec4 color;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform vec3 Color;
uniform Material material;
uniform Light lights[5];

vec3 toonShade( Light light, float levels, float toonScale)
{
    vec3 s = normalize( light.position.xyz - FragPos.xyz );
    float cosine = max( 0.0, dot( s, Normal ) );
    vec3 diffuse = light.diffuse * floor( cosine * levels ) * toonScale;
    return light.intensity * (light.ambient + diffuse);
}


void main(){

    float toonLevels = 3;
    float toonScale = 1 / toonLevels;
    
    vec3 result = vec3(0.0f);
    
    for(int i = 0; i < 5; i++){
        result += vec3(texture(material.diffuse, TexCoords)) * toonShade(lights[i], toonLevels, toonScale);
    }
    
//    for(int i = 0; i < 5; i++){
//        //ambient
//        vec3 ambient = lights[i].ambient * vec3(texture(material.diffuse, TexCoords));
//
//        //diffuse
//        vec3 lightDir = normalize(lights[i].position - FragPos);
//        float diff = max(dot(Normal, lightDir), 0.0f);
//        vec3 diffuse = lights[i].diffuse * diff * vec3(texture(material.diffuse, TexCoords));
//        diffuse *= lights[i].intensity;
//
//        result += ambient + diffuse;
//
//    }
    
    color = vec4(result, 1.0f);
}

