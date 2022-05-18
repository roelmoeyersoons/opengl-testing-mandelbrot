#version 330 core
out vec4 FragColor;  


in vec3 ourColor;
in vec3 pNormal;
in vec3 FragPos;  

//uniform sampler2D texture1;
//uniform sampler2D texture2;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    //FragColor = mix(texture(texture1, fTexCoords), texture(texture2, fTexCoords), 0.3);
    float ambientStrength = 0.2;
    float specularStrength = 0.5;

    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(pNormal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;



    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (ambient + diffuse + specular) * objectColor;
    
    FragColor = vec4(result, 1.0);
}