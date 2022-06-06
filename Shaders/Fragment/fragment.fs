#version 330 core
#pragma language glsl3
#extension GL_ARB_gpu_shader_fp64 : enable

out vec4 FragColor;

in vec3 ourColor;
in vec2 fragCoords;


uniform float Time;
uniform float xCoord;
uniform float yCoord;

//const float ITERATIONS = 50;
const float INFINITY = 100.0f;
const float PI = 3.14159265359F;
const float TAU = 2* PI;


const float SPIRALS = 5; 

const vec3 a = vec3(0.5, 0.0, 0.0);
const vec3 b = vec3(0.5, 0.0, 0.0);

//c == how many loops, with behaviour of atan this should be whole number
const vec3 c = vec3(1, 0.7, 0.4);
//d == phase shift. for having symmetry, this should be 0 or 0.5, more generic  x*0.5 == d*c for any x
const vec3 d = vec3(0.00, 0.15, 0.20); 

const vec3 aRadius = vec3(0.0, 0.5, 0.0);
const vec3 bRadius = vec3(0.0, 0.5, 0.0);
const vec3 cRadius = vec3(1.0, 1.0, 10);
const vec3 dRadius = vec3(0.00, 0.30, 0.20); 

vec3 palette( in double t, in vec3 a, in vec3 b, in vec3 c, in vec3 d )
{
    vec3 fullColor = a + b*cos( TAU*(c*float(t)+d) );
    return fullColor;
}

vec3 combineColors(in vec3 angleColor, in vec3 radiusColor){
    float weight = max(angleColor.x, max(angleColor.y, angleColor.z));
    
    return angleColor + weight*radiusColor;
}

void main()
{

    float x = fragCoords.x + xCoord;
    float y = fragCoords.y + yCoord;

    float radius = sqrt(x*x + y*y);

    float angleRadians = atan(y, x); //number between -PI and PI, so TAU range, for all 360 degrees of screen, flip from PI to -PI happens on 180 degrees
    float angleNormalized = SPIRALS * (angleRadians / TAU) + 0.5; //dividing by TAU gives number between -0.5 and 0.5, by adding a constant we get multiple spirals
    //this works well / so far only with the palette function, cos is unaffected by flip from PI to -PI


    vec3 colorAngle = palette(angleNormalized, a, b, c, d); //angleNormalized+ radius also cool in separate channel mode

    
    float radianUnit = 0.4f;
    float radiusNormalized = radius / radianUnit; // * TAU but done in palette function, it will go from 0 to TAU in 1 radian unit, and then repeat colors

    vec3 colorRadius = palette(radiusNormalized, aRadius, bRadius, cRadius, dRadius);

    vec3 color = combineColors(colorAngle, colorRadius);

    FragColor = vec4(color, 1.0f);
    //FragColor = mix(texture(texture1, fTexCoords), texture(texture2, fTexCoords), 0.3);
}

