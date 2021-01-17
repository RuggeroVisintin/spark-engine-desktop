#version 330 core

// Ouput data
out float color;

void main(){
    color = gl_FragCoord.z;
}