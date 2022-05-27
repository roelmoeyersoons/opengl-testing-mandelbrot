#version 330 core
#pragma language glsl3
#extension GL_ARB_gpu_shader_fp64 : enable

out vec4 FragColor;

in vec3 ourColor;
in vec2 fragCoords;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

uniform int Time;
//uniform int ITERATIONS;
//uniform double xCoord;
//uniform double yCoord;
//uniform double Zoom;
//uniform float infinity;

//const float ITERATIONS = 50;
const float INFINITY = 100.0f;
const float SPIRALS = 1;
const float PI = 3.14159265359f;
const float TAUINVERT = 0.15923566879f;
const float PHASE = TAUINVERT * SPIRALS;

const vec3 a = vec3(0.5, 0.5, 0.5);
const vec3 b = vec3(0.5, 0.5, 0.5);
const vec3 c = vec3(1.0, 1.0, 1.0);
const vec3 d = vec3(0.0, 0.0, 0.0);  


vec3 palette( in double t, in vec3 a, in vec3 b, in vec3 c, in vec3 d)
{
    vec3 fullColor = a + b*cos( 6.28318*(c*float(t)+d));
    return fullColor;
}
//MSS IETS MET FRACT DOEN


//dus: je berekent atan: dit geeft een hoek/radian terug op basis van ingegeven xy coordinaat
//hierin mag je een getal steken van -3.14 tot +3.14, alles van pi
//indien x < 0 is dan moet je atan + pi doen

//hierboven zie je een cos functie, die is defined
void main()
{
    float x = fragCoords.x;
    float y = fragCoords.y;
    float radius = sqrt(x*x + y*y);

    //float angle = acos(x/radius);
    //if(y < 0)
    //    angle*=-1;

    //float flippingcos = cos(y/x);
    //if(int(y*10) % 2 == 0)
    //    x *=-1;



    float division = y/x;
    //if(division < 0.0f) mirrors against y axis, this is like a abs(atan) 
    //    division *=-1;

    float angleRadians = atan(y/x)*20; //factor determines amount of rays
    //if(int(angleRadians / PI) % 2 == 0)
    //    angleRadians + PI;
    //if(x < 0) //use when using atan2 and cos for drawing, otherwise cos result is negative
    //    angleRadians += PI;
    float angleNormalized = cos(angleRadians)*0.5+0.5;
    
    //vec3 color = palette(angleNormalized, a, b, c, d);
    vec3 color = vec3(angleNormalized, 0.0f, 0.0f);

    

    FragColor = vec4(color, 1.0f);
    //FragColor = mix(texture(texture1, fTexCoords), texture(texture2, fTexCoords), 0.3);
}

