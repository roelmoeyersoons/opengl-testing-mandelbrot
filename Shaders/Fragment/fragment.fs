#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec2 fTexCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;
  
void main()
{
    FragColor = mix(texture(texture1, fTexCoords), texture(texture2, fTexCoords), 0.1);
}