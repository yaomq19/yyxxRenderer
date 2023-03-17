#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1; 
    sampler2D texture_normal1;
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform samplerCube skybox;
uniform Light light[100];
uniform int n_light;

void main()
{
    vec3 result1 = vec3(0.0,0.0,0.0);
    int i=0;
    vec3 ambient,norm,lightDir,diffuse,viewDir,reflectDir,specular;
    vec3 I,R,result2;
    float diff,spec;
    vec4 FragColor1,FragColor2;
    
    for(i=0;i<n_light;i++)
    {
        // ambient
        ambient = light[i].ambient * texture(material.texture_diffuse1, TexCoords).rgb;
        
        // diffuse 
        norm = normalize(Normal);
        lightDir = normalize(light[i].position - FragPos);
        diff = max(dot(norm, lightDir), 0.0);
        diffuse = light[i].diffuse * diff * texture(material.texture_diffuse1, TexCoords).rgb;
        
        // specular
        viewDir = normalize(viewPos - FragPos);
        reflectDir = reflect(-lightDir, norm);  
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        specular = light[i].specular * spec * texture(material.texture_specular1, TexCoords).rgb;
            
        result1 += (ambient + diffuse + specular);
    }
    
    I = normalize(FragPos - viewPos);
    R = reflect(I,normalize(Normal));
    result2 = texture(skybox,R).rgb;
    
    FragColor += vec4(result2,1.0);
} 