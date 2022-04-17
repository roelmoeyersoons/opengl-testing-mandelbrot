#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec2 fTexCoords;

uniform sampler2D tx;
  
void main()
{
    FragColor = texture(tx, fTexCoords);
}