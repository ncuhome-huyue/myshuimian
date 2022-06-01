#version 450 core

layout ( location = 0) in vec3 aPos;

uniform vec2 time;
uniform mat4 projection;
uniform mat4 view;
uniform vec2 D[10];
uniform vec4 param[10];
uniform int count;

out vec3 fc;

void main(){
    vec3 fin=aPos;
    for (int i=0;i<count;i++){
        //* param[0].y * D[0].x * cos(param[0].z * dot(D[0],vec2(aPos.x,aPos.z) ) + param[0].w * time.x )
        fin.x=fin.x+(param[i].x*param[i].y*D[i].x)*cos(param[i].z*dot(D[i], vec2(aPos.x, aPos.z))+param[i].w*time.x);
        fin.y=fin.y+(param[i].y*sin((param[i].z*dot(D[i], vec2(aPos.x, aPos.z))+param[i].w*time.x)));
        fin.z=fin.z+(param[i].x*param[i].y*D[i].y)*cos(param[i].z*dot(D[i], vec2(aPos.x, aPos.z))+param[i].w*time.x);
    }
    gl_Position=projection*view*vec4(fin,1.0);
}