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
uniform Light light[100];
uniform int n_light;

void main()
{
    vec4 result;
    for(int i=0;i<n_light;i++)
    {

    // ambient
    vec4 ambient = vec4(light[i].ambient,1.0) * texture(material.texture_diffuse1, TexCoords);
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light[i].position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = vec4(light[i].diffuse,1.0) * diff * texture(material.texture_diffuse1, TexCoords);  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec4 specular = vec4(light[i].specular,1.0) * spec * texture(material.texture_specular1, TexCoords);  
        
    result += ambient + diffuse + specular;
    }
    
    FragColor = result;
} 