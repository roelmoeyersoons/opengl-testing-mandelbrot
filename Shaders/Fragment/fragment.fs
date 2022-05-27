#version 330 core
#pragma language glsl3
#extension GL_ARB_gpu_shader_fp64 : enable

out vec4 FragColor;

in vec3 ourColor;
in vec2 fragCoords;


uniform float Time;

//const float ITERATIONS = 50;
const float INFINITY = 100.0f;
const float PI = 3.14159265359F;

const vec3 a = vec3(0.5, 0.5, 0.5);
const vec3 b = vec3(0.5, 0.5, 0.5);
const vec3 c = vec3(1.0, 1.0, 1.0);
const vec3 d = vec3(0.00, 0.15, 0.20);


vec3 palette( in double t, in vec3 a, in vec3 b, in vec3 c, in vec3 d )
{
    vec3 fullColor = a + b*cos( 6.28318*(c*float(t)+d) );
    return fullColor;
}

void main()
{

    float x = fragCoords.x;
    float y = fragCoords.y;
    float radius = sqrt(x*x + y*y);

    //float angle = acos(x/radius);
    //if(y < 0)
    //    angle*=-1;
    float division = y/x;
    float angleRadians = atan(y, x) / (PI/1.5);
    //float angleNormalized = angleRadians / PI + 0.5;
    
    //vec3 color = palette(angle, a, b, c, d);
    //vec3 color = vec3(angleRadians, 0.0f, 0.0f);

    //double normalized = pow((float(i)/ITERATIONS),3);
    vec3 color = palette(angleRadians + radius/2 + Time, a, b, c, d);
    //vec3 color = vec3(normalized, 0.0f, 0.0f);

    FragColor = vec4(color, 1.0f);
    //FragColor = mix(texture(texture1, fTexCoords), texture(texture2, fTexCoords), 0.3);
}

