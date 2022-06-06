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
const float TAU = 2* PI;


const float SPIRALS = 3; 

const vec3 a = vec3(0.5, 0.5, 0.5);
const vec3 b = vec3(0.5, 0.5, 0.5);
const vec3 c = vec3(2.0, 1.0, 5.0);
//d == phase shift. for having symmetry, this should be 0 or 0.5, or 0.5 == d*c
const vec3 d = vec3(0.00, 0.0, 0.10); 

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

    float angleRadians = atan(y, x); //number between -PI and PI, so TAU range, for all 360 degrees of screen, flip from PI to -PI happens on 180 degrees
    float angleNormalized = SPIRALS * (angleRadians / TAU) + 0.5; //dividing by TAU gives number between -0.5 and 0.5, by adding a constant we get multiple spirals
    //this works well / so far only with the palette function, cos is unaffected by flip from PI to -PI


    //double normalized = pow((float(i)/ITERATIONS),3);
    vec3 color = palette(angleNormalized + radius/2 , a, b, c, d);
    //vec3 color = vec3(angleRadians, 0.0f, 0.0f);

    FragColor = vec4(color, 1.0f);
    //FragColor = mix(texture(texture1, fTexCoords), texture(texture2, fTexCoords), 0.3);
}

