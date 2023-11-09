#version 330
layout(location=0) in vec3 vp; //vertex position

out vec3 toFrag_worldNormal; //transformed normal to fragment shader
out vec4 toFrag_worldPosition; //transformed position to fragment shader
out vec3 toFrag_cameraLocation; //camera position for fragment shader

out vec3 toFrag_textureCoords;

uniform mat4 modelMatrix; //transformation matrix, UNUSED
uniform mat4 viewMatrix; //camera view matrix
uniform mat4 projectionMatrix; //camera projection matrix

void main () {
    toFrag_textureCoords = vp;

    vec4 position = projectionMatrix * viewMatrix * vec4(vp, 1.0);
    //w-component of the position vector is equal to the w-component before the perspective division.
    gl_Position = position;
}
