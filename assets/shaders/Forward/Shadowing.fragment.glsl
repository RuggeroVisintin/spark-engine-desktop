#version 330 core

// Ouput data
out float color;

void main(){
    // Not really needed, OpenGL does it anyway
    color = gl_FragCoord.z;
}