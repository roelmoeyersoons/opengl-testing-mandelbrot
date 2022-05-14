#version 330 core
#pragma language glsl3
#extension GL_ARB_gpu_shader_fp64 : enable

out vec4 FragColor;

in vec3 ourColor;
in vec2 fragCoords;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

uniform int Time;
uniform int ITERATIONS;
uniform double xCoord;
uniform double yCoord;
uniform double Zoom;
//uniform float infinity;

//const float ITERATIONS = 50;
const float INFINITY = 100.0f;

const vec3 a = vec3(0.5, 0.5, 0.5);
const vec3 b = vec3(0.5, 0.5, 0.5);
const vec3 c = vec3(1.0, 0.7, 0.4);
const vec3 d = vec3(0.00, 0.15, 0.20);
const vec3 a2 = vec3(0.2, 0.5, 0.4);
const vec3 b2 = vec3(0.2, 0.4, 0.2);
const vec3 c2 = vec3(1.5, 0.5, 0.5);
const vec3 d2 = vec3(0.00, 0.25, 0.25);


vec3 palette( in double t, in vec3 a, in vec3 b, in vec3 c, in vec3 d )
{
    vec3 fullColor = a + b*cos( 6.28318*(c*float(t)+d) );
    vec3 alternateColor = a2 + b2*cos( 6.28318*(c2*float(t)+d2) ); 
    float amountFull= abs(sin(Time/float(30)));
    

    return amountFull * fullColor +  (1-amountFull) * alternateColor;
}

void main()
{

    double real = (fragCoords.x * 1.3f - 0.5f)/Zoom + xCoord;
    double imag = (fragCoords.y * 1.3f - 0.2f)/Zoom + yCoord;
    double accReal = 0.0f;
    double accImag = 0.0f;
    double vecSize = 0.0f;

    int i = 0;
    while(i < ITERATIONS && vecSize < INFINITY){
        double previousAccReal = accReal;
        accReal = ((previousAccReal * previousAccReal) - (accImag * accImag)) + real;
        accImag = 2*(previousAccReal * accImag) + imag;

        vecSize = accReal * accReal - accImag * accImag;
        i++;
    }

    double normalized = pow((float(i)/ITERATIONS),3);
    vec3 color = palette(normalized, a, b, c, d);
    //vec3 color = vec3(normalized, 0.0f, 0.0f);

    FragColor = vec4(color, 1.0f);
    //FragColor = mix(texture(texture1, fTexCoords), texture(texture2, fTexCoords), 0.3);
}

