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
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

out vec4 color;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform vec3 Color;
uniform Material material;
uniform Light lights[5];

void main(){

    vec3 result = vec3(0.0f);
    
    for(int i = 0; i < 5; i++){
        //ambient
        vec3 ambient = lights[i].ambient * vec3(texture(material.diffuse, TexCoords));
        
        //diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = lights[i].diffuse * diff * vec3(texture(material.diffuse, TexCoords));
        
        //specular
        float specularStrength = 1.0f;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
        vec3 specular = lights[i].specular * spec * vec3(texture(material.specular, TexCoords));
        
        diffuse *= lights[i].intensity;
        specular *= lights[i].intensity;
        
        //attenuation
        float dist = length(lights[i].position - FragPos);
        float attenuation = 1.0f / ( lights[i].constant + lights[i].linear * dist + lights[i].quadratic * dist * dist);

        specular *= attenuation;
//    //    ambient *= attenuation;
//    //    diffuse *= attenuation;
        
//        result += ambient + diffuse + specular;
        result += diffuse + specular;
        
    }
    

    
    color = vec4(result, 1.0f);
//    color = vec4(1.0f);
}
